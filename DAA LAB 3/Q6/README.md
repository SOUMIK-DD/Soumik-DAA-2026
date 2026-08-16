# Loop Invariants in Sorting — Selection Sort

This README accompanies `Q6.c`, which implements the sorting algorithm
described below: repeatedly find the smallest element of the
unsorted suffix of the array and swap it into its correct position.
This is the classic **Selection Sort** algorithm.

---

## 1. The Algorithm in Words

1. Find the smallest element of `A[1..n]`, exchange it with `A[1]`.
2. Find the smallest element of `A[2..n]`, exchange it with `A[2]`.
3. Find the smallest element of `A[3..n]`, exchange it with `A[3]`.
4. Continue this way for the first `n - 1` elements of `A`.

Each pass shrinks the "unsorted region" by one element and grows the
"sorted region" by one element, always picking the globally smallest
remaining value to extend the sorted region.

---

## 2. Pseudocode

```
SELECTION-SORT(A, n)
    for i = 1 to n - 1
        min_index = i
        for j = i + 1 to n
            if A[j] < A[min_index]
                min_index = j
        exchange A[i] with A[min_index]
```

(1-indexed, matching the problem statement's `A[1 .. n]` convention.)

---

## 3. Loop Invariant

**Invariant (for the outer `for` loop, at the start of each iteration
indexed by `i`):**

> The subarray `A[1 .. i-1]` consists of the `i - 1` smallest elements
> of the original array `A[1 .. n]`, sorted in non-decreasing order.

Equivalently: at the start of iteration `i`, `A[1..i-1]` is sorted, and
every element in `A[1..i-1]` is `≤` every element in `A[i..n]`.

### 3.1 Initialization

Before the first iteration, `i = 1`, so the subarray `A[1..i-1] = A[1..0]`
is **empty**. An empty subarray is trivially sorted, and the invariant
("the `i-1 = 0` smallest elements, sorted") holds vacuously.

### 3.2 Maintenance

Assume the invariant holds at the start of iteration `i`: `A[1..i-1]`
holds the `i-1` smallest elements of `A`, sorted, and all of them are
`≤` every element in `A[i..n]`.

Within iteration `i`, the inner loop scans `A[i..n]` and finds
`min_index`, the index of the smallest element in that range. Since
by the invariant every element of `A[1..i-1]` is already `≤` every
element of `A[i..n]`, this newly found minimum of `A[i..n]` is in fact
the smallest element of the **entire remaining unsorted array**, i.e.
it is the `i`-th smallest element overall.

Swapping `A[i]` and `A[min_index]` places this `i`-th smallest element
into position `i`. Now `A[1..i]` consists of the `i` smallest elements
of `A`, still sorted (since the new element is `≥` everything already
in `A[1..i-1]`, by the same "already ≤ everything in the suffix"
property). Incrementing `i` for the next iteration, the invariant
again holds — now with `i-1` replaced by the new, larger `i-1`.

### 3.3 Termination

The outer loop terminates when `i = n` (i.e. it exits after processing
`i = n - 1`). At that point the invariant states: `A[1 .. n-1]`
consists of the `n - 1` smallest elements of `A`, sorted, and every
element of `A[1..n-1]` is `≤` the one remaining element `A[n]`.

Since `A[1..n-1]` holds the `n-1` smallest elements in sorted order
and `A[n]` (the single remaining, and therefore largest, element) is
`≥` all of them, the **entire array** `A[1..n]` is sorted. This is
exactly what we needed to prove — the loop invariant, combined with
the reason the loop terminates, directly establishes the algorithm's
correctness.

---

## 4. Why Only the First `n - 1` Elements?

After the `(n-1)`-th iteration completes, `A[1 .. n-1]` contains the
`n - 1` smallest elements in sorted order, and by elimination the
single element left at `A[n]` must be the **largest** element of the
whole array — it is already exactly where it needs to be.

Running one more iteration for `i = n` would search `A[n..n]`, a
single-element range, find `min_index = n` trivially, and swap `A[n]`
with itself — a wasted no-op comparison-free pass that cannot change
anything. So the algorithm correctly (and efficiently) stops at
`i = n - 1`.

---

## 5. Running Time

### 5.1 Counting comparisons

The inner loop, for a given outer index `i`, performs `n - i`
comparisons (comparing each element of `A[i+1 .. n]` against the
current minimum). Total comparisons across all outer iterations:

```
sum_{i=1}^{n-1} (n - i)  =  (n-1) + (n-2) + ... + 1  =  n(n-1)/2
```

### 5.2 Worst-case running time

The inner loop always runs the same number of times regardless of the
data — it must inspect every remaining element to be sure it has
found the true minimum, no matter what order the input is in. So:

```
T(n) = Θ(n(n-1)/2) = Θ(n^2)
```

**Worst-case running time: Θ(n²).**

### 5.3 Best-case running time

Unlike algorithms such as insertion sort or bubble sort (which can
detect an already-sorted array and finish early, giving them a
better best case), **selection sort's inner loop always scans the
entire remaining unsorted suffix to find the minimum** — it has no
way to know it has found the minimum without checking every
candidate, even if the array is already perfectly sorted.

So the number of *comparisons* is always exactly `n(n-1)/2`,
regardless of input order — **best case = worst case = average case
= Θ(n²)**.

(The only thing that can vary with input is the number of *swaps*:
in the best case, an already-sorted array needs 0 swaps, since
`min_index` always equals `i` already; in the worst case it can need
up to `n - 1` swaps. But since each swap is `O(1)` and swaps don't
dominate the `Θ(n²)` comparison cost, this does **not** change the
overall asymptotic running time.)

**Conclusion: the best-case running time is NOT asymptotically better
— it is also Θ(n²).** This is a key structural difference from, e.g.,
insertion sort, whose best case is Θ(n).

### 5.4 Summary table

| Case     | Comparisons  | Swaps        | Running Time |
|----------|--------------|--------------|--------------|
| Best      | `n(n-1)/2`   | `0`          | `Θ(n²)`      |
| Average   | `n(n-1)/2`   | `Θ(n)`       | `Θ(n²)`      |
| Worst     | `n(n-1)/2`   | `n - 1`      | `Θ(n²)`      |

---

## 6. Validating the Claim (`Q6.c`)

`Q6.c` implements the pseudocode above in C. To empirically confirm
the Θ(n²) claim and the loop invariant:

1. **Correctness check**: run the program on random arrays and
   confirm the output is sorted (e.g. by comparing against a
   library `qsort` result, or simply checking `A[i] <= A[i+1]` for
   all `i`).
2. **Loop invariant check**: after each outer iteration `i`, print
   `A[1..i]` and confirm it is (a) sorted and (b) that every element
   in it is `≤` every remaining element in `A[i+1..n]` — this
   directly demonstrates the invariant from §3 holding at every step.
3. **Comparison counting**: instrument the inner loop with a counter
   and confirm the total matches `n(n-1)/2` exactly for every input
   (since, per §5.3, this count never depends on the data).
4. **Timing sweep**: run with increasing `n` (e.g. doubling each
   time: 500, 1000, 2000, 4000, ...) and confirm the measured time
   roughly quadruples each time `n` doubles — the empirical signature
   of `Θ(n²)` growth.

### Build & run

```bash
gcc -O2 -o Q6 Q6.c
./Q6
```

(Refer to `Q6.c` itself for the exact input format / prompts used in
this implementation.)

---

## 7. Key Takeaways

- The loop invariant *is* the proof of correctness: initialization
  gives a true base case, maintenance shows each iteration preserves
  the property, and termination shows the final state implies the
  desired postcondition (the whole array sorted).
- Selection sort needs only `n - 1` (not `n`) outer iterations because
  the last remaining element is forced into its correct position by
  elimination.
- Selection sort's running time is `Θ(n²)` in **every** case (best,
  average, and worst) because the number of comparisons is
  data-independent — this is what distinguishes it from adaptive
  sorts like insertion sort.
