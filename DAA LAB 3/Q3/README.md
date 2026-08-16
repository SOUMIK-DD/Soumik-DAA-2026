# Strassen's Matrix Multiplication (Divide and Conquer)

A C implementation that multiplies two `n x n` square matrices using
**Strassen's algorithm**, a Divide-and-Conquer technique that reduces
the number of scalar multiplications needed compared to the naive
`O(n^3)` method.

---

## 1. Files

| File          | Purpose                                   |
|---------------|--------------------------------------------|
| `strassen.c`  | Full C source (algorithm + I/O + timing)  |
| `README.md`   | This document                             |

---

## 2. Problem

Given two `n x n` matrices `A` and `B`, compute `C = A x B`.

The **naive** method computes each of the `n^2` entries of `C` as a dot
product of length `n`, costing `O(n^3)` multiplications overall.

**Strassen's insight (1969):** you don't need 8 sub-multiplications to
combine 2x2 block matrices — 7 cleverly chosen products are enough,
at the cost of extra additions/subtractions (which are cheap, `O(n^2)`).

---

## 3. Algorithm

### 3.1 Divide

Split each `n x n` matrix into four `(n/2) x (n/2)` sub-matrices:

```
      | A11  A12 |         | B11  B12 |
  A = |          |     B = |          |
      | A21  A22 |         | B21  B22 |
```

### 3.2 Conquer — 7 recursive products

Instead of the 8 products the block-matrix formula naturally suggests,
Strassen computes only 7:

```
M1 = (A11 + A22) x (B11 + B22)
M2 = (A21 + A22) x  B11
M3 =  A11         x (B12 - B22)
M4 =  A22         x (B21 - B11)
M5 = (A11 + A12) x  B22
M6 = (A21 - A11) x (B11 + B12)
M7 = (A12 - A22) x (B21 + B22)
```

Each `Mi` is itself an `(n/2) x (n/2)` matrix product, computed by
**recursing** on the same function.

### 3.3 Combine

The four quadrants of the result `C` are formed using only additions
and subtractions of the `Mi`:

```
C11 = M1 + M4 - M5 + M7
C12 = M3 + M5
C21 = M2 + M4
C22 = M1 - M2 + M3 + M6
```

### 3.4 Base case

When the sub-matrix size reaches `1 x 1`, multiplication is a single
scalar multiply — recursion stops.

### 3.5 Handling non-power-of-2 sizes

Strassen's split assumes `n` is even at every level, i.e. a power of
2. For an arbitrary `n`, this program:

1. Computes `m` = the next power of 2 `>= n`.
2. Pads `A` and `B` with zero rows/columns to size `m x m`.
3. Runs Strassen's algorithm on the padded matrices.
4. Crops the resulting `m x m` product back down to `n x n`.

Padding with zeros doesn't affect the numerical result because the
extra rows/columns only ever multiply with zero.

### Pseudocode

```
function STRASSEN(A, B, n):
    if n == 1:
        return [ A[0][0] * B[0][0] ]

    split A into A11, A12, A21, A22   (each n/2 x n/2)
    split B into B11, B12, B21, B22

    M1 = STRASSEN(A11 + A22, B11 + B22, n/2)
    M2 = STRASSEN(A21 + A22, B11,       n/2)
    M3 = STRASSEN(A11,       B12 - B22, n/2)
    M4 = STRASSEN(A22,       B21 - B11, n/2)
    M5 = STRASSEN(A11 + A12, B22,       n/2)
    M6 = STRASSEN(A21 - A11, B11 + B12, n/2)
    M7 = STRASSEN(A12 - A22, B21 + B22, n/2)

    C11 = M1 + M4 - M5 + M7
    C12 = M3 + M5
    C21 = M2 + M4
    C22 = M1 - M2 + M3 + M6

    return join(C11, C12, C21, C22)
```

---

## 4. Complexity Analysis

### 4.1 Recurrence relation

Let `T(n)` be the time to multiply two `n x n` matrices.

- 7 recursive multiplications on matrices of size `n/2`.
- A constant number of matrix additions/subtractions on `n/2 x n/2`
  matrices, each costing `O((n/2)^2) = O(n^2)`.

```
T(n) = 7*T(n/2) + O(n^2),      T(1) = O(1)
```

### 4.2 Solving with the Master Theorem

Master theorem form: `T(n) = a*T(n/b) + O(n^d)` with `a = 7`, `b = 2`, `d = 2`.

Compare `d` with `log_b(a) = log2(7) ≈ 2.807`:

Since `d = 2 < log2(7)`, the recursion-tree leaves dominate, giving:

```
T(n) = O(n^(log2 7)) ≈ O(n^2.807)
```

### 4.3 Comparison table

| Method                | Time Complexity        | Approx. exponent |
|------------------------|------------------------|-------------------|
| Naive / brute force     | `O(n^3)`                | 3.000             |
| **Strassen**             | `O(n^log2(7))`          | **2.807**         |
| Coppersmith–Winograd (theoretical) | `O(n^2.376)` | 2.376 |
| Current best known (galactic, impractical) | `O(n^2.371...)` | ~2.371 |

### 4.4 Space complexity

- Each recursive call allocates `O(n^2)` extra space for sub-matrices
  (`A11..A22`, `B11..B22`, `M1..M7`, temporaries).
- Summed over all recursion levels: `O(n^2)` total auxiliary space
  (a geometric series `n^2 + (n/2)^2*4 + ... ` converges to `O(n^2)`),
  i.e. space complexity is `O(n^2)`, same order as the input itself.

### 4.5 Practical notes

- Strassen's constant factor is larger than the naive method's, and
  the extra additions/subtractions add real overhead. For small `n`
  (typically below ~64), the naive `O(n^3)` method is often *faster*
  in wall-clock time. Production implementations usually switch to
  naive multiplication below some threshold (a "hybrid" approach).
- Strassen's algorithm has a larger memory footprint due to the many
  temporary matrices created at each level of recursion.
- Numerically, Strassen's algorithm is slightly less stable than the
  naive method because of the extra additions/subtractions, though
  this rarely matters for integer matrices.
- This implementation pads to the next power of 2, which is simple
  but can waste up to ~4x work in the worst case (e.g. `n = 2^k + 1`).
  A tighter implementation would only recurse down to a fixed
  crossover size and use naive multiplication for the odd leftover
  rows/columns.

---

## 5. Build & Run

```bash
gcc -O2 -o strassen strassen.c
./strassen
```

Example session (`n = 3`):

```
Enter size of square matrices (n): 3
Enter elements of matrix A (3 x 3), row by row:
1 2 3
4 5 6
7 8 9
Enter elements of matrix B (3 x 3), row by row:
9 8 7
6 5 4
3 2 1

Matrix A:
     1      2      3
     4      5      6
     7      8      9

Matrix B:
     9      8      7
     6      5      4
     3      2      1

Product C = A x B (via Strassen's algorithm):
    30     24     18
    84     69     54
   138    114     90

Time taken: 0.000018 seconds
```

---

## 6. Code Structure (`strassen.c`)

| Function                | Role                                                       |
|--------------------------|-------------------------------------------------------------|
| `allocateMatrix`/`freeMatrix` | Dynamic memory management for `int**` matrices        |
| `addMatrix`/`subMatrix`   | `O(n^2)` element-wise add/subtract                         |
| `splitMatrix`/`joinMatrix`| Break a matrix into 4 quadrants / reassemble them          |
| `strassenMultiply`        | The core recursive D&C algorithm (7 products)              |
| `nextPowerOfTwo`, `padMatrix`, `cropMatrix` | Handle arbitrary `n` by padding/cropping |
| `multiply`                | Public wrapper: pads if needed, then calls `strassenMultiply` |
| `main`                    | Reads `A`, `B` from stdin, multiplies, prints result + timing |

---

## 7. Possible Extensions

- Add a crossover threshold (e.g. switch to naive multiplication for `n <= 32`) to speed up real-world performance.
- Support non-square / rectangular matrices via padding to the same square size.
- Use `double` instead of `int` for floating-point matrices.
- Parallelize the 7 recursive calls with threads (they are independent of each other).
