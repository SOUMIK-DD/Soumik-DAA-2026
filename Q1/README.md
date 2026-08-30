# DAA Lab 5 - Question 1

## Find Median Without Sorting

### Aim
To find the median of N numbers without sorting the complete list.

### Approach
The Quickselect algorithm is used. It partitions the array like Quick Sort but processes only the portion containing the required median.

### Algorithm
1. Read N numbers.
2. If N is odd, find the element at index `N/2`.
3. If N is even, find elements at indices `N/2 - 1` and `N/2`.
4. Calculate their average for the even case.
5. Use Quickselect to find the required element(s).
6. Display the median.

### Example Output
```text
Median = 10
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
The median was successfully found without sorting the complete list.
