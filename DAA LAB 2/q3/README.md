# Merging K Sorted Arrays

## Method 1

The arrays are merged one at a time.

First merge:
2 arrays × n elements = O(2n)

Second merge:
3 arrays × n elements = O(3n)

Third merge:
4 arrays × n elements = O(4n)

Therefore:

T(n,k) = 2n + 3n + 4n + ... + kn

T(n,k) = n(2 + 3 + 4 + ... + k)

Using:

2 + 3 + ... + k = k(k+1)/2 - 1

Therefore:

T(n,k) = n[k(k+1)/2 - 1]

Hence:

Worst-case running time = O(nk²)


## Method 2

The k arrays are divided into pairs.

At every level, all kn elements are processed.

Therefore, work at each level:

O(kn)

Number of levels:

log₂(k)

Therefore:

T(n,k) = O(kn log₂ k)

Hence:

Worst-case running time = O(nk log k)


## Comparison

| Method | Worst-Case Running Time |
|--------|--------------------------|
| Method 1 | O(nk²) |
| Method 2 | O(nk log k) |

Therefore, Method 2 is more efficient than Method 1 for large values of k.
