# Application of Sorting-V

## Problem Statement

Given a list `I` of `n` intervals, where each interval is represented as:

```text
(xi, yi)
```

merge all overlapping intervals and return the resulting list of non-overlapping intervals.

For example:

```text
I = {(1,3), (2,6), (8,10), (7,18)}
```

The output should be:

```text
{(1,6), (7,18)}
```

The algorithm must run in **worst-case O(n log n)** time.

---

## Aim

To merge all overlapping intervals using a sorting-based approach with a worst-case time complexity of:

```text
O(n log n)
```

---

## Key Idea

The main idea is to **sort the intervals according to their starting point**.

Once sorted, overlapping intervals will appear next to each other.

For every interval, compare its starting point with the ending point of the current merged interval.

If:

```text
next.start <= current.end
```

the two intervals overlap, so extend the current interval:

```text
current.end = max(current.end, next.end)
```

Otherwise, the current interval is complete and can be added to the output.

---

## Algorithm

### Step 1: Sort Intervals

Sort all intervals in ascending order based on their starting points.

For example:

```text
Input:
(1,3), (2,6), (8,10), (7,18)
```

After sorting:

```text
(1,3), (2,6), (7,18), (8,10)
```

### Step 2: Initialize

Take the first interval as the current interval:

```text
current = (1,3)
```

### Step 3: Compare Intervals

For every remaining interval:

- If its starting point is less than or equal to the current ending point, they overlap.
- Merge them by extending the ending point if necessary.
- Otherwise, add the current interval to the output and start a new current interval.

### Step 4: Add the Last Interval

After processing all intervals, add the final current interval to the output.

---

## Pseudocode

```text id="s8a0f1"
ALGORITHM MergeIntervals(I, n)

    Sort I by starting point

    Create empty output list

    currentStart = I[0].start
    currentEnd   = I[0].end

    FOR i = 1 TO n - 1

        IF I[i].start <= currentEnd

            currentEnd = max(currentEnd, I[i].end)

        ELSE

            Add (currentStart, currentEnd) to output

            currentStart = I[i].start
            currentEnd = I[i].end

    Add (currentStart, currentEnd) to output

    RETURN output
```

---

## Example

Given:

```text
I = {(1,3), (2,6), (8,10), (7,18)}
```

### Step 1: Sort by Starting Point

```text
(1,3)
(2,6)
(7,18)
(8,10)
```

### Step 2: Start With

```text
current = (1,3)
```

### Step 3: Process `(2,6)`

Since:

```text
2 <= 3
```

the intervals overlap.

Merge:

```text
(1,3) + (2,6)
       ↓
(1,6)
```

### Step 4: Process `(7,18)`

Since:

```text
7 > 6
```

there is no overlap.

Add:

```text
(1,6)
```

to the output.

Start a new current interval:

```text
current = (7,18)
```

### Step 5: Process `(8,10)`

Since:

```text
8 <= 18
```

the intervals overlap.

The larger ending point is `18`, so:

```text
(7,18)
```

remains unchanged.

### Final Output

```text
{(1,6), (7,18)}
```

---

## Correctness

After sorting, intervals are arranged according to their starting points.

We maintain the invariant:

> `currentStart` and `currentEnd` represent the complete merged interval containing all processed intervals that overlap with the current interval.

For every next interval `(start, end)`:

### Case 1: Overlapping

If:

```text
start <= currentEnd
```

then the next interval overlaps the current merged interval.

The merged ending point must be:

```text
max(currentEnd, end)
```

Therefore, updating `currentEnd` correctly combines both intervals.

### Case 2: Non-overlapping

If:

```text
start > currentEnd
```

then the next interval cannot overlap the current interval or any earlier interval in the current group because the intervals are sorted by starting point.

Therefore, the current interval can safely be added to the output, and the next interval becomes the new current interval.

After all intervals have been processed, the final current interval is also added.

Thus, every overlapping group is merged correctly, and the output contains only non-overlapping intervals.

---

# Time Complexity Analysis

Let there be `n` intervals.

### 1. Sorting

We sort the `n` intervals based on their starting points.

Using a comparison-based sorting algorithm:

```text id="x9lqzv"
O(n log n)
```

### 2. Merging

After sorting, we scan the intervals exactly once.

There are `n` intervals, so:

```text id="5e6o0v"
O(n)
```

### 3. Total Complexity

Therefore:

```text id="65mm6e"
T(n) = O(n log n) + O(n)

     = O(n log n)
```

Since:

```text
n log n > n
```

for sufficiently large `n`, the sorting step dominates.

### Final Time Complexity

```text id="wq4q9q"
Worst Case = O(n log n)
```

This satisfies the required complexity.

---

## Space Complexity

The input contains `n` intervals.

We use an additional output array that can contain at most `n` intervals.

Therefore:

```text id="d0o9qj"
Space Complexity = O(n)
```

The `qsort()` implementation may also use internal stack space, but the algorithm's explicit auxiliary storage is `O(n)`.

---

## C Program

```c id="6w3s5a"
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int start;
    int end;
} Interval;

/* Compare intervals according to starting point */
int compare(const void *a, const void *b)
{
    Interval *i1 = (Interval *)a;
    Interval *i2 = (Interval *)b;

    if (i1->start < i2->start)
        return -1;

    if (i1->start > i2->start)
        return 1;

    return 0;
}

int main()
{
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid number of intervals.\n");
        return 1;
    }

    Interval intervals[n];
    Interval result[n];

    printf("\nEnter the intervals (start end):\n");

    for (int i = 0; i < n; i++)
    {
        printf("Interval %d: ", i + 1);
        scanf("%d %d",
              &intervals[i].start,
              &intervals[i].end);

        if (intervals[i].start > intervals[i].end)
        {
            printf("Invalid interval.\n");
            return 1;
        }
    }

    /* Sort intervals by starting point */
    qsort(intervals,
          n,
          sizeof(Interval),
          compare);

    int resultCount = 0;

    /* Start with the first interval */
    int currentStart = intervals[0].start;
    int currentEnd = intervals[0].end;

    /* Merge overlapping intervals */
    for (int i = 1; i < n; i++)
    {
        if (intervals[i].start <= currentEnd)
        {
            /*
                Intervals overlap.
                Extend current interval if necessary.
            */
            if (intervals[i].end > currentEnd)
            {
                currentEnd = intervals[i].end;
            }
        }
        else
        {
            /*
                No overlap.
                Store the current merged interval.
            */
            result[resultCount].start = currentStart;
            result[resultCount].end = currentEnd;
            resultCount++;

            /* Start a new interval */
            currentStart = intervals[i].start;
            currentEnd = intervals[i].end;
        }
    }

    /* Store the final interval */
    result[resultCount].start = currentStart;
    result[resultCount].end = currentEnd;
    resultCount++;

    /* Display result */
    printf("\nMerged intervals:\n");

    printf("{");

    for (int i = 0; i < resultCount; i++)
    {
        printf("(%d,%d)",
               result[i].start,
               result[i].end);

        if (i < resultCount - 1)
            printf(", ");
    }

    printf("}\n");

    return 0;
}
```

---

# Sample Input

```text id="4v2y9g"
Enter number of intervals: 4

Enter the intervals (start end):
Interval 1: 1 3
Interval 2: 2 6
Interval 3: 8 10
Interval 4: 7 18
```

## Sample Output

```text id="2w6p5f"
Merged intervals:
{(1,6), (7,18)}
```

---

# Another Example

### Input

```text id="c3f5qv"
6

(1,4)
(3,5)
(6,8)
(7,10)
(12,15)
(14,18)
```

After sorting:

```text id="b9z5u7"
(1,4)
(3,5)
(6,8)
(7,10)
(12,15)
(14,18)
```

Merging:

```text id="m3v1e8"
(1,4) + (3,5)  → (1,5)

(6,8) + (7,10) → (6,10)

(12,15) + (14,18) → (12,18)
```

### Output

```text id="l6p5km"
{(1,5), (6,10), (12,18)}
```

---

# Why Sorting Is Important

Without sorting, determining which intervals overlap could require comparing every interval with every other interval.

This could result in:

```text id="7r0j2b"
O(n²)
```

time.

By sorting according to the starting points:

```text id="v4h9ns"
Input intervals
      ↓
Sort by start
      ↓
Scan from left to right
      ↓
Merge overlapping intervals
```

we only need one linear scan after sorting.

Therefore:

```text id="4zq5kg"
Sorting = O(n log n)
Scanning = O(n)

Total = O(n log n)
```

---

# Complexity Summary

| Operation | Complexity |
|---|---:|
| Sort intervals | O(n log n) |
| Scan and merge | O(n) |
| **Total Time** | **O(n log n)** |
| **Space Complexity** | **O(n)** |

---

# Conclusion

The interval-merging problem can be solved efficiently by first sorting all intervals according to their starting points.

After sorting, a single traversal is sufficient to identify and merge overlapping intervals.

For every interval:

```text
start <= currentEnd
```

means that it overlaps with the current interval and can be merged. Otherwise, the current interval is finalized and a new interval begins.

Thus, the algorithm achieves the required **worst-case O(n log n)** time complexity.