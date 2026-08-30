# DAA Lab 5 - Question 4

## Heap Sort Using Random Elements Stored in a File

### Aim
To generate N random elements, store them in a file, read them back, and sort them using Heap Sort.

### Approach
The program generates N random numbers, stores them in `random.txt`, reads them back, builds a Max Heap, and repeatedly extracts the maximum element.

### Algorithm
1. Read N.
2. Generate N random numbers.
3. Store them in `random.txt`.
4. Read the numbers from the file.
5. Build a Max Heap.
6. Swap the root with the last element.
7. Reduce the heap size and apply Heapify.
8. Repeat until sorted.
9. Display the result.

### Example Output
```text
Sorted elements:
29 91 128 210 317 403 562 671 734 845
```

### Complexity Analysis
| Operation | Complexity |
|-----------|------------|
| Build Max Heap | O(N) |
| Heapify | O(log N) |
| Heap Sort | O(N log N) |

| Case | Time |
|------|------|
| Best | O(N log N) |
| Average | O(N log N) |
| Worst | O(N log N) |

### Space Complexity
`O(1)` auxiliary space.

### Result
N randomly generated elements were stored in a file, read back, and successfully sorted using Heap Sort.
