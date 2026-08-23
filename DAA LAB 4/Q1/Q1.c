#include <stdio.h>
#include <string.h>

typedef struct {
    int number;
    char color;
} Item;

int main() {
    int n;

    printf("Enter number of items: ");
    scanf("%d", &n);

    Item items[n], red[n], blue[n], yellow[n], result[n];

    printf("Enter number and color (R/B/Y):\n");

    for (int i = 0; i < n; i++) {
        scanf("%d %c", &items[i].number, &items[i].color);
    }

    int r = 0, b = 0, y = 0;

    // Stable partition into three groups
    for (int i = 0; i < n; i++) {
        if (items[i].color == 'R')
            red[r++] = items[i];
        else if (items[i].color == 'B')
            blue[b++] = items[i];
        else if (items[i].color == 'Y')
            yellow[y++] = items[i];
    }

    // Combine: Red -> Blue -> Yellow
    int k = 0;

    for (int i = 0; i < r; i++)
        result[k++] = red[i];

    for (int i = 0; i < b; i++)
        result[k++] = blue[i];

    for (int i = 0; i < y; i++)
        result[k++] = yellow[i];

    printf("\nSorted by colour:\n");

    for (int i = 0; i < n; i++)
        printf("(%d, %c) ", result[i].number, result[i].color);

    printf("\n");

    return 0;
}