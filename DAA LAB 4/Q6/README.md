# Application of Sorting-VI

## Problem Statement

Given a set `S` of `n` intervals on a line, where the `i`th interval is represented by its left and right endpoints:

```text
(li, ri)
```

find a point `p` on the line that lies in the **largest possible number of intervals**.

An endpoint is considered to be part of its interval.

### Example

Given:

```text
S = {(10,40), (20,60), (50,90), (15,70)}
```

No point lies in all four intervals.

However:

```text
p = 50
```

lies in:

```text
(20,60)
(50,90)
(15,70)
```

Therefore, `p = 50` lies in **3 intervals**, which is the maximum.

The algorithm must run in:

```text
O(n log n)
```

time.

---

## Aim

To identify a point on a line that is contained in the maximum number of intervals using a sorting-based algorithm with **O(n log n)** time complexity.

---

# Key Idea

The problem can be converted into an **event processing problem**.

Each interval generates two events:

- **Left endpoint** → one person/interval becomes active → `+1`
- **Right endpoint** → one interval becomes inactive → `-1`

Since the problem states that an endpoint **counts as being inside its interval**, when a left and right endpoint occur at the same position, the endpoint must be processed appropriately.

However, the problem does not require handling ties between endpoints specially if all endpoints are distinct. For a general implementation, we can use an event type and process **start events before end events** at the same coordinate.

After sorting all `2n` events by position, scan from left to right while maintaining:

```text
currentCount
```

Whenever `currentCount` becomes greater than the previous maximum, store that coordinate as the answer.

---

# Algorithm

### Step 1: Create Events

For every interval `(li, ri)`, create:

```text
(li, +1)    // interval starts
(ri, -1)    // interval ends
```

Therefore, there are:

```text
2n
```

events.

---

### Step 2: Sort the Events

Sort all events according to their position on the line.

If two events have the same position, process the **start event before the end event** because endpoints count as belonging to their intervals.

---

### Step 3: Sweep the Line

Initialize:

```text
currentCount = 0
maxCount = 0
bestPoint = 0
```

Traverse the sorted events.

For each event:

### Start Event

```text
currentCount++
```

If:

```text
currentCount > maxCount
```

then:

```text
maxCount = currentCount
bestPoint = event.position
```

### End Event

```text
currentCount--
```

Continue until all events have been processed.

---

# Pseudocode

```text
ALGORITHM MaximumOverlap(S, n)

    Create Events[2n]

    FOR i = 0 TO n-1

        Events[2i]     = (li, START)
        Events[2i + 1] = (ri, END)

    Sort Events by position
        If positions are equal:
            START comes before END

    currentCount = 0
    maxCount = 0
    bestPoint = 0

    FOR each event in Events

        IF event.type = START

            currentCount++

            IF currentCount > maxCount

                maxCount = currentCount
                bestPoint = event.position

        ELSE

            currentCount--

    RETURN bestPoint, maxCount
```

---

# Example

Consider:

```text
S = {(10,40), (20,60), (50,90), (15,70)}
```

Create events:

```text
10 → START
40 → END

20 → START
60 → END

50 → START
90 → END

15 → START
70 → END
```

After sorting:

```text
10  START
15  START
20  START
40  END
50  START
60  END
70  END
90  END
```

Now perform the sweep.

| Point | Event | Current Count | Maximum |
|---:|---|---:|---:|
| 10 | Start | 1 | 1 |
| 15 | Start | 2 | 2 |
| 20 | Start | 3 | 3 |
| 40 | End | 2 | 3 |
| 50 | Start | 3 | 3 |
| 60 | End | 2 | 3 |
| 70 | End | 1 | 3 |
| 90 | End | 0 | 3 |

The maximum overlap is:

```text
3
```

One valid point is:

```text
20
```

At `p = 20`, the intervals containing the point are:

```text
(10,40)
(20,60)
(15,70)
```

So:

```text
Maximum number of intervals = 3
Point = 20
```

The example's `p = 50` is also valid because it lies in three intervals.

---

# Correctness

The sweep-line algorithm maintains the number of intervals currently covering the point being processed.

Consider the events from left to right.

Whenever a left endpoint is encountered, its interval begins, so:

```text
currentCount++
```

Whenever a right endpoint is encountered, its interval ends, so:

```text
currentCount--
```

Therefore, between two consecutive event coordinates, `currentCount` represents exactly the number of intervals covering every point in that region.

When a start event causes:

```text
currentCount > maxCount
```

we have found a point covered by more intervals than any previously examined point.

That point is stored as `bestPoint`.

Because every interval contributes both its starting and ending event, the entire line is examined.

Therefore, after all events have been processed:

```text
maxCount
```

is the largest number of intervals covering any point, and:

```text
bestPoint
```

is a point where this maximum occurs.

Hence, the algorithm is correct.

---

# Time Complexity Analysis

There are `n` intervals.

Each interval produces two events:

```text
2n events
```

## 1. Creating Events

For each interval, we create two events.

Therefore:

```text
O(n)
```

---

## 2. Sorting Events

We sort `2n` events.

Using a comparison-based sorting algorithm:

```text
O(2n log(2n))
```

Ignoring constants:

```text
O(n log n)
```

---

## 3. Scanning Events

We process every event exactly once.

There are `2n` events:

```text
O(2n)
= O(n)
```

---

## 4. Total Complexity

Therefore:

```text
T(n) = O(n) + O(n log n) + O(n)

     = O(n log n)
```

The sorting operation dominates the running time.

### Final Time Complexity

```text
Best Case    = O(n log n)
Average Case = O(n log n)
Worst Case   = O(n log n)
```





---

# Space Complexity

The algorithm creates `2n` events.

Therefore, the event array requires:

```text
O(2n) = O(n)
```

Additional variables require constant space:

```text
O(1)
```

Hence:

```text
Space Complexity = O(n)
```

---

# C Program

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int position;
    int type;   // 1 = START, -1 = END
} Event;

/*
    Comparator for sorting events.

    If positions are different, sort by position.

    If positions are equal, START (+1) comes before
    END (-1), because endpoints count as belonging
    to the interval.
*/
int compareEvents(const void *a, const void *b)
{
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    if (e1->position != e2->position)
        return e1->position - e2->position;

    return e2->type - e1->type;
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

    Event events[2 * n];

    printf("\nEnter the intervals (left right):\n");

    for (int i = 0; i < n; i++)
    {
        int left, right;

        printf("Interval %d: ", i + 1);
        scanf("%d %d", &left, &right);

        if (left > right)
        {
            printf("Invalid interval.\n");
            return 1;
        }

        /*
            Left endpoint = START event
            Right endpoint = END event
        */
        events[2 * i].position = left;
        events[2 * i].type = 1;

        events[2 * i + 1].position = right;
        events[2 * i + 1].type = -1;
    }

    /* Sort all events */
    qsort(
        events,
        2 * n,
        sizeof(Event),
        compareEvents
    );

    int currentCount = 0;
    int maxCount = 0;
    int bestPoint = 0;

    /*
        Sweep through the sorted events.
    */
    for (int i = 0; i < 2 * n; i++)
    {
        if (events[i].type == 1)
        {
            /* Start event */
            currentCount++;

            if (currentCount > maxCount)
            {
                maxCount = currentCount;
                bestPoint = events[i].position;
            }
        }
        else
        {
            /* End event */
            currentCount--;
        }
    }

    printf("\n--------------------------------------\n");
    printf("Point with maximum overlap: %d\n", bestPoint);
    printf("Maximum number of intervals: %d\n", maxCount);
    printf("--------------------------------------\n");

    return 0;
}
```

---

# Sample Input

```text
Enter number of intervals: 4

Enter the intervals (left right):
Interval 1: 10 40
Interval 2: 20 60
Interval 3: 50 90
Interval 4: 15 70
```

# Sample Output

```text
--------------------------------------
Point with maximum overlap: 20
Maximum number of intervals: 3
--------------------------------------
```

`20` is one valid answer. The point `50` would also have an overlap of `3`.

---

# Another Example

Consider:

```text
S = {(1,5), (2,7), (4,8), (10,15), (12,20)}
```

Events:

```text
1  START
2  START
4  START
5  END
7  END
8  END
10 START
12 START
15 END
20 END
```

The sweep gives:

| Point | Event | Current Count |
|---:|---|---:|
| 1 | Start | 1 |
| 2 | Start | 2 |
| 4 | Start | 3 |
| 5 | End | 2 |
| 7 | End | 1 |
| 8 | End | 0 |
| 10 | Start | 1 |
| 12 | Start | 2 |
| 15 | End | 1 |
| 20 | End | 0 |

Therefore:

```text
Maximum overlap = 3
Point = 4
```

---

# Suitable Input Representation

Each interval:

```text
(li, ri)
```

is converted into two events:

```text
(li, +1)
(ri, -1)
```

The event structure used in C is:

```c
typedef struct
{
    int position;
    int type;
} Event;
```

where:

```text
type = +1 → interval starts
type = -1 → interval ends
```

This representation allows the problem to be solved using a simple sorting and scanning technique.

---

# Why Sorting Helps

A brute-force approach could check every possible point against every interval, resulting in approximately:

```text
O(n²)
```

operations.

Instead, the sorting-based approach transforms the problem into:

```text
Intervals
    ↓
Create 2n start/end events
    ↓
Sort events
    ↓
Sweep from left to right
    ↓
Maintain active interval count
    ↓
Record maximum
```

The sorting step costs:

```text
O(n log n)
```

and the sweep costs:

```text
O(n)
```

Therefore:

```text
Total = O(n log n)
```

---

# Complexity Summary

| Operation | Complexity |
|---|---:|
| Create `2n` events | O(n) |
| Sort events | O(n log n) |
| Sweep through events | O(n) |
| **Total Time** | **O(n log n)** |
| **Space Complexity** | **O(n)** |

---

# Conclusion

The interval-overlap problem can be efficiently solved using a **sweep-line algorithm**.

Each interval is represented using a start event and an end event. After sorting all events by position, we scan them from left to right while maintaining the number of currently active intervals.

The point at which this count reaches its maximum is the required point `p`.

Thus, the algorithm achieves the required:

```text
O(n log n)
```

time complexity with:

```text
O(n)
```

space complexity.