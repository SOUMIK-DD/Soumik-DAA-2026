# Application of Sorting-IV

## Problem Statement

A camera at the door records the **entry time** `ai` and **exit time** `bi` for each of `n` persons `pi` attending a party.

For every person:

```text
bi > ai
```

where:

- `ai` = entry time
- `bi` = exit time

Design an **O(n log n)** algorithm to determine the **time when the maximum number of people were simultaneously present** at the party.

Assume that all entry and exit times are distinct, so there are **no ties**.

By choosing a suitable input representation, write a C program to validate the algorithm.

---

## Aim

To determine the time at which the **maximum number of people are simultaneously present** at a party using a sorting-based algorithm with:

```text
O(n log n)
```

time complexity.

---

## Key Idea

Each person produces two events:

- **Entry** → `+1` person
- **Exit** → `-1` person

Therefore, instead of processing pairs individually, we create an event array containing all `2n` events.

For example:

```text
Person 1: Entry = 10, Exit = 40

Events:
(10, +1)
(40, -1)
```

We then sort all events according to their time.

After sorting, scan the events from earliest to latest while maintaining a counter:

```text
currentPeople
```

- When an entry event occurs:
  ```text
  currentPeople++
  ```

- When an exit event occurs:
  ```text
  currentPeople--
  ```

Whenever `currentPeople` becomes greater than the previous maximum, store that time.

The stored time is the time when the maximum number of people were simultaneously present.

---

## Algorithm

### Step 1: Create Events

For each person `i`:

```text
(ai, ENTRY)
(bi, EXIT)
```

Thus, there are:

```text
2n
```

events.

### Step 2: Sort Events

Sort all `2n` events according to their time.

Since all times are distinct, no tie-breaking is required.

### Step 3: Scan the Events

Initialize:

```text
currentPeople = 0
maxPeople = 0
maxTime = 0
```

Traverse the sorted events.

For every event:

- If it is an entry:
  ```text
  currentPeople++
  ```

- If it is an exit:
  ```text
  currentPeople--
  ```

Whenever:

```text
currentPeople > maxPeople
```

update:

```text
maxPeople = currentPeople
maxTime = event.time
```

### Step 4: Return the Result

After processing all events:

- `maxPeople` = maximum number of simultaneous people.
- `maxTime` = time when this maximum was first reached.

---

## Pseudocode

```text
ALGORITHM MaximumPeople(A, B, n)

    Create an array Events of size 2n

    FOR i = 0 TO n-1

        Events[2i]     = (A[i], +1)
        Events[2i + 1] = (B[i], -1)

    Sort Events by time

    currentPeople = 0
    maxPeople = 0
    maxTime = 0

    FOR i = 0 TO 2n-1

        IF Events[i].type = ENTRY
            currentPeople = currentPeople + 1

            IF currentPeople > maxPeople
                maxPeople = currentPeople
                maxTime = Events[i].time

        ELSE
            currentPeople = currentPeople - 1

    RETURN maxTime, maxPeople
```

---

## Example

Consider the following people:

| Person | Entry | Exit |
|---|---:|---:|
| P1 | 10 | 40 |
| P2 | 20 | 60 |
| P3 | 50 | 90 |
| P4 | 15 | 70 |

### Create Events

```text
10 → Entry
40 → Exit
20 → Entry
60 → Exit
50 → Entry
90 → Exit
15 → Entry
70 → Exit
```

After sorting:

```text
10  Entry
15  Entry
20  Entry
40  Exit
50  Entry
60  Exit
70  Exit
90  Exit
```

Now scan the events:

| Time | Event | Current People | Maximum |
|---:|---|---:|---:|
| 10 | Entry | 1 | 1 |
| 15 | Entry | 2 | 2 |
| 20 | Entry | 3 | 3 |
| 40 | Exit | 2 | 3 |
| 50 | Entry | 3 | 3 |
| 60 | Exit | 2 | 3 |
| 70 | Exit | 1 | 3 |
| 90 | Exit | 0 | 3 |

Therefore:

```text
Maximum people = 3
Time = 20
```

The maximum number of people simultaneously present was **3**, first reached at time **20**.

---

## Correctness

We maintain a counter representing the number of people currently inside the party.

Before processing any events:

```text
currentPeople = 0
```

Whenever an entry event occurs, exactly one person enters:

```text
currentPeople++
```

Whenever an exit event occurs, exactly one person leaves:

```text
currentPeople--
```

Because the events are processed in chronological order, `currentPeople` always represents the exact number of people present immediately after that event.

Whenever:

```text
currentPeople > maxPeople
```

the algorithm records the current time.

Therefore, whenever a new maximum number of simultaneously present people occurs, it is recorded.

After all `2n` events are processed, the recorded `maxPeople` is the maximum number of people present at any time, and `maxTime` is the time when this maximum was first achieved.

Hence, the algorithm is correct.

---

# Time Complexity Analysis

There are `n` people.

Each person produces two events:

```text
2 events per person
```

Therefore, total events:

```text
2n
```

### 1. Creating Events

Creating the event array requires visiting each person once:

```text
O(n)
```

### 2. Sorting Events

We sort `2n` events.

Using a comparison-based sorting algorithm such as `qsort()`:

```text
O(2n log(2n))
```

Since constants are ignored:

```text
O(n log n)
```

### 3. Scanning Events

There are `2n` events and each is processed once:

```text
O(2n)
= O(n)
```

### 4. Total Complexity

Therefore:

```text
T(n) = O(n) + O(n log n) + O(n)

     = O(n log n)
```

The sorting operation dominates.

### Final Time Complexity

```text
Best Case    = O(n log n)
Average Case = O(n log n)
Worst Case   = O(n log n)
```





---

# Space Complexity

We create an event array containing `2n` events.

Therefore:

```text
O(2n) = O(n)
```

Additional variables such as:

```text
currentPeople
maxPeople
maxTime
```

require constant space:

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
    int time;
    int type;   // +1 = Entry, -1 = Exit
} Event;

/* Comparator for qsort() */
int compare(const void *a, const void *b)
{
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    return e1->time - e2->time;
}

int main()
{
    int n;

    printf("Enter number of people: ");
    scanf("%d", &n);

    Event events[2 * n];

    printf("\nEnter entry and exit times:\n");

    for (int i = 0; i < n; i++)
    {
        int entry, exit;

        printf("Person %d: ", i + 1);
        scanf("%d %d", &entry, &exit);

        if (exit <= entry)
        {
            printf("Invalid input! Exit time must be greater than entry time.\n");
            return 1;
        }

        events[2 * i].time = entry;
        events[2 * i].type = 1;

        events[2 * i + 1].time = exit;
        events[2 * i + 1].type = -1;
    }

    /* Sort all events by time */
    qsort(events, 2 * n, sizeof(Event), compare);

    int currentPeople = 0;
    int maxPeople = 0;
    int maxTime = 0;

    /* Process sorted events */
    for (int i = 0; i < 2 * n; i++)
    {
        if (events[i].type == 1)
        {
            currentPeople++;

            if (currentPeople > maxPeople)
            {
                maxPeople = currentPeople;
                maxTime = events[i].time;
            }
        }
        else
        {
            currentPeople--;
        }
    }

    printf("\n---------------------------------\n");
    printf("Maximum number of people: %d\n", maxPeople);
    printf("Time when maximum was reached: %d\n", maxTime);
    printf("---------------------------------\n");

    return 0;
}
```

---

# Sample Input

```text
Enter number of people: 4

Enter entry and exit times:
Person 1: 10 40
Person 2: 20 60
Person 3: 50 90
Person 4: 15 70
```

## Sample Output

```text
---------------------------------
Maximum number of people: 3
Time when maximum was reached: 20
---------------------------------
```

---

# Event Representation

The program uses the following representation:

```text
Entry → +1
Exit  → -1
```

For example:

```text
Person 1: (10, 40)
```

is represented as:

```text
(10, +1)
(40, -1)
```

For `n` people, the program therefore creates exactly:

```text
2n
```

events.

This representation makes the problem equivalent to finding the maximum prefix sum after sorting the events by time.

---

# Why the Algorithm Is O(n log n)

A naive approach could compare every possible time interval with every other interval, potentially requiring:

```text
O(n²)
```

time.

Instead, our algorithm converts the problem into an **event sorting problem**:

```text
Entry/Exit Times
       ↓
Create 2n Events
       ↓
Sort Events
       ↓
Scan Once
       ↓
Track Current People
       ↓
Find Maximum
```

The expensive operation is sorting:

```text
O(2n log(2n))
= O(n log n)
```

The final scan is only:

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
| Create events | O(n) |
| Sort `2n` events | O(n log n) |
| Scan events | O(n) |
| **Total Time** | **O(n log n)** |
| **Space** | **O(n)** |

---

# Conclusion

The problem can be efficiently solved by treating every entry and exit as an event.

Each entry increases the number of people by `1`, while each exit decreases it by `1`. After sorting all `2n` events by time, a single scan keeps track of the number of people currently present.

The maximum value of this counter gives the **maximum number of simultaneously present people**, and the corresponding event time gives the **time when the maximum was reached**.

Therefore, the algorithm achieves the required:

```text
O(n log n)
```

time complexity and:

```text
O(n)
```

space complexity.