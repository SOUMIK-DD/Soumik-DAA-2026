# Application of Sorting-II

## Problem Statement

Given two sets `S1` and `S2`, each containing `n` elements, and a number `x`, determine whether there exists a pair of elements such that:

```text
a + b = x
```

where:

- `a` belongs to `S1`
- `b` belongs to `S2`

Design an **O(n log n)** algorithm and write a C program to validate the algorithm.

---

## Aim

To determine whether there exists a pair of elements, one from `S1` and one from `S2`, whose sum is equal to the given number `x`, using an **O(n log n)** sorting-based algorithm.

---

## Algorithm

We use the **sorting + binary search** approach.

### Steps

1. Read the `n` elements of `S1`.
2. Read the `n` elements of `S2`.
3. Sort `S2` in ascending order.
4. For every element `a` in `S1`:
   - Calculate the required value:
     ```text
     target = x - a
     ```
   - Perform a binary search for `target` in sorted `S2`.
5. If the target is found, a valid pair exists.
6. If all elements of `S1` are checked and no target is found, no such pair exists.

---

## Pseudocode

```text
ALGORITHM FindPair(S1, S2, n, x)

    Sort S2 in ascending order

    FOR i = 0 TO n - 1

        target = x - S1[i]

        IF BinarySearch(S2, n, target) = TRUE
            RETURN TRUE

    RETURN FALSE
```

### Binary Search

```text
ALGORITHM BinarySearch(A, n, target)

    low = 0
    high = n - 1

    WHILE low <= high

        mid = low + (high - low) / 2

        IF A[mid] = target
            RETURN TRUE

        ELSE IF A[mid] < target
            low = mid + 1

        ELSE
            high = mid - 1

    RETURN FALSE
```

---

## Example

Consider:

```text
S1 = {2, 4, 7, 9}
S2 = {1, 3, 5, 8}
x = 10
```

First, sort `S2`:

```text
S2 = {1, 3, 5, 8}
```

Now check elements of `S1`.

For `a = 2`:

```text
target = 10 - 2
       = 8
```

Binary search finds `8` in `S2`.

Therefore:

```text
2 + 8 = 10
```

A valid pair exists.

### Output

```text
Pair exists.
Pair: (2, 8)
```

---

## Correctness

For every element `a` in `S1`, the algorithm searches for:

```text
x - a
```

in `S2`.

If this value is found, then:

```text
a + (x - a) = x
```

Therefore, a valid pair exists.

Conversely, suppose a valid pair exists:

```text
a + b = x
```

where `a ∈ S1` and `b ∈ S2`.

When the algorithm processes `a`, it calculates:

```text
x - a = b
```

Since `b` belongs to `S2`, binary search will find it.

Therefore, the algorithm returns `TRUE`.

Hence, the algorithm correctly determines whether such a pair exists.

---

## Time Complexity Analysis

Let `n` be the number of elements in each set.

### Step 1: Sorting S2

We sort `S2` using `qsort()`.

The sorting complexity is:

```text
O(n log n)
```

### Step 2: Traversing S1

We examine every element of `S1`.

Number of elements:

```text
n
```

Therefore:

```text
O(n)
```

### Step 3: Binary Search

For every element of `S1`, we perform one binary search on `S2`.

A binary search takes:

```text
O(log n)
```

Since there are `n` elements:

```text
n × O(log n)
= O(n log n)
```

### Total Complexity

Therefore:

```text
T(n) = O(n log n) + O(n) + O(n log n)

     = O(n log n)
```

Since `n log n` dominates `n`:

```text
Final Time Complexity = O(n log n)
```

---

## Best, Average and Worst Case

### Best Case

The first element of `S1` finds its required pair immediately.

However, `S2` still needs to be sorted.

```text
O(n log n)
```

### Average Case

We perform binary searches for approximately `n` elements.

```text
O(n log n)
```

### Worst Case

No pair exists, so all `n` elements require binary search.

```text
O(n log n)
```

Therefore:

| Case | Time Complexity |
|---|---:|
| Best Case | O(n log n) |
| Average Case | O(n log n) |
| Worst Case | O(n log n) |

---

## Space Complexity

The program stores:

- `S1` → `O(n)`
- `S2` → `O(n)`

Therefore, the total auxiliary/input storage is:

```text
O(n)
```

The iterative binary search uses:

```text
O(1)
```

additional space.

Thus:

```text
Space Complexity = O(n)
```

---

## C Program

```c
#include <stdio.h>
#include <stdlib.h>

/* Comparator function for qsort() */
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

/* Binary Search */
int binarySearch(int arr[], int n, int target)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target)
        {
            return 1;
        }
        else if (arr[mid] < target)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return 0;
}

int main()
{
    int n, x;

    printf("Enter the size of the sets: ");
    scanf("%d", &n);

    int S1[n];
    int S2[n];

    printf("\nEnter elements of S1:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &S1[i]);
    }

    printf("\nEnter elements of S2:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &S2[i]);
    }

    printf("\nEnter value of x: ");
    scanf("%d", &x);

    /* Sort S2 */
    qsort(S2, n, sizeof(int), compare);

    /* Search for a valid pair */
    int found = 0;

    for (int i = 0; i < n; i++)
    {
        int target = x - S1[i];

        if (binarySearch(S2, n, target))
        {
            printf("\nPair exists.\n");
            printf("Pair: (%d, %d)\n", S1[i], target);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nNo pair exists whose sum is %d.\n", x);
    }

    return 0;
}
```

---

## Sample Input

```text
Enter the size of the sets: 4

Enter elements of S1:
2 4 7 9

Enter elements of S2:
1 3 5 8

Enter value of x: 10
```

## Sample Output

```text
Pair exists.
Pair: (2, 8)
```

---

## Sample Input 2

```text
Enter the size of the sets: 5

Enter elements of S1:
1 4 6 8 10

Enter elements of S2:
2 3 5 7 9

Enter value of x: 20
```

## Sample Output

```text
No pair exists whose sum is 20.
```

---

## Complexity Summary

| Operation | Complexity |
|---|---:|
| Sort `S2` | O(n log n) |
| Traverse `S1` | O(n) |
| Binary searches | O(n log n) |
| **Total Time** | **O(n log n)** |
| **Space Complexity** | **O(n)** |

---

## Why Sorting Is Used

Without sorting, searching for the required element in `S2` would require a linear search for every element of `S1`:

```text
n × n = O(n²)
```

By sorting `S2` once, binary search can be used:

```text
Sorting       → O(n log n)
n searches    → O(n log n)
Total         → O(n log n)
```

Therefore, sorting reduces the overall complexity from **O(n²)** to **O(n log n)**.

---

## Conclusion

The problem can be solved efficiently by sorting one set and applying binary search.

For every element `a` in `S1`, we search for:

```text
x - a
```

in the sorted `S2`.

The algorithm correctly identifies whether a pair exists and achieves the required **O(n log n)** time complexity with **O(n)** space complexity.