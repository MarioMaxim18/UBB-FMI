# Task 0 — Particle Simulation & Entropy Visualization

---

## 1. Entropy — Conceptual Overview

Entropy is a measure of **disorder**, **uncertainty**, or **spread** within a system.
It appears in two distinct but deeply related fields:

| Field              | Question it answers                                          |
| ------------------ | ------------------------------------------------------------ |
| Thermodynamics     | How disordered is the physical state of a system?            |
| Information Theory | How uncertain / unpredictable is a probability distribution? |

Both formulations converge on the same idea: **the more spread out** a system is across its possible states, the **higher the entropy**.

---

## 2. Boltzmann Entropy (Thermodynamic)

### Origin

Introduced by **Ludwig Boltzmann** (1877) to connect the microscopic behaviour of particles to the macroscopic concept of thermodynamic entropy from the Second Law of Thermodynamics.

### Key Concepts

- A **macrostate** is what we observe at large scale (e.g., temperature, pressure).
- A **microstate** is one specific configuration of all particles (positions + velocities) that produces that macrostate.
- **Ω (omega)** — the number of microstates compatible with a given macrostate.

### Formula

```
S = k_B * ln(Ω)
```

| Symbol | Meaning                                    |
| ------ | ------------------------------------------ |
| S      | Entropy (SI unit: J/K)                     |
| k_B    | Boltzmann constant = 1.380649 × 10⁻²³ J/K |
| Ω      | Number of accessible microstates           |
| ln     | Natural logarithm                          |

### Intuition

- If all particles are crammed into one corner → very few microstates → low Ω → **low S**.
- If particles are spread uniformly across the box → enormous number of arrangements → high Ω → **high S**.
- This is why systems naturally evolve toward high entropy: there are simply far more disordered states than ordered ones.

### Example

Suppose a box is divided into 2 halves, with N = 4 particles:

- All 4 on the left:  Ω = 1        →  S = k_B * ln(1) = 0
- 2 on each side:     Ω = C(4,2) = 6  →  S = k_B * ln(6) ≈ 2.47 × 10⁻²³ J/K

---

## 3. Shannon Entropy (Information Theory)

### Origin

Introduced by **Claude Shannon** (1948) in his landmark paper *"A Mathematical Theory of Communication"*.
Although developed for communication channels, it is mathematically equivalent to Boltzmann entropy (with k_B = 1 and natural log replaced by log base 2).

### Formula

```
H = - sum( p_i * log2(p_i) )   for i = 1 to n
```

| Symbol | Meaning                                     |
| ------ | ------------------------------------------- |
| H      | Entropy (unit: **bits**)                    |
| p_i    | Probability of outcome i                    |
| log2   | Logarithm base 2                            |
| n      | Number of possible outcomes (bins / states) |

**Convention:** when p_i = 0, the term contributes 0  (since the limit of p * log(p) as p → 0 equals 0).

### Intuition

- If all particles in a subcube have the **same speed** → distribution is a spike → H = 0 bits (no uncertainty).
- If particles are spread **uniformly** across all speed bins → H = log2(n) bits (maximum uncertainty).
- H = 0 is the minimum; H = log2(n) is the maximum for n equally probable outcomes.

### Maximum Entropy

For n bins of equal probability ( p_i = 1/n for all i ):

```
H_max = - sum( (1/n) * log2(1/n) )  =  log2(n)
```

In this simulation with **8 speed bins**:  H_max = log2(8) = **3 bits**.

---

## 4. Connection Between Boltzmann and Shannon Entropy

Shannon entropy is the **information-theoretic generalisation** of Boltzmann entropy.

| Boltzmann                             | Shannon                                 |
| ------------------------------------- | --------------------------------------- |
| Counts microstates (Ω)                | Works with probabilities (p_i)          |
| Uses natural log                      | Uses log base 2 (or natural log)        |
| Physical constant k_B gives units J/K | Unitless (or "bits" with log2)          |
| Applies to physical systems           | Applies to any probability distribution |

If each of the Ω microstates is equally likely, then p_i = 1/Ω for all i, and:

```
H_Shannon = - sum( (1/Ω) * log2(1/Ω) )
           = log2(Ω)
           = S_Boltzmann / (k_B * ln(2))
```

They are the same quantity, differing only by a physical constant and the base of the logarithm.

---

## 5. How Entropy is Applied in This Simulation

### Spatial Decomposition

The main cube (side length L) is divided into an **n × n × n grid** of equal subcubes, each with side length L/n.
At every animation frame, each particle is assigned to exactly one subcube based on its (x, y, z) position:

```
cell_index_x = floor( (x + L/2) / (L/n) )   clamped to [0, n-1]
cell_index_y = floor( (y + L/2) / (L/n) )   clamped to [0, n-1]
cell_index_z = floor( (z + L/2) / (L/n) )   clamped to [0, n-1]
```

### Speed Histogram per Subcube

For each subcube, particle speeds are collected and placed into **B = 8 equally spaced bins** spanning [0, v_max]:

```
bin_index = floor( |v| / v_max * B )   clamped to [0, B-1]
```

### Shannon Entropy per Subcube

Let `c_j` be the count in speed bin j, and `N = sum(c_j)` the total particles in that subcube:

```
p_j = c_j / N

H = - sum( p_j * log2(p_j) )   for j = 1 to B
```

- Subcube where all particles move at the same speed  →  H ≈ 0 bits
- Subcube where particles are spread across all speed bins  →  H ≈ log2(8) = 3 bits

### Colour Mapping

Each subcube is coloured using a 5-stop gradient mapped linearly from H = 0 to H = H_max:

| H value     | Colour    | Physical meaning                                  |
| ----------- | --------- | ------------------------------------------------- |
| 0 (minimum) | Deep Blue | All particles same speed — highly ordered         |
| ~25% of max | Cyan      | Slightly disordered                               |
| ~50% of max | Green     | Moderately disordered                             |
| ~75% of max | Yellow    | Mostly disordered                                 |
| H_max       | Red       | Maximally disordered — uniform speed distribution |

---

## 6. Particle Dynamics

### Initial Conditions

- **Positions:** uniformly random inside the cube — (x, y, z) each drawn from Uniform(-L/2, +L/2).
- **Velocities:** random direction on the unit sphere, magnitude drawn from:

```
|v| ~ Uniform(0.6 * T,  1.4 * T)
```

where T is the temperature parameter set by the slider.

### Wall Collisions (Elastic Reflection)

When a particle hits a wall, the velocity component **normal to that wall** is reversed:

```
hit left/right wall   →   v_x = -v_x
hit top/bottom wall   →   v_y = -v_y
hit front/back wall   →   v_z = -v_z
```

This conserves kinetic energy (elastic collision with an infinitely massive wall).

### Temperature Parameter

Temperature T acts as a **speed scaling factor**. Increasing T rescales all particle velocities proportionally:

```
v_new = (T / |v_old|) * v_old * ξ,    ξ ~ Uniform(0.6, 1.4)
```

This is analogous to the Maxwell–Boltzmann distribution, where higher temperature means higher mean kinetic energy and higher mean speed.

---