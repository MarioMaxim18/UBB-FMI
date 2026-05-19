# ID3 Decision Tree — Play Tennis

---

## Problem

Given past records of weather conditions and whether tennis was played, predict **Play Tennis = Yes/No** for new days.

Each row in `PlayTennis.csv` contains:


| Attribute       | Example values        |
| --------------- | --------------------- |
| Outlook         | Sunny, Overcast, Rain |
| Temperature     | Hot, Mild, Cool       |
| Humidity        | High, Normal          |
| Wind            | Strong, Weak          |
| **Play Tennis** | **Yes / No (target)** |


---

## Algorithm: ID3

**ID3** (Iterative Dichotomiser 3) builds a decision tree by repeatedly choosing the attribute that best separates the classes.

---

## 1. Entropy

Measures **uncertainty** in a set of labels. Higher entropy means the outcome is harder to predict.

```
H(S) = - Σ p_i · log₂(p_i)
```


| Distribution       | Entropy         |
| ------------------ | --------------- |
| All Yes or all No  | 0 bits          |
| 50% Yes, 50% No    | 1 bit           |
| Mixed (e.g. 75/25) | between 0 and 1 |


---

## 2. Information Gain

Measures how much an attribute **reduces uncertainty** when used as a split.

```
IG(S, A) = H(S) - Σ (|S_v| / |S|) · H(S_v)
```

- `H(S)` — entropy before the split
- `S_v` — subset of rows where attribute `A` equals value `v`

The attribute with the **highest information gain** is chosen at each node.

---

## 3. Tree Construction (`id3`)

Recursive procedure:

1. **Base case — pure node:** all labels are identical → create a leaf with that label.
2. **Base case — no attributes left:** create a leaf with the majority class.
3. **Otherwise:**
  - Compute information gain for each remaining attribute.
  - Pick the attribute with maximum gain as the node split.
  - For each attribute value, recurse on the corresponding subset.
  - Empty subsets get a majority-vote leaf.

Result: a tree of **decision nodes** (attributes) and **leaf nodes** (Yes/No).

---

## 4. Classification (`classify`)

To predict a new row:

1. Start at the root.
2. Follow the branch matching the row's attribute value.
3. Repeat until a leaf is reached.
4. Return the leaf label.

No entropy is computed at prediction time — only during training.

---

## 5. Output

The script:

- Prints root entropy and information gain for each attribute.
- Builds the tree with `id3()`.
- Saves a PNG diagram (`play_tennis_tree.png`).
- Reports training accuracy (how many rows the tree classifies correctly).

---

## Summary


| Step                 | Role                                    |
| -------------------- | --------------------------------------- |
| `entropy()`          | Measures label uncertainty              |
| `information_gain()` | Ranks attributes by how useful they are |
| `id3()`              | Builds the decision tree                |
| `classify()`         | Predicts using the trained tree         |


**Entropy drives training** — it tells ID3 which question to ask at each step. Once the tree is built, classification is a simple top-down traversal.