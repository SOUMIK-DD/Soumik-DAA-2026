
# Multi-Source BFS for Radius-Constrained Voronoi Cell Partitioning

## Problem Statement

You are given an unweighted, undirected graph `G = (V, E)`, a set of `K` designated hub vertices `H = {h1, h2, ..., hK}`, and an integer radius threshold `R >= 0`.

For every vertex `v`, let `dist(v, hi)` denote the shortest path distance from `v` to hub `hi`.

The objective is to assign an ownership label `owner[v]` according to the following rules:

1. Find the minimum distance from vertex `v` to any hub.
2. If the minimum distance is greater than `R`, assign `owner[v] = -1`.
3. Otherwise, assign the vertex to its closest hub.
4. If multiple hubs are equally close, choose the hub with the smallest numerical index.

The program outputs the owner and corresponding shortest distance for every vertex.

## Approach

We use **Multi-Source Breadth-First Search (Multi-Source BFS)**.

Instead of performing a separate BFS from every hub, we insert all hubs into a single queue and explore the graph simultaneously.

We maintain two arrays:

- `dist[v]`: Shortest distance from vertex `v` to its assigned hub.
- `owner[v]`: Index of the hub that owns vertex `v`.

Initially, all vertices have:

`dist[v] = -1`

`owner[v] = -1`

Each hub is initialized with distance `0` and its corresponding hub index.

The hubs are inserted into the queue in ascending index order. BFS processes vertices level by level, ensuring that the first hub to reach an unvisited vertex is the closest hub, with ties resolved in favour of the smallest index.

The search does not expand vertices whose distance equals `R`.

## Algorithm

1. Represent the undirected graph using an adjacency list.
2. Initialize the owner and distance arrays to `-1`.
3. Insert all hub vertices into the queue in ascending hub-index order.
4. Set the distance of every hub to `0` and its owner to its hub index.
5. Remove a vertex `u` from the queue.
6. If `dist[u] == R`, do not explore its neighbours.
7. Otherwise, visit every unassigned neighbour `v`.
8. Set `dist[v] = dist[u] + 1`.
9. Set `owner[v] = owner[u]` and insert `v` into the queue.
10. Output the owner and distance for every vertex.

Vertices that remain unassigned are outside the service coverage area or cannot be reached from any hub.

## Input Format

- First line: `n m`, the number of vertices and edges.
- Next `m` lines: `u v`, representing undirected edges.
- Next line: `K R`, the number of hubs and the maximum radius.
- Final line: The `K` hub vertices in their index order.

Vertices are numbered from `1` to `n`. Hub indices are assigned according to their positions in the hub list, starting from `1`.

## Example Input

```text
7 6
1 3
2 3
3 4
4 5
6 7
1 2
1 2
```

## Example Output

```text
Vertex  Owner  Distance
1       1      0
2       2      0
3       1      1
4       1      2
5      -1     -1
6      -1     -1
7      -1     -1
```

## Explanation

There are seven vertices, six edges, and two hubs:

- Hub 1 is vertex `1`.
- Hub 2 is vertex `2`.
- The maximum service radius is `R = 2`.

Vertex `3` is one edge away from both hubs. Since the distances are equal, it is assigned to Hub 1 because Hub 1 has the smaller index.

Vertex `4` is two edges away from Hub 1, so it belongs to Hub 1.

Vertex `5` is three edges away from the nearest hub, exceeding the radius. Therefore, it is unassigned.

Vertices `6` and `7` are disconnected from both hubs, so they are also unassigned.

For unassigned vertices, both `owner[v]` and `dist[v]` are `-1`.

## Data Structures Used

- **Adjacency List:** Stores the undirected graph efficiently.
- **Queue:** Processes vertices in BFS order.
- **Owner Array:** Stores the assigned hub index.
- **Distance Array:** Stores the shortest distance to the assigned hub.
- **Hub Array:** Stores the designated hub vertices.

## Complexity Analysis

Let:

- `V` be the number of vertices.
- `E` be the number of edges.
- `K` be the number of hubs.

### Time Complexity

Building the adjacency list takes `O(V + E)` time.

Each vertex is inserted into the queue at most once, and each edge is examined at most twice in an undirected graph.

Initializing the hubs takes `O(K)` time.

Since `K <= V`, the overall time complexity is:

**O(V + E)**

## Conclusion

Multi-Source BFS efficiently assigns each vertex to its nearest service hub while respecting the maximum radius. Processing hubs in ascending index order ensures deterministic tie-breaking, and vertices outside the coverage radius remain unassigned.

