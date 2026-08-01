# Design and Analysis of Algorithms (DAA) Lab Programs

## Student Information

- **Name:** Soumik Nayak
- **Roll Number:** B525062
- **Year:** 2nd Year
- **Department:** Computer Engineering

---

# List of Programs

| Sl. No. | Program | Time Complexity |
|---------|----------|----------------|
| 1 | Bubble Sort Performance Analysis | Best: O(n), Average: O(n²), Worst: O(n²) |
| 2 | Towers of Hanoi | O(2ⁿ) |
| 3 | Fair vs Biased Coin Toss Simulation | O(n) |
| 4 | Growth Rate Comparison | Depends on functions evaluated (typically O(n)) |
| 5 | Partition Point using Binary Search | O(log n) |
| 6 | Element Uniqueness (Duplicate Detection) | O(n²) (Brute Force) |

---

# 1. Bubble Sort Performance Analysis

## Algorithm

1. Read the number of elements.
2. Generate random numbers.
3. Apply Bubble Sort.
4. Version 1:
   - Stop immediately if no swaps occur in a pass.
5. Version 2:
   - Always perform (n−1) passes.
6. Count the total comparisons.
7. Display the sorted array and comparison count.

### Time Complexity

| Case | Complexity |
|------|------------|
| Best | O(n) |
| Average | O(n²) |
| Worst | O(n²) |

---

# 2. Towers of Hanoi

## Algorithm

1. If only one disk:
   - Move it from Source to Destination.
2. Otherwise:
   - Move n−1 disks from Source to Auxiliary.
   - Move largest disk to Destination.
   - Move n−1 disks from Auxiliary to Destination.
3. Count total moves.

### Time Complexity

**T(n) = 2T(n−1) + 1**

Therefore,

**O(2ⁿ)**

---

# 3. Fair vs Biased Coin Toss Simulation

## Algorithm

1. Read number of tosses.
2. Generate random numbers.
3. For Fair Coin:
   - Head if random < 0.5.
4. For Biased Coin:
   - Head if random < desired probability (e.g., 0.7).
5. Count Heads and Tails.
6. Display probabilities.

### Time Complexity

Each toss is processed once.

**O(n)**

---

# 4. Growth Rate Comparison

## Algorithm

1. Choose different values of n.
2. Evaluate functions:
   - log n
   - n
   - n log n
   - n²
   - n³
   - 2ⁿ
3. Store the results.
4. Plot or print the comparison.

### Time Complexity

Evaluating each function once per input:

**O(n)**

---

# 5. Partition Point using Binary Search

## Problem

Array contains:

```
0 0 0 0 0 1 1 1 1
```

Find the first occurrence of **1**.

## Algorithm

1. Initialize:
   - low = 0
   - high = n−1
2. Compute middle.
3. If middle element is 0:
   - Search right half.
4. Otherwise:
   - Save answer.
   - Search left half.
5. Repeat until low > high.
6. Return partition index.

### Time Complexity

Binary search halves the search space each iteration.

**O(log n)**

---

# 6. Element Uniqueness (Duplicate Detection)

## Algorithm

1. Read n elements.
2. Compare every element with every other element.
3. If two elements are equal:
   - Duplicate exists.
4. Otherwise:
   - All elements are unique.

### Time Complexity

Nested loops:

**O(n²)**

---

# Repository Structure

```
DAA-Lab/
│
├── BubbleSort/
├── TowersOfHanoi/
├── CoinToss/
├── GrowthRate/
├── PartitionPoint/
├── ElementUniqueness/
└── README.md
```

---

# Conclusion

This repository contains the implementation of six Design and Analysis of Algorithms laboratory programs in the C programming language. Each program demonstrates a different algorithmic technique and includes its corresponding time complexity analysis for performance evaluation.

---

## Author

**Soumik Nayak**  
**B525062CE**  
**2nd Year - Computer Engineering**
