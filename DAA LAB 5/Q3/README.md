# DAA Lab 5 - Question 3

## Quick Sort Using Random Elements Stored in a File

### Aim
To generate N random elements, store them in a file, read them back, and sort them using Quick Sort.

### Approach
The program generates N random numbers, stores them in `random.txt`, reads them back, applies Quick Sort, and displays the sorted elements.

### Algorithm
1. Read N.
2. Generate N random numbers using `rand()`.
3. Store them in `random.txt`.
4. Read the numbers from the file.
5. Select a pivot and partition the array.
6. Recursively sort the left and right partitions.
7. Display the sorted array.

### Example Output
```text
Sorted elements:
46 71 127 209 375 490 583 654 812 921
```

### Complexity Analysis
| Case | Time |
|------|------|
| Best | O(N log N) |
| Average | O(N log N) |
| Worst | O(N²) |

### Space Complexity
Average recursion stack: `O(log N)`; worst case: `O(N)`.

### Result
N randomly generated elements were stored in a file, read back, and successfully sorted using Quick Sort.
