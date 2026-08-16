#include <stdio.h>

int comparisons = 0;

void maxMin(int a[], int low, int high, int *min, int *max)
{
    int min1, max1, min2, max2, mid;

    // Only one element
    if (low == high)
    {
        *min = *max = a[low];
        return;
    }

    // Two elements
    if (high == low + 1)
    {
        comparisons++;

        if (a[low] < a[high])
        {
            *min = a[low];
            *max = a[high];
        }
        else
        {
            *min = a[high];
            *max = a[low];
        }

        return;
    }

    // Divide
    mid = (low + high) / 2;

    // Conquer
    maxMin(a, low, mid, &min1, &max1);
    maxMin(a, mid + 1, high, &min2, &max2);

    // Combine
    comparisons++;
    *min = (min1 < min2) ? min1 : min2;

    comparisons++;
    *max = (max1 > max2) ? max1 : max2;
}

int main()
{
    int n, min, max;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int a[n];

    printf("Enter elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    maxMin(a, 0, n - 1, &min, &max);

    printf("\nMinimum = %d\n", min);
    printf("Maximum = %d\n", max);
    printf("Number of comparisons = %d\n", comparisons);

    return 0;
}