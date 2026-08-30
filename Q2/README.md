# DAA Lab 5 - Question 2

## Find K-th Smallest Element Without Sorting

### Aim
To find the K-th smallest element in N numbers without sorting the complete list.

### Approach
Quickselect partitions the array around a pivot and searches only the partition containing the K-th smallest element.

### Algorithm
1. Read N elements and K.
2. Validate K.
3. Select a pivot and partition the array.
4. Find the pivot's final position.
5. Compare it with `K - 1`.
6. Search the left or right partition accordingly.
7. Display the K-th smallest element.

### Example Output
```text
The 4-th smallest element is: 12
```

### Complexity Analysis
| Case | Time |
|------|------|
| Best | O(N) |
| Average | O(N) |
| Worst | O(N²) |

### Space Complexity
Array: `O(N)`; recursion stack: `O(N)` worst case.

### Result
The K-th smallest element was successfully found without sorting the complete list.
