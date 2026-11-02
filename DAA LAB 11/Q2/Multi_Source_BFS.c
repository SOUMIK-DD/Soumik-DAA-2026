#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int to;
    struct Edge *next;
} Edge;

void addEdge(Edge **graph, int u, int v) {
    Edge *e = malloc(sizeof(Edge));

    if (e == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    e->to = v;
    e->next = graph[u];
    graph[u] = e;
}

int main(void) {
    int n, m, K, R;

    printf("Enter number of vertices and edges: ");
    if (scanf("%d %d", &n, &m) != 2 ||
        n <= 0 || m < 0) {
        printf("Invalid input.\n");
        return 1;
    }

    Edge **graph = calloc(n + 1, sizeof(Edge *));

    if (graph == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter undirected edges (u v):\n");

    for (int i = 0; i < m; i++) {
        int u, v;

        if (scanf("%d %d", &u, &v) != 2 ||
            u < 1 || u > n || v < 1 || v > n) {
            printf("Invalid edge input.\n");
            return 1;
        }

        addEdge(graph, u, v);
        addEdge(graph, v, u);
    }

    printf("Enter number of hubs and radius R: ");

    if (scanf("%d %d", &K, &R) != 2 ||
        K < 1 || K > n || R < 0) {
        printf("Invalid input.\n");
        return 1;
    }

    int *hubs = malloc(K * sizeof(int));
    int *owner = malloc((n + 1) * sizeof(int));
    int *dist = malloc((n + 1) * sizeof(int));
    int *queue = malloc((n + 1) * sizeof(int));
    int *used = calloc(n + 1, sizeof(int));

    if (hubs == NULL || owner == NULL ||
        dist == NULL || queue == NULL || used == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter hub vertices in index order:\n");

    for (int i = 0; i < K; i++) {
        if (scanf("%d", &hubs[i]) != 1 ||
            hubs[i] < 1 || hubs[i] > n ||
            used[hubs[i]]) {
            printf("Invalid or duplicate hub.\n");
            return 1;
        }

        used[hubs[i]] = 1;
    }

    for (int v = 1; v <= n; v++) {
        owner[v] = -1;
        dist[v] = -1;
    }

    int front = 0, rear = 0;

    for (int i = 0; i < K; i++) {
        int h = hubs[i];

        dist[h] = 0;
        owner[h] = i + 1;
        queue[rear++] = h;
    }

    while (front < rear) {
        int u = queue[front++];

        if (dist[u] == R)
            continue;

        for (Edge *e = graph[u]; e != NULL; e = e->next) {
            int v = e->to;

            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                owner[v] = owner[u];
                queue[rear++] = v;
            }
        }
    }

    printf("\nVertex\tOwner\tDistance\n");

    for (int v = 1; v <= n; v++) {
        printf("%d\t%d\t%d\n", v, owner[v], dist[v]);
    }

    for (int i = 1; i <= n; i++) {
        Edge *e = graph[i];

        while (e != NULL) {
            Edge *temp = e;
            e = e->next;
            free(temp);
        }
    }

    free(graph);
    free(hubs);
    free(owner);
    free(dist);
    free(queue);
    free(used);

    return 0;
}
