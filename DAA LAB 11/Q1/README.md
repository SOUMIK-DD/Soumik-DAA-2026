# Q1. Shortest Path on Parity-Constrained Graphs using 0-1 BFS

## Problem Statement

Given a directed graph with `V` vertices and `E` edges, where each edge has a weight of either `0` or `1`, a source vertex `S`, and a penalty value `C`.

For any path `P`:

- `W(P)` is the sum of all edge weights.
- `k₁(P)` is the number of weight-1 edges in the path.
- If `k₁(P)` is even, then:

```text
Cost(P) = W(P)
```

- If `k₁(P)` is odd, then:

```text
Cost(P) = W(P) + C
```

The objective is to find the minimum effective cost from the source vertex to every other vertex. If a vertex is unreachable, it should be reported as `Unreachable`.

---

## Algorithm

1. Represent the directed graph using an adjacency list.
2. Maintain two distance values for every vertex:
   - `dist[v][0]` → minimum distance when the number of weight-1 edges is even.
   - `dist[v][1]` → minimum distance when the number of weight-1 edges is odd.
3. Initialize all distances to `INF`.
4. Set `dist[S][0] = 0` because the source initially has zero weight-1 edges.
5. Use a deque to perform 0-1 BFS.
6. For every edge:
   - If its weight is `0`, the parity remains unchanged.
   - If its weight is `1`, the parity changes.
7. If a shorter distance is found, update the corresponding distance.
8. Insert weight-0 transitions at the front of the deque and weight-1 transitions at the back.
9. For each vertex, calculate the final effective cost as:

```text
min(dist[v][0], dist[v][1] + C)
```

10. Print the minimum cost or `Unreachable`.
11. Free all dynamically allocated memory.

---

## Pseudocode

```text
START

Read V, E

Create adjacency list adj[V]

FOR each edge
    Read u, v, w
    Add edge u → v with weight w
END FOR

Read source S and penalty C

Initialize dist[v][0] = INF
Initialize dist[v][1] = INF for every vertex v

dist[S][0] = 0

Create empty deque
Insert (S, 0) into deque

WHILE deque is not empty

    Remove (u, parity) from front

    FOR every edge u → v with weight w

        IF w = 0
            newParity = parity
        ELSE
            newParity = 1 - parity
        END IF

        newDistance = dist[u][parity] + w

        IF newDistance < dist[v][newParity]

            dist[v][newParity] = newDistance

            IF w = 0
                Insert (v, newParity) at front
            ELSE
                Insert (v, newParity) at back
            END IF

        END IF

    END FOR

END WHILE

FOR every vertex v

    answer = INF

    answer = min(answer, dist[v][0])

    IF dist[v][1] is not INF
        answer = min(answer, dist[v][1] + C)
    END IF

    IF answer = INF
        Print "Unreachable"
    ELSE
        Print answer
    END IF

END FOR

Free allocated memory

STOP
```
---

## Sample Input

```text
Enter number of vertices and edges: 5 6
Enter directed edges (u v weight):
0 1 0
0 2 1
1 2 1
1 3 0
2 3 0
3 4 1
Enter source vertex and penalty C: 0 5
```

## Sample Output

```text
Minimum effective cost from source 0:
Vertex 0 : 0
Vertex 1 : 0
Vertex 2 : 1
Vertex 3 : 0
Vertex 4 : 1
```

---

## Time Complexity Analysis

The algorithm maintains two states for every vertex:

```text
(v, even)
(v, odd)
```

Thus, there are `2V` states.

Since the graph contains only edge weights `0` and `1`, 0-1 BFS is used. Each state processes its outgoing edges, giving:

```text
Time Complexity: O(V + E)
```

---

## Conclusion

The program finds the minimum effective cost from a given source vertex to every vertex in a directed graph with edge weights `0` and `1`, while considering the parity of the number of weight-1 edges. It uses two distance states for each vertex and a deque-based 0-1 BFS to efficiently handle the parity constraint and penalty. The algorithm achieves an overall time complexity of `O(V + E)`.
