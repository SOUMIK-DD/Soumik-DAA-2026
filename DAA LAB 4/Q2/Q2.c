#include <stdio.h>
#include <stdlib.h>

// Compare function for qsort()
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Binary search
int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == key)
            return 1;

        if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return 0;
}

int main() {
    int n, x;

    printf("Enter size of sets: ");
    scanf("%d", &n);

    int S1[n], S2[n];

    printf("Enter elements of S1:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &S1[i]);

    printf("Enter elements of S2:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &S2[i]);

    printf("Enter target x: ");
    scanf("%d", &x);

    // Sort S2
    qsort(S2, n, sizeof(int), compare);

    // Search for x - S1[i] in S2
    for (int i = 0; i < n; i++) {
        int needed = x - S1[i];

        if (binarySearch(S2, n, needed)) {
            printf("Pair found: (%d, %d)\n", S1[i], needed);
            return 0;
        }
    }

    printf("No pair found.\n");

    return 0;
}