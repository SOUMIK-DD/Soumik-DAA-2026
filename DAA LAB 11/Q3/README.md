# Bidirectional BFS for Shortest Transformation Sequence in a Word Graph

## Problem Statement

You are given a dictionary `D` containing `N` unique words, all having the same length `L`, a starting word `A`, and a target word `B`.

A valid mutation consists of changing exactly one character of a word such that the resulting word exists in the dictionary.

A transformation sequence is a sequence of words:

`W0, W1, W2, ..., Wk`

such that:

1. `W0 = A` and `Wk = B`.
2. Every intermediate word belongs to the dictionary.
3. Every adjacent pair of words differs in exactly one character.

The objective is to find the minimum number of mutations required to transform `A` into `B`.

If no valid transformation exists, return `-1`.

### Constraints

- `N <= 10^5`
- `L <= 10`
- All words contain only lowercase English letters (`a` to `z`).
- All dictionary words are unique.
- The target word `B` must exist in the dictionary.
- The starting word `A` does not necessarily need to belong to the dictionary.

## Approach

We use **Bidirectional Breadth-First Search (Bidirectional BFS)** to find the shortest transformation sequence efficiently.

Instead of performing BFS only from the starting word, we perform two simultaneous searches:

- Forward BFS starts from `A`.
- Backward BFS starts from `B`.

Both searches expand level by level. When the searches meet at a common word, the minimum mutation distance is obtained by adding the distances from both searches.

To efficiently find neighbouring words, we use a hash table to check whether a generated word exists in the dictionary.

For each word, we change one character at a time and try all 26 lowercase English letters. The original character is skipped because a mutation must change exactly one character.

We expand the smaller BFS frontier at each iteration to reduce the search space.

## Algorithm

1. Read the dictionary, starting word `A`, and target word `B`.
2. Store dictionary words in a hash table for fast lookup.
3. If `B` is absent from the dictionary, report that no valid transformation exists.
4. Initialize two distance arrays, one for the forward search and one for the backward search.
5. Set the distance of `A` in the forward search to `0`.
6. Set the distance of `B` in the backward search to `0`.
7. Maintain separate BFS frontiers for both searches.
8. Expand one complete BFS layer from the smaller frontier.
9. Generate neighbours by replacing each character with every other lowercase letter.
10. Check each generated word using the dictionary hash table.
11. When a word is reached by both searches, add the two distances and return the result.
12. If either search becomes empty before the searches meet, return `-1`.

## Input Format

- First line: `N L`, the number of dictionary words and the word length.
- Next `N` lines: The dictionary words.
- Final line: The starting word `A` and target word `B`.

All words must have exactly `L` lowercase English letters.

## Example Input

```text
6 3
hot
dot
dog
lot
log
cog
hit cog
```

## Example Output

```text
Minimum mutations: 4
```

## Explanation

The starting word is `hit`, and the target word is `cog`.

One valid shortest transformation is:

`hit -> hot -> dot -> dog -> cog`

The mutations are:

1. `hit -> hot`: Change `i` to `o`.
2. `hot -> dot`: Change `h` to `d`.
3. `dot -> dog`: Change `t` to `g`.
4. `dog -> cog`: Change `d` to `c`.

Therefore, the minimum number of mutations is `4`.

The starting word `hit` does not need to be in the dictionary, but all subsequent words, including `cog`, must belong to the dictionary.

## Data Structures Used

- **Dictionary Array:** Stores all dictionary words.
- **Hash Table:** Checks whether a generated word exists in the dictionary.
- **Forward Distance Array:** Stores distances from the starting word.
- **Backward Distance Array:** Stores distances from the target word.
- **BFS Frontiers:** Store vertices at the current search level.
- **Candidate Word Buffer:** Generates possible one-character mutations.

## Complexity Analysis

Let:

- `N` be the number of dictionary words.
- `L` be the length of each word.
- The alphabet size be 26.

### Time Complexity

For each visited word:

- There are `L` character positions.
- Each position has 25 alternative characters.
- Each candidate requires hashing and potentially comparing strings of length `L`.

Therefore, the expected search complexity, including string processing, is:

`O(N * L * 25 * L)`

Since 25 is constant:

**Expected Time Complexity: O(N * L^2)**

Hash-table operations are expected constant-time with respect to the number of stored words, but hashing and comparing a word can take `O(L)` time.

## Conclusion

Bidirectional BFS efficiently finds the shortest word transformation sequence by searching simultaneously from the starting and target words. A hash table provides fast dictionary lookups, while generating one-character mutations avoids explicitly constructing every edge in the graph.

The algorithm returns the minimum number of mutations if a valid path exists; otherwise, it returns `-1`.
