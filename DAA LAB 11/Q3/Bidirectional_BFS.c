
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXL 10

typedef unsigned long long ULL;

ULL hashWord(const char *s) {
    ULL h = 1469598103934665603ULL;

    while (*s) {
        h ^= (unsigned char)*s++;
        h *= 1099511628211ULL;
    }

    return h;
}

int findWord(const char *s, char words[][MAXL + 1],
             int *table, int mask) {
    int pos = (int)(hashWord(s) & (ULL)mask);

    while (table[pos] != 0) {
        int idx = table[pos] - 1;

        if (strcmp(words[idx], s) == 0)
            return idx;

        pos = (pos + 1) & mask;
    }

    return -1;
}

void insertWord(int idx, char words[][MAXL + 1],
                int *table, int mask) {
    int pos = (int)(hashWord(words[idx]) & (ULL)mask);

    while (table[pos] != 0)
        pos = (pos + 1) & mask;

    table[pos] = idx + 1;
}

/* Expand one complete BFS layer.
   Return 1 if the searches meet; otherwise return 0. */
int expandLayer(
    int *front, int frontSize,
    int *next, int *nextSize,
    int *dist, int *otherDist,
    char words[][MAXL + 1],
    int *table, int mask, int L,
    int *answer
) {
    *nextSize = 0;

    for (int i = 0; i < frontSize; i++) {
        int u = front[i];

        char original = words[u][0];

        for (int pos = 0; pos < L; pos++) {
            original = words[u][pos];

            for (char ch = 'a'; ch <= 'z'; ch++) {
                if (ch == original)
                    continue;

                words[u][pos] = ch;

                int v = findWord(words[u], words,
                                 table, mask);

                if (v == -1)
                    continue;

                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    next[(*nextSize)++] = v;
                }

                if (otherDist[v] != -1) {
                    *answer = dist[v] + otherDist[v];
                    words[u][pos] = original;
                    return 1;
                }
            }

            words[u][pos] = original;
        }
    }

    return 0;
}

int main(void) {
    int N, L;

    printf("Enter number of dictionary words N and word length L: ");

    if (scanf("%d %d", &N, &L) != 2 ||
        N < 1 || N > 100000 || L < 1 || L > MAXL) {
        printf("Invalid input.\n");
        return 1;
    }

    char (*words)[MAXL + 1] =
        malloc((N + 1) * sizeof(*words));

    if (words == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter dictionary words:\n");

    for (int i = 0; i < N; i++) {
        if (scanf("%10s", words[i]) != 1 ||
            (int)strlen(words[i]) != L) {
            printf("Invalid word length.\n");
            free(words);
            return 1;
        }
    }

    char A[MAXL + 1], B[MAXL + 1];

    printf("Enter starting word A and target word B: ");

    if (scanf("%10s %10s", A, B) != 2 ||
        (int)strlen(A) != L || (int)strlen(B) != L) {
        printf("Invalid starting or target word.\n");
        free(words);
        return 1;
    }

    // Hash table size: power of two, with low load factor.
    int capacity = 1;

    while (capacity < 2 * (N + 1))
        capacity *= 2;

    int mask = capacity - 1;
    int *table = calloc(capacity, sizeof(int));

    if (table == NULL) {
        printf("Memory allocation failed.\n");
        free(words);
        return 1;
    }

    for (int i = 0; i < N; i++) {
        if (findWord(words[i], words, table, mask) != -1) {
            printf("Dictionary words must be unique.\n");
            free(table);
            free(words);
            return 1;
        }

        insertWord(i, words, table, mask);
    }

    int target = findWord(B, words, table, mask);

    if (target == -1) {
        printf("Target word B must be in the dictionary.\n");
        free(table);
        free(words);
        return 1;
    }

    int start = findWord(A, words, table, mask);

    // A need not be in the dictionary.
    if (start == -1) {
        start = N;
        strcpy(words[start], A);
        insertWord(start, words, table, mask);
        N++;
    }

    if (start == target) {
        printf("Minimum mutations: 0\n");
        free(table);
        free(words);
        return 0;
    }

    int *distA = malloc(N * sizeof(int));
    int *distB = malloc(N * sizeof(int));
    int *frontA = malloc(N * sizeof(int));
    int *frontB = malloc(N * sizeof(int));
    int *nextA = malloc(N * sizeof(int));
    int *nextB = malloc(N * sizeof(int));

    if (!distA || !distB || !frontA || !frontB ||
        !nextA || !nextB) {
        printf("Memory allocation failed.\n");
        free(distA); free(distB);
        free(frontA); free(frontB);
        free(nextA); free(nextB);
        free(table); free(words);
        return 1;
    }

    for (int i = 0; i < N; i++)
        distA[i] = distB[i] = -1;

    distA[start] = 0;
    distB[target] = 0;

    frontA[0] = start;
    frontB[0] = target;

    int sizeA = 1, sizeB = 1;
    int answer = -1;

    while (sizeA > 0 && sizeB > 0) {
        int found, nextSize;

        // Expand the smaller frontier.
        if (sizeA <= sizeB) {
            found = expandLayer(
                frontA, sizeA, nextA, &nextSize,
                distA, distB, words, table, mask, L,
                &answer
            );

            if (found)
                break;

            int *temp = frontA;
            frontA = nextA;
            nextA = temp;
            sizeA = nextSize;
        } else {
            found = expandLayer(
                frontB, sizeB, nextB, &nextSize,
                distB, distA, words, table, mask, L,
                &answer
            );

            if (found)
                break;

            int *temp = frontB;
            frontB = nextB;
            nextB = temp;
            sizeB = nextSize;
        }
    }

    printf("Minimum mutations: %d\n", answer);

    free(distA);
    free(distB);
    free(frontA);
    free(frontB);
    free(nextA);
    free(nextB);
    free(table);
    free(words);

    return 0;
}
