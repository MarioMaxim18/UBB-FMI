import math
import csv
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from collections import Counter


def entropy(rows, label):
    counts = Counter(r[label] for r in rows)
    total  = len(rows)
    return -sum((c/total)*math.log2(c/total) for c in counts.values() if c)


def information_gain(rows, attr, label):
    total = len(rows)
    parts = {}
    for r in rows:
        parts.setdefault(r[attr], []).append(r)
    return entropy(rows, label) - sum((len(s)/total)*entropy(s, label) for s in parts.values())


def id3(rows, attrs, label):
    labels = [r[label] for r in rows]
    if len(set(labels)) == 1:
        return {"leaf": True, "label": labels[0], "size": len(rows)}
    if not attrs:
        maj = Counter(labels).most_common(1)[0][0]
        return {"leaf": True, "label": maj, "size": len(rows)}
    gains = {a: information_gain(rows, a, label) for a in attrs}
    best  = max(gains, key=gains.get)
    node  = {"leaf": False, "attr": best, "ig": gains[best], "size": len(rows), "children": {}}
    rem   = [a for a in attrs if a != best]
    for val in sorted(set(r[best] for r in rows)):
        sub = [r for r in rows if r[best] == val]
        node["children"][val] = id3(sub, rem, label) if sub else \
            {"leaf": True, "label": Counter(labels).most_common(1)[0][0], "size": 0}
    return node


def classify(node, row):
    if node["leaf"]:
        return node["label"]
    val = row.get(node["attr"], "")
    return classify(node["children"][val], row) if val in node["children"] else None


# ── Visualisation ─────────────────────────────────────────────────────────────

X_GAP, Y_STEP = 1.6, 2.0
BW, BH = 1.1, 0.38
VW, VH = 0.9, 0.32
LW, LH = 1.1, 0.38


def compute_layout(node, depth=0, x_offset=0.0):
    if node["leaf"]:
        node["_x"], node["_y"], node["_width"] = x_offset + X_GAP*0.5, -depth*Y_STEP, X_GAP
        return
    total_w = 0.0
    for child in node["children"].values():
        compute_layout(child, depth+1, x_offset+total_w)
        total_w += child["_width"]
    node["_x"], node["_y"], node["_width"] = x_offset+total_w/2, -depth*Y_STEP, total_w


def fancy_box(ax, cx, cy, w, h, fc, text, fontsize=9, bold=False):
    ax.add_patch(mpatches.FancyBboxPatch(
        (cx-w/2, cy-h/2), w, h, boxstyle="round,pad=0.06",
        linewidth=1.2, edgecolor="#888888", facecolor=fc, zorder=3))
    ax.text(cx, cy, text, ha="center", va="center", fontsize=fontsize,
            color="#1a1a1a", zorder=4, fontweight="bold" if bold else "normal", linespacing=1.35)


def draw_tree(ax, node):
    if node["leaf"]:
        fancy_box(ax, node["_x"], node["_y"], LW, LH, "#FAD7A0",
                  f"Play={node['label']}", bold=True)
        return
    fancy_box(ax, node["_x"], node["_y"], BW, BH, "#AED6F1",
              f"{node['attr']}\nIG={node['ig']:.3f}", fontsize=8.5, bold=True)
    for val, child in node["children"].items():
        px, py = node["_x"], node["_y"]
        cx, cy = child["_x"], child["_y"]
        vx, vy = cx, (py+cy)/2.0
        ax.annotate("", xy=(vx, vy+VH/2), xytext=(px, py-BH/2),
            arrowprops=dict(arrowstyle="-|>", color="#555", lw=1.2, mutation_scale=11), zorder=2)
        fancy_box(ax, vx, vy, VW, VH, "#E8E8E8", str(val), fontsize=8.5)
        ax.annotate("", xy=(cx, cy+(LH/2 if child["leaf"] else BH/2)), xytext=(vx, vy-VH/2),
            arrowprops=dict(arrowstyle="-|>", color="#555", lw=1.2, mutation_scale=11), zorder=2)
        draw_tree(ax, child)


def save_tree_png(tree, filename="play_tennis_tree.png"):
    compute_layout(tree)
    all_x, all_y = [], []
    def collect(n):
        all_x.append(n["_x"]); all_y.append(n["_y"])
        if not n["leaf"]:
            for c in n["children"].values():
                all_y.append((n["_y"]+c["_y"])/2); collect(c)
    collect(tree)
    fig, ax = plt.subplots(figsize=(11, 7))
    fig.patch.set_facecolor("white"); ax.set_facecolor("white")
    ax.set_xlim(min(all_x)-1, max(all_x)+1)
    ax.set_ylim(min(all_y)-1, max(all_y)+1)
    ax.axis("off")
    ax.set_title("ID3 Decision Tree — Play Tennis", fontsize=13, fontweight="bold", pad=16)
    draw_tree(ax, tree)
    plt.tight_layout()
    plt.savefig(filename, dpi=150, bbox_inches="tight", facecolor="white")
    plt.close()
    print(f"Tree saved -> {filename}")


# ── Main ──────────────────────────────────────────────────────────────────────

def main():
    with open("PlayTennis.csv", newline="", encoding="utf-8") as f:
        data = list(csv.DictReader(f))

    label = "Play Tennis"
    attrs = [c for c in data[0] if c != label]

    print(f"Samples : {len(data)}")
    print(f"Root entropy: {entropy(data, label):.4f} bits\n")
    print("Information Gain at root:")
    for a, ig in sorted([(a, information_gain(data, a, label)) for a in attrs], key=lambda x: -x[1]):
        print(f"  IG({a:<12}) = {ig:.4f}  {'█'*int(ig*40)}")

    tree = id3(data, attrs, label)
    save_tree_png(tree)

    correct = sum(1 for r in data if classify(tree, r) == r[label])
    print(f"Training accuracy: {correct}/{len(data)} = {correct/len(data)*100:.1f}%")


if __name__ == "__main__":
    main()
