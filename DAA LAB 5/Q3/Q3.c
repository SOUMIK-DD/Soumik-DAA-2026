#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);

    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    /* Generate random numbers and store in file */
    FILE *fp = fopen("random.txt", "w");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    srand(time(NULL));

    printf("\nRandom elements:\n");

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000;

        printf("%d ", arr[i]);
        fprintf(fp, "%d ", arr[i]);
    }

    fclose(fp);

    /* Read elements from file */
    fp = fopen("random.txt", "r");

    if (fp == NULL)
    {
        printf("\nError opening file.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        fscanf(fp, "%d", &arr[i]);
    }

    fclose(fp);

    /* Quick Sort */
    quickSort(arr, 0, n - 1);

    printf("\n\nSorted elements:\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");

    return 0;
}