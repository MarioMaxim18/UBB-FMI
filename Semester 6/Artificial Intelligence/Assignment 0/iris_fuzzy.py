import math
import warnings
import numpy as np
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from collections import Counter

warnings.filterwarnings("ignore")

try:
    from sklearn.datasets import load_iris
    _iris   = load_iris()
    X_raw   = _iris.data
    y_raw   = np.array([_iris.target_names[i] for i in _iris.target])
    F_NAMES = list(_iris.feature_names)
except ImportError:
    raise SystemExit("scikit-learn is required: pip install scikit-learn")

CLASSES = sorted(set(y_raw))


# ── Fuzzy logic ───────────────────────────────────────────────────────────────

def triangular(x, a, b, c):
    if a == b: return 1.0 if x<=b else (0.0 if x>=c else (c-x)/(c-b))
    if b == c: return 1.0 if x>=b else (0.0 if x<=a else (x-a)/(b-a))
    if x<=a or x>=c: return 0.0
    return (x-a)/(b-a) if x<=b else (c-x)/(c-b)


def make_fuzzy_sets(col):
    lo, hi, mid = float(col.min()), float(col.max()), (float(col.min())+float(col.max()))/2
    return {
        "low":    lambda x,lo=lo,mid=mid:       triangular(x,lo,lo,mid),
        "medium": lambda x,lo=lo,mid=mid,hi=hi: triangular(x,lo,mid,hi),
        "high":   lambda x,mid=mid,hi=hi:       triangular(x,mid,hi,hi),
    }


def fuzzy_entropy(weights, labels):
    total = sum(weights)
    if total < 1e-10: return 0.0
    cw = {}
    for w,l in zip(weights,labels): cw[l]=cw.get(l,0.0)+w
    return -sum((v/total)*math.log2(v/total) for v in cw.values() if v>1e-10)


def fuzzy_information_gain(weights, labels, memberships):
    total=sum(weights); h=fuzzy_entropy(weights,labels); wh=0.0
    for mu in memberships:
        cw=[w*m for w,m in zip(weights,mu)]; ct=sum(cw)
        if ct>1e-10: wh+=(ct/total)*fuzzy_entropy(cw,labels)
    return h-wh


# ── Tree builder ──────────────────────────────────────────────────────────────

class FuzzyDecisionTree:
    def __init__(self, feature_names, max_depth=3, min_weight=1.5):
        self.feature_names = feature_names
        self.max_depth     = max_depth
        self.min_weight    = min_weight
        self.fuzzy_sets    = {}
        self.tree          = None

    def fit(self, X, y):
        for i in range(X.shape[1]):
            self.fuzzy_sets[i] = make_fuzzy_sets(X[:, i])
        self.tree = self._build(X, y, np.ones(len(y)), list(range(X.shape[1])), depth=0)
        return self

    def _build(self, X, y, weights, feats, depth):
        total = float(sum(weights))
        cw = {}
        for w,l in zip(weights,y): cw[l]=cw.get(l,0.0)+w
        majority = max(cw, key=cw.get)
        if depth>=self.max_depth or total<self.min_weight or not feats or (cw[majority]/total)>0.97:
            return {"leaf":True,"label":majority,"dist":cw,"weight":total}
        best_feat, best_ig = None, -1.0
        for fi in feats:
            mu_list=[[self.fuzzy_sets[fi][n](X[i,fi]) for i in range(len(y))] for n in ("low","medium","high")]
            ig=fuzzy_information_gain(list(weights),list(y),mu_list)
            if ig>best_ig: best_ig,best_feat=ig,fi
        if best_feat is None or best_ig<0.001:
            return {"leaf":True,"label":majority,"dist":cw,"weight":total}
        rem=[f for f in feats if f!=best_feat]
        node={"leaf":False,"feature":best_feat,"fname":self.feature_names[best_feat],
              "ig":best_ig,"weight":total,"children":{}}
        for sname in ("low","medium","high"):
            mu=np.array([self.fuzzy_sets[best_feat][sname](X[i,best_feat]) for i in range(len(y))])
            node["children"][sname]=self._build(X,y,weights*mu,rem,depth+1)
        return node

    def predict_one(self, x):
        scores = {c:0.0 for c in CLASSES}
        self._traverse(self.tree, x, 1.0, scores)
        return max(scores, key=scores.get), scores

    def _traverse(self, node, x, weight, scores):
        if node["leaf"]:
            scores[node["label"]]=scores.get(node["label"],0.0)+weight; return
        fi=node["feature"]
        for sname,child in node["children"].items():
            mu=self.fuzzy_sets[fi][sname](x[fi])
            if mu>1e-6: self._traverse(child,x,weight*mu,scores)

    def predict(self, X):
        return [self.predict_one(X[i])[0] for i in range(len(X))]


# ── Visualisation ─────────────────────────────────────────────────────────────

X_GAP, Y_STEP = 1.6, 2.0
BW, BH = 1.1, 0.38
VW, VH = 0.9, 0.32
LW, LH = 1.1, 0.38
LEAF_COLORS = {"setosa":"#AED6F1","versicolor":"#A9DFBF","virginica":"#F9E79F"}


def compute_layout(node, depth=0, x_offset=0.0):
    if node["leaf"]:
        node["_x"],node["_y"],node["_width"] = x_offset+X_GAP*0.5,-depth*Y_STEP,X_GAP; return
    total_w=0.0
    for child in node["children"].values():
        compute_layout(child,depth+1,x_offset+total_w); total_w+=child["_width"]
    node["_x"],node["_y"],node["_width"] = x_offset+total_w/2,-depth*Y_STEP,total_w


def fancy_box(ax, cx, cy, w, h, fc, text, fontsize=9, bold=False):
    ax.add_patch(mpatches.FancyBboxPatch(
        (cx-w/2,cy-h/2),w,h,boxstyle="round,pad=0.06",
        linewidth=1.2,edgecolor="#888888",facecolor=fc,zorder=3))
    ax.text(cx,cy,text,ha="center",va="center",fontsize=fontsize,
            color="#1a1a1a",zorder=4,fontweight="bold" if bold else "normal",linespacing=1.35)


def draw_tree(ax, node):
    if node["leaf"]:
        fc=LEAF_COLORS.get(node["label"],"#FAD7A0")
        fancy_box(ax,node["_x"],node["_y"],LW,LH,fc,str(node["label"]),bold=True); return
    fancy_box(ax,node["_x"],node["_y"],BW,BH,"#D5D8DC",
              f"{node['fname']}\nIG={node['ig']:.3f}",fontsize=8,bold=True)
    for val,child in node["children"].items():
        px,py=node["_x"],node["_y"]; cx,cy=child["_x"],child["_y"]; vx,vy=cx,(py+cy)/2
        ax.annotate("",xy=(vx,vy+VH/2),xytext=(px,py-BH/2),
            arrowprops=dict(arrowstyle="-|>",color="#555",lw=1.2,mutation_scale=11),zorder=2)
        fancy_box(ax,vx,vy,VW,VH,"#E8E8E8",str(val),fontsize=8)
        ax.annotate("",xy=(cx,cy+(LH/2 if child["leaf"] else BH/2)),xytext=(vx,vy-VH/2),
            arrowprops=dict(arrowstyle="-|>",color="#555",lw=1.2,mutation_scale=11),zorder=2)
        draw_tree(ax,child)


def save_tree_png(tree, filename="iris_fuzzy_tree.png"):
    compute_layout(tree)
    all_x,all_y=[],[]
    def collect(n):
        all_x.append(n["_x"]); all_y.append(n["_y"])
        if not n["leaf"]:
            for c in n["children"].values():
                all_y.append((n["_y"]+c["_y"])/2); collect(c)
    collect(tree)
    fig,ax=plt.subplots(figsize=(26,12))
    fig.patch.set_facecolor("white"); ax.set_facecolor("white")
    ax.set_xlim(min(all_x)-1,max(all_x)+1); ax.set_ylim(min(all_y)-1,max(all_y)+1)
    ax.axis("off")
    ax.set_title("Fuzzy Decision Tree — Iris Dataset (low / medium / high fuzzy sets)",fontsize=13,fontweight="bold",pad=16)
    draw_tree(ax,tree)
    plt.tight_layout()
    plt.savefig(filename,dpi=150,bbox_inches="tight",facecolor="white")
    plt.close()
    print(f"Tree saved -> {filename}")


# ── Main ──────────────────────────────────────────────────────────────────────

def main():
    print(f"Samples : {len(X_raw)},  Classes: {CLASSES}\n")

    fdt = FuzzyDecisionTree(F_NAMES, max_depth=3, min_weight=1.5)
    fdt.fit(X_raw, y_raw)
    save_tree_png(fdt.tree)

    preds   = fdt.predict(X_raw)
    correct = sum(p==t for p,t in zip(preds,y_raw))
    print(f"Training accuracy: {correct}/{len(y_raw)} = {correct/len(y_raw)*100:.1f}%")

    print("\nPer-class accuracy:")
    for cls in CLASSES:
        mask=y_raw==cls; c=sum(p==t for p,t in zip(np.array(preds)[mask],y_raw[mask]))
        print(f"  {cls:<15} {c}/{mask.sum()} = {c/mask.sum()*100:.1f}%")

    print("\nExample predictions:")
    for i in [0,51,100]:
        pred,scores=fdt.predict_one(X_raw[i])
        print(f"  Sample {i:>3} ({y_raw[i]:<12}) -> {pred}  "
              + "  ".join(f"{k}: {v:.2f}" for k,v in scores.items()))


if __name__ == "__main__":
    main()
