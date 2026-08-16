# Multiplying Special-Pattern Matrices in O(n²) — Divide & Conquer

Two `n x n` matrices (`n = 2^k`) are given, each with the recursive
block structure

```
        | M1  M2 |
   M =  |        |
        | M2  M1 |
```

where `M1` and `M2` are themselves `(n/2) x (n/2)` matrices with the
**same** recursive pattern, all the way down to `1 x 1` scalars.

Goal: multiply two such matrices in **O(n²)** time — much better than
the `O(n³)` naive bound and even better than Strassen's `O(n^2.807)`,
by exploiting the special structure.

---

## 1. Files

| File                 | Purpose                                             |
|----------------------|-------------------------------------------------------|
| `special_matmul.c`   | Full C source: builds valid inputs, multiplies, validates against brute force, times both |
| `README.md`          | This document                                          |

---

## 2. Key Structural Insight

### 2.1 The product of two special matrices is again special

Let

```
A = | A1  A2 |        B = | B1  B2 |
    | A2  A1 |            | B2  B1 |
```

Multiply as ordinary 2×2 block matrices:

```
AB = | A1B1+A2B2   A1B2+A2B1 |
     | A2B1+A1B2   A2B2+A1B1 |
```

Define `C1 = A1B1 + A2B2` and `C2 = A1B2 + A2B1`. Then:

- top-left     = `C1`
- top-right    = `C2`
- bottom-left  = `A2B1 + A1B2 = C2`  (addition commutes)
- bottom-right = `A2B2 + A1B1 = C1`

So

```
AB = | C1  C2 |
     | C2  C1 |
```

**The product has exactly the same special pattern.** This closure
property is what makes a clean recursive algorithm possible: we never
need to touch a "generic" unpatterned matrix except transiently.

Also note: if `X` and `Y` are both special-pattern matrices, `X + Y`
and `X - Y` are trivially special-pattern too (block-wise sum/difference
of two symmetric-under-swap block matrices retains the symmetry).

### 2.2 Naive recursive count: 4 multiplications (not enough)

Computing `C1 = A1B1+A2B2` and `C2 = A1B2+A2B1` directly needs 4
half-size multiplications: `A1B1, A2B2, A1B2, A2B1`. Recurrence:

```
T(n) = 4T(n/2) + O(n^2)
```

By the Master theorem (`a=4, b=2, d=2`, `log_b a = 2 = d`):

```
T(n) = O(n^2 log n)      <-- NOT O(n^2). Not good enough.
```

### 2.3 The Karatsuba-style trick: only 3 multiplications

Just like Karatsuba's trick for multiplying two 2-term expressions
with 3 products instead of 4, define:

```
P1 = A1 * B1
P2 = A2 * B2
P3 = (A1 + A2) * (B1 + B2)
```

Expand `P3`:

```
P3 = A1B1 + A1B2 + A2B1 + A2B2 = (A1B1 + A2B2) + (A1B2 + A2B1)
   = C1 + C2
```

So:

```
C1 = P1 + P2
C2 = P3 - C1        (= P3 - P1 - P2)
```

Only **3** recursive multiplications are required:
`P1 = A1*B1`, `P2 = A2*B2`, `P3 = (A1+A2)*(B1+B2)` — and crucially,
`A1+A2` and `B1+B2` are themselves special-pattern matrices of size
`n/2`, so `P3` is a valid recursive call of the *same* algorithm.

---

## 3. The Algorithm

### 3.1 Pseudocode

```
function SPECIAL-MULTIPLY(A, B, n):
    if n == 1:
        return [ A[0][0] * B[0][0] ]

    half = n / 2
    A1 = top-left  half x half block of A
    A2 = top-right half x half block of A
    B1 = top-left  half x half block of B
    B2 = top-right half x half block of B

    SA = A1 + A2                      # O(half^2), still special-pattern
    SB = B1 + B2                      # O(half^2), still special-pattern

    P1 = SPECIAL-MULTIPLY(A1, B1, half)
    P2 = SPECIAL-MULTIPLY(A2, B2, half)
    P3 = SPECIAL-MULTIPLY(SA, SB, half)

    C1 = P1 + P2                      # O(half^2)
    C2 = P3 - C1                      # O(half^2)

    C = | C1  C2 |                    # O(n^2) to assemble
        | C2  C1 |

    return C
```

Base case `n = 1`: multiplying two scalars, `O(1)`.

### 3.2 Why only the top blocks are needed

Because `M2` already appears in *both* off-diagonal positions and
`M1` in both diagonal positions, the bottom half of the input matrix
carries no new information — `A1` and `A2` (extracted once, from the
top half) fully determine `A`. The algorithm therefore only ever
reads/derives from the top-left and top-right quadrants at each
level.

### 3.3 A nice corollary — information content

Let `f(n)` = number of independent scalar entries needed to fully
specify a special-pattern `n x n` matrix. Since the matrix is
determined by two `(n/2) x (n/2)` special matrices:

```
f(n) = 2 f(n/2),    f(1) = 1     =>     f(n) = n
```

So an `n x n` special matrix really only carries **n** degrees of
freedom (not `n²`) — this is analogous to a circulant matrix being
fully determined by one row. `special_matmul.c` uses this fact: the
program builds a guaranteed-valid input matrix from just `n` numbers
(function `buildSpecialFromSeq`), recursively expanding them into the
full `n x n` array.

---

## 4. Complexity Analysis

### 4.1 Recurrence

Per level of recursion: 3 recursive calls on size `n/2`, plus a
constant number of `O(n^2)`-time matrix additions/subtractions
(computing `SA`, `SB`, `C1`, `C2`) and an `O(n^2)` assembly step:

```
T(n) = 3 T(n/2) + O(n^2),    T(1) = O(1)
```

### 4.2 Solving with the Master Theorem

Master form `T(n) = a T(n/b) + O(n^d)` with `a = 3`, `b = 2`, `d = 2`.

Compare `d` to `log_b(a) = log2(3) ≈ 1.585`:

```
d = 2  >  log2(3) ≈ 1.585
```

Since the top level dominates (case 3 of the Master theorem):

```
T(n) = O(n^d) = O(n^2)
```

### 4.3 Verifying by unrolling the recurrence directly

```
T(n) = c*n^2 + 3*T(n/2)
     = c*n^2 + 3[c*(n/2)^2 + 3*T(n/4)]
     = c*n^2 + 3c*(n/2)^2 + 9c*(n/4)^2 + ... + 3^k * c * (n/2^k)^2   (k = log2 n)
     = c*n^2 * sum_{i=0}^{k} (3/4)^i
```

`sum_{i=0}^{∞} (3/4)^i = 1/(1 - 3/4) = 4` (convergent geometric series,
since `3/4 < 1`), so:

```
T(n) <= 4c*n^2 = O(n^2)
```

This confirms the O(n²) bound rigorously — the work strictly
*decreases* geometrically as recursion depth increases (each level
does `3/4` of the previous level's work), so the **top level alone
already accounts for a constant fraction of the total cost**.

### 4.4 Complexity comparison

| Algorithm                              | Time         |
|------------------------------------------|--------------|
| Naive (ignores structure)                 | `O(n^3)`     |
| Strassen (ignores structure, general case)| `O(n^2.807)` |
| **This algorithm (exploits structure)**   | **`O(n^2)`** |

`O(n^2)` is also **optimal up to constant factors**: just *writing
out* the `n x n` output matrix takes `Ω(n^2)` time, so no algorithm
that outputs the full matrix can beat `O(n^2)`.

### 4.5 Space complexity

- Each level allocates `O(n^2)` auxiliary space (blocks, sums, the
  assembled output), and, exactly as with the time recurrence, this
  telescopes to `O(n^2)` total: `S(n) = 3S(n/2) + O(n^2) = O(n^2)`.
- Using the length-`n` generating-sequence representation from
  §3.3, both **input** matrices can be stored in `O(n)` space instead
  of `O(n^2)` — a nice practical optimization not required by the
  problem but implemented in the demo program for convenience.

---

## 5. Correctness

The algorithm's correctness follows directly from the two identities
proved in §2:

1. `AB` retains the special pattern (§2.1) — so the recursive
   "shape" of the problem is preserved at every level, which is a
   prerequisite for the recursion to even type-check.
2. `C1 = P1+P2` and `C2 = P3-P1-P2` correctly reproduce
   `A1B1+A2B2` and `A1B2+A2B1` respectively (§2.3) — verified purely
   by algebraic expansion, independent of `n`.

Combined with a correct base case (`n=1`, scalar multiply), induction
on `k` (where `n = 2^k`) gives full correctness for all `n`.

`special_matmul.c` also includes a **runtime self-check**: it builds
matrices guaranteed to satisfy the pattern, runs both the D&C
algorithm and a brute-force `O(n^3)` multiply, and prints whether the
two results match — confirmed for `n = 1, 2, 4, 8, 16, ...` during
testing.

---

## 6. Build & Run

```bash
gcc -O2 -o special_matmul special_matmul.c
./special_matmul
```

Example (`n = 8`):

```
Enter n (power of 2): 8
Enter 8 generating values for matrix A (defines it fully): 1 2 3 4 5 6 7 8
Enter 8 generating values for matrix B (defines it fully): 8 7 6 5 4 3 2 1

Matrix A (n=8):
    1     2     3     4     5     6     7     8
    2     1     4     3     6     5     8     7
    3     4     1     2     7     8     5     6
    4     3     2     1     8     7     6     5
    5     6     7     8     1     2     3     4
    6     5     8     7     2     1     4     3
    7     8     5     6     3     4     1     2
    8     7     6     5     4     3     2     1

Pattern check A: valid
Pattern check B: valid

Product C = A x B (Divide & Conquer, O(n^2)):
  120   124   136   140   184   188   200   204
  124   120   140   136   188   184   204   200
  136   140   120   124   200   204   184   188
  140   136   124   120   204   200   188   184
  184   188   200   204   120   124   136   140
  188   184   204   200   124   120   140   136
  200   204   184   188   136   140   120   124
  204   200   188   184   140   136   124   120

Matches brute-force O(n^3) result: YES
```

---

## 7. Code Structure (`special_matmul.c`)

| Function                 | Role                                                                 |
|----------------------------|-----------------------------------------------------------------------|
| `allocMatrix` / `freeMatrix` | Dynamic memory for `int**` matrices                                  |
| `addMat` / `subMat`        | `O(n^2)` element-wise add/subtract                                   |
| `getBlock` / `setBlock`    | Extract / write an `n/2 x n/2` quadrant                              |
| `buildSpecialFromSeq`      | Build a valid `n x n` special matrix from its `n` generating values  |
| `verifyPattern`            | Recursively confirms a matrix truly satisfies the pattern (`O(n^2)`) |
| `specialMultiply`          | **The main O(n²) algorithm** (3-multiplication recursion)            |
| `naiveMultiply`             | Brute-force `O(n^3)` reference implementation, for validation        |
| `matricesEqual`             | Compares two matrices element-wise                                   |
| `main`                      | Reads input, builds matrices, runs both algorithms, times & validates|

---

## 8. Extensions / Notes

- The same 3-multiplication trick is the reason Karatsuba's integer
  multiplication beats grade-school multiplication — this problem is
  structurally the same idea applied to a matrix-valued "coefficient".
- If the block pattern were `[[M1, M2], [M3, M4]]` with *no* relation
  between the blocks (i.e. a general matrix, Strassen's setting),
  closure under multiplication no longer holds trivially and 7
  multiplications are needed, giving `O(n^log2 7) ≈ O(n^2.807)`
  instead of `O(n^2)` — this contrast is exactly why exploiting the
  given matrices' special structure is so much more powerful here.
- The generating-sequence trick (§3.3) generalizes: matrices whose
  recursive block pattern is invariant under a group action (here,
  the group `Z/2` acting by swapping blocks) are fully determined by
  one representative per group orbit — the same underlying idea used
  for circulant matrices and the Fast Fourier Transform.
