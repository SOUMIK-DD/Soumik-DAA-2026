# Q1 - Dictionary ADT using Different Data Structures

## Problem Statement

Consider a Dictionary (D) Abstract Data Type that permits access to data items by their content (key).

The primary operations are:

- Search(D, k)
- Insert(D, x)
- Delete(D, x)
- Minimum(D)
- Maximum(D)
- Predecessor(D, x)
- Successor(D, x)

Implement the Dictionary ADT using the following six data structures:

1. Unsorted Array
2. Sorted Array
3. Singly Linked Unsorted List
4. Singly Linked Sorted List
5. Doubly Linked Unsorted List
6. Doubly Linked Sorted List

Determine the worst-case asymptotic running time of all seven operations and validate the order of growth using Gnuplot.

---

## Data Structures Used

### 1. Unsorted Array
Elements are stored without maintaining any particular order.

### 2. Sorted Array
Elements are maintained in increasing order.

### 3. Singly Linked Unsorted List
Elements are stored in nodes connected using a `next` pointer, without maintaining order.

### 4. Singly Linked Sorted List
Elements are stored in increasing order using a singly linked list.

### 5. Doubly Linked Unsorted List
Each node contains `prev` and `next` pointers, but elements are not sorted.

### 6. Doubly Linked Sorted List
Elements are maintained in sorted order using a doubly linked list.

---

## Worst-Case Complexity

| Operation | Unsorted Array | Sorted Array | Singly Unsorted | Singly Sorted | Doubly Unsorted | Doubly Sorted |
|-----------|----------------|--------------|-----------------|---------------|-----------------|---------------|
| Search | O(n) | O(log n) | O(n) | O(n) | O(n) | O(n) |
| Insert | O(1) | O(n) | O(1) | O(n) | O(1) | O(n) |
| Delete | O(n) | O(n) | O(n) | O(n) | O(n) | O(n) |
| Minimum | O(n) | O(1) | O(n) | O(1) | O(n) | O(1) |
| Maximum | O(n) | O(1) | O(n) | O(n) | O(n) | O(n) |
| Predecessor | O(n) | O(n) | O(n) | O(n) | O(n) | O(n) |
| Successor | O(n) | O(n) | O(n) | O(n) | O(n) | O(n) |

> **Note:** The table corresponds to the implementations in the C program, where operations such as predecessor and successor are performed using a key. Therefore, the key may first need to be searched.

---

## Program Description

The C program:

- Implements all six data structures.
- Implements all seven Dictionary operations.
- Demonstrates the operations using sample data.
- Displays the worst-case complexity comparison.
- Generates `operations.dat` containing operation-growth data.
- Generates `plot.gp`, a Gnuplot script used to plot the results.

---

## Files

```text
q1.c
operations.dat
plot.gp
README.md
