#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

typedef struct Edge {
    int to;
    int weight;
    struct Edge *next;
} Edge;

typedef struct {
    int vertex;
    int parity;
} State;

typedef struct Node {
    State data;
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
} Deque;

void addEdge(Edge **adj, int u, int v, int w) {
    Edge *newEdge = (Edge *)malloc(sizeof(Edge));

    newEdge->to = v;
    newEdge->weight = w;
    newEdge->next = adj[u];

    adj[u] = newEdge;
}

void pushFront(Deque *dq, State state) {
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->data = state;
    newNode->next = dq->front;

    dq->front = newNode;

    if (dq->rear == NULL)
        dq->rear = newNode;
}

void pushBack(Deque *dq, State state) {
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->data = state;
    newNode->next = NULL;

    if (dq->rear == NULL) {
        dq->front = newNode;
        dq->rear = newNode;
    } else {
        dq->rear->next = newNode;
        dq->rear = newNode;
    }
}

State popFront(Deque *dq) {
    Node *temp = dq->front;
    State state = temp->data;

    dq->front = dq->front->next;

    if (dq->front == NULL)
        dq->rear = NULL;

    free(temp);

    return state;
}

int isEmpty(Deque *dq) {
    return dq->front == NULL;
}

int main() {
    int V, E, S, C;

    printf("Enter number of vertices and edges: ");
    if (scanf("%d %d", &V, &E) != 2)
        return 1;

    Edge **adj = (Edge **)malloc(V * sizeof(Edge *));

    for (int i = 0; i < V; i++)
        adj[i] = NULL;

    printf("Enter directed edges (u v weight):\n");

    for (int i = 0; i < E; i++) {
        int u, v, w;

        scanf("%d %d %d", &u, &v, &w);

        addEdge(adj, u, v, w);
    }

    printf("Enter source vertex and penalty C: ");
    scanf("%d %d", &S, &C);

    int **dist = (int **)malloc(V * sizeof(int *));

    for (int i = 0; i < V; i++) {
        dist[i] = (int *)malloc(2 * sizeof(int));

        dist[i][0] = INF;
        dist[i][1] = INF;
    }

    Deque dq;
    dq.front = NULL;
    dq.rear = NULL;

    dist[S][0] = 0;

    pushFront(&dq, (State){S, 0});

    while (!isEmpty(&dq)) {
        State current = popFront(&dq);

        int u = current.vertex;
        int parity = current.parity;

        Edge *temp = adj[u];

        while (temp != NULL) {
            int v = temp->to;
            int w = temp->weight;

            int newParity;

            if (w == 0)
                newParity = parity;
            else
                newParity = 1 - parity;

            int newDistance = dist[u][parity] + w;

            if (newDistance < dist[v][newParity]) {
                dist[v][newParity] = newDistance;

                if (w == 0)
                    pushFront(&dq, (State){v, newParity});
                else
                    pushBack(&dq, (State){v, newParity});
            }

            temp = temp->next;
        }
    }

    printf("\nMinimum effective cost from source %d:\n", S);

    for (int v = 0; v < V; v++) {
        int answer = INF;

        if (dist[v][0] < answer)
            answer = dist[v][0];

        if (dist[v][1] != INF &&
            dist[v][1] + C < answer)
            answer = dist[v][1] + C;

        if (answer == INF)
            printf("Vertex %d : Unreachable\n", v);
        else
            printf("Vertex %d : %d\n", v, answer);
    }

    for (int i = 0; i < V; i++) {
        free(dist[i]);

        Edge *temp = adj[i];

        while (temp != NULL) {
            Edge *next = temp->next;
            free(temp);
            temp = next;
        }
    }

    free(dist);
    free(adj);

    while (!isEmpty(&dq))
        popFront(&dq);

    return 0;
}