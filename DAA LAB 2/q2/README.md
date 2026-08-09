# 2-Way and 3-Way Merge Sort

## Problem Statement

Consider the following modification to merge sort: divide the input array into thirds (rather than halves), recursively sort each third, and finally combine the results using a three-way merge subroutine. What is the worst-case running time of this modified merge sort? Write a C program to validate your claim by plotting the order of growth for both the merge sort discussed in the class and the modified merge sort described above.

---

## 1. 2-Way Merge Sort

The input array is divided into two equal parts.

### Recurrence

T(n) = 2T(n/2) + cn

Using the substitution method, assume:

T(n) <= c₁n log₂n

Substituting:

T(n) <= 2[c₁(n/2)log₂(n/2)] + cn

T(n) <= c₁n(log₂n - 1) + cn

T(n) <= c₁n log₂n - c₁n + cn

For c₁ >= c:

T(n) <= c₁n log₂n

Therefore:

**T(n) = O(n log n)**

### Worst-Case Running Time

**O(n log n)**

---

## 2. 3-Way Merge Sort

The input array is divided into three equal parts.

### Recurrence

T(n) = 3T(n/3) + cn

Using the substitution method, assume:

T(n) <= c₁n log₃n

Substituting:

T(n) <= 3[c₁(n/3)log₃(n/3)] + cn

T(n) <= c₁n(log₃n - 1) + cn

T(n) <= c₁n log₃n - c₁n + cn

For c₁ >= c:

T(n) <= c₁n log₃n

Therefore:

**T(n) = O(n log₃n)**

Since logarithms with different constant bases differ only by a constant factor:

**O(n log₃n) = O(n log n)**

### Worst-Case Running Time

**O(n log n)**

---

## 3. Comparison

| Algorithm | Recurrence | Worst-Case Running Time |
|-----------|------------|-------------------------|
| 2-Way Merge Sort | T(n) = 2T(n/2) + O(n) | O(n log n) |
| 3-Way Merge Sort | T(n) = 3T(n/3) + O(n) | O(n log n) |

---

## 4. Experimental Validation

A C program is used to compare the order of growth of both algorithms.

The program counts the number of comparisons for different input sizes and stores the results in `data.txt`.

GNUplot is used to plot the results.

- X-axis: Input Size (n)
- Y-axis: Number of Comparisons

The graph compares the growth of 2-way and 3-way merge sort.

---

## 5. Conclusion

Using the substitution method, the worst-case running time of both algorithms is found to be:

**2-Way Merge Sort: O(n log n)**

**3-Way Merge Sort: O(n log n)**

Thus, dividing the array into three parts instead of two does not change the asymptotic order of growth.
