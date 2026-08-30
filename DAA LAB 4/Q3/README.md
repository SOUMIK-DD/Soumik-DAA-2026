# Application of Sorting-III

## Problem Statement

Given a set `S` containing `n` integers and an integer `T`, design an algorithm to determine whether there exist **`k` integers** in `S` whose sum is equal to `T`.

The required time complexity is:

```text
O(n^(k-1) · log n)
```

By choosing a suitable input representation, write a C program to validate the algorithm.

---

## Aim

To determine whether any `k` distinct integers from a set `S` add up to a given target `T`, using sorting and binary search in:

```text
O(n^(k-1) log n)
```

time.

---

## Key Idea

The main idea is to:

1. Sort the set `S`.
2. Select `k - 1` elements using nested loops/recursion.
3. Calculate the required remaining value.
4. Use **binary search** to check whether that remaining value exists in `S`.

Suppose we have selected:

```text
a1 + a2 + ... + a(k-1)
```

Then the required final element is:

```text
required = T - (a1 + a2 + ... + a(k-1))
```

We search for `required` in the sorted set.

If it exists and is different from the already selected elements, then `k` integers with sum `T` exist.

---

## Algorithm

### Step-by-Step

1. Sort the set `S` in ascending order.
2. Recursively select `k - 1` different elements from `S`.
3. Maintain their sum.
4. Once `k - 1` elements have been selected:
   - Calculate:
     ```text
     required = T - currentSum
     ```
5. Perform binary search for `required` in the sorted array.
6. Make sure the found element is not one of the already selected elements.
7. If found, return `TRUE`.
8. If every possible combination of `k - 1` elements has been checked without finding a match, return `FALSE`.

---

## Pseudocode

```text
ALGORITHM KSum(S, n, k, T)

    Sort S in ascending order

    RETURN Search(S, n, k, T, 0, 0)


ALGORITHM Search(S, n, k, T, start, currentSum)

    IF k = 1

        required = T - currentSum

        IF BinarySearch(S, required) exists
            RETURN TRUE

        RETURN FALSE


    FOR i = start TO n - k

        IF Search(S, n, k - 1, T,
                  i + 1,
                  currentSum + S[i]) = TRUE

            RETURN TRUE

    RETURN FALSE
```

---

## Binary Search

Since `S` is sorted, binary search is used to find the required final element.

```text
ALGORITHM BinarySearch(S, n, target)

    low = 0
    high = n - 1

    WHILE low <= high

        mid = low + (high - low) / 2

        IF S[mid] = target
            RETURN TRUE

        ELSE IF S[mid] < target
            low = mid + 1

        ELSE
            high = mid - 1

    RETURN FALSE
```

---

## Example

Consider:

```text
S = {2, 4, 6, 8, 10}
T = 18
k = 3
```

We need to determine whether any three numbers add up to `18`.

Sort the set:

```text
S = {2, 4, 6, 8, 10}
```

Select two elements.

Suppose:

```text
2 + 6 = 8
```

The required third element is:

```text
required = 18 - 8
         = 10
```

Binary search finds `10`.

Therefore:

```text
2 + 6 + 10 = 18
```

Hence, a valid combination exists.

### Output

```text
A combination exists.
2 + 6 + 10 = 18
```

---

## Another Example

Consider:

```text
S = {1, 3, 5, 7, 9}
T = 20
k = 3
```

Try:

```text
1 + 3 = 4
required = 16
```

`16` does not exist.

Try:

```text
1 + 5 = 6
required = 14
```

Not found.

Try:

```text
1 + 7 = 8
required = 12
```

Not found.

Continue for all possible pairs.

If no required value is found:

```text
No combination exists.
```

---

## Correctness

The algorithm considers every possible selection of `k - 1` elements from the set.

For each selected set:

```text
a1 + a2 + ... + a(k-1)
```

it calculates:

```text
required = T - (a1 + a2 + ... + a(k-1))
```

If `required` exists in `S` and has not already been selected, then:

```text
a1 + a2 + ... + a(k-1) + required = T
```

Therefore, a valid set of `k` integers has been found.

Conversely, suppose there exists a valid combination:

```text
a1 + a2 + ... + ak = T
```

The recursive algorithm eventually selects the first `k - 1` elements. At that point:

```text
required = T - (a1 + a2 + ... + a(k-1))
```

which is exactly `ak`.

Binary search will find `ak` in the sorted set.

Therefore, the algorithm will return `TRUE`.

Hence, the algorithm is correct.

---

# Time Complexity Analysis

The required complexity is:

```text
O(n^(k-1) log n)
```

### Step 1: Sorting

Sorting the `n` integers requires:

```text
O(n log n)
```

time.

### Step 2: Selecting `k - 1` Elements

The algorithm explores combinations of `k - 1` elements.

The number of possible selections is approximately:

```text
n^(k-1)
```

For a fixed `k`, this gives:

```text
O(n^(k-1))
```

possibilities.

### Step 3: Binary Search

For every selection of `k - 1` elements, we perform one binary search.

Binary search takes:

```text
O(log n)
```

time.

Therefore:

```text
O(n^(k-1)) × O(log n)
```

which gives:

```text
O(n^(k-1) log n)
```

### Total Complexity

Including sorting:

```text
T(n) = O(n log n) + O(n^(k-1) log n)
```

For `k >= 2`:

```text
O(n^(k-1) log n)
```

dominates the sorting term.

Therefore:

```text
┌──────────────────────────────┐
│ Time Complexity              │
│ O(n^(k-1) · log n)           │
└──────────────────────────────┘
```





---

## Complexity for Different Values of k

The general complexity is:

```text
O(n^(k-1) log n)
```

For example:

| k | Complexity |
|---:|---:|
| 2 | O(n log n) |
| 3 | O(n² log n) |
| 4 | O(n³ log n) |
| 5 | O(n⁴ log n) |
| k | O(n^(k-1) log n) |

For `k = 3`, for example:

```text
O(n^(3-1) log n)
= O(n² log n)
```

---

## Space Complexity

The array containing the set requires:

```text
O(n)
```

The recursive function has a maximum depth of `k`.

Since `k` is normally treated as a fixed constant:

```text
O(k) = O(1)
```

additional recursion space is used.

Therefore, the overall space complexity is:

```text
O(n)
```

---

# C Program

```c
#include <stdio.h>
#include <stdlib.h>

/* Compare function for qsort */
int compare(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y)
        return -1;
    else if (x > y)
        return 1;
    else
        return 0;
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
            return mid;

        if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

/*
    Recursive function to find k elements
    whose sum is equal to target.

    start      -> index from which elements can be selected
    currentSum -> sum of already selected elements
    depth      -> number of elements selected
*/
int findKSum(int arr[], int n, int k, int target,
            int start, int currentSum)
{
    /* When k-1 elements are selected,
       search for the final required element. */
    if (k == 1)
    {
        int required = target - currentSum;

        int pos = binarySearch(arr, n, required);

        if (pos == -1)
            return 0;

        /*
            The binary search may find an element that
            was already selected. Since the input is a set
            of distinct elements, check that the element
            occurs after the selected range.
        */

        if (pos < start)
            return 0;

        return 1;
    }

    /*
        Select one element and recursively
        select the remaining elements.
    */
    for (int i = start; i <= n - k; i++)
    {
        if (findKSum(arr, n, k - 1, target,
                    i + 1,
                    currentSum + arr[i]))
        {
            return 1;
        }
    }

    return 0;
}

int main()
{
    int n, k, T;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int S[n];

    printf("Enter the elements of the set:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &S[i]);
    }

    printf("Enter the value of k: ");
    scanf("%d", &k);

    printf("Enter the target T: ");
    scanf("%d", &T);

    /* Validate k */
    if (k <= 0 || k > n)
    {
        printf("\nInvalid value of k.\n");
        return 1;
    }

    /* Sort the set */
    qsort(S, n, sizeof(int), compare);

    /* Search for k elements */
    if (findKSum(S, n, k, T, 0, 0))
    {
        printf("\nYES\n");
        printf("There exist %d elements whose sum is %d.\n",
               k, T);
    }
    else
    {
        printf("\nNO\n");
        printf("No %d elements have sum %d.\n",
               k, T);
    }

    return 0;
}
```

---

# Sample Input 1

```text
Enter the number of elements: 5

Enter the elements of the set:
2 4 6 8 10

Enter the value of k: 3

Enter the target T: 18
```

## Sample Output

```text
YES
There exist 3 elements whose sum is 18.
```

One such combination is:

```text
2 + 6 + 10 = 18
```

---

# Sample Input 2

```text
Enter the number of elements: 6

Enter the elements of the set:
1 3 5 7 9 11

Enter the value of k: 3

Enter the target T: 20
```

## Sample Output

```text
NO
No 3 elements have sum 20.
```

---

# Complexity Summary

| Operation | Complexity |
|---|---:|
| Sorting | O(n log n) |
| Selecting `k-1` elements | O(n^(k-1)) |
| Binary search for each selection | O(log n) |
| **Total Time** | **O(n^(k-1) log n)** |
| **Space Complexity** | **O(n)** |

---

## Important Observation

The algorithm avoids checking every possible combination of `k` elements.

A direct brute-force approach would require approximately:

```text
O(n^k)
```

operations.

Instead, we select only `k - 1` elements and use binary search to find the final element:

```text
Select k-1 elements
        ↓
Calculate required value
        ↓
Binary search in sorted S
        ↓
Found? → YES
Not found? → Continue
```

This reduces the required complexity to:

```text
O(n^(k-1) log n)
```

---

## Conclusion

By first sorting the set and then selecting `k - 1` elements, the required `k`th element can be calculated directly:

```text
required = T - currentSum
```

Binary search is then used to determine whether the required element exists.

Therefore, the algorithm successfully tests whether `k` integers in `S` add up to `T` in:

```text
O(n^(k-1) log n)
```

time and uses:

```text
O(n)
```

space.