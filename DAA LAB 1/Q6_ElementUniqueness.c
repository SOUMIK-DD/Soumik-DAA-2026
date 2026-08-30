#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    int n;

    printf("Enter the number of random elements: ");
    scanf("%d", &n);

    int arr[n];

    srand(time(NULL));

    
    printf("\nGenerated Numbers:\n");
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000;
        printf("%d ", arr[i]);
    }

    
    qsort(arr, n, sizeof(int), compare);

    int duplicate = 0;

    for (int i = 1; i < n; i++)
    {
        if (arr[i] == arr[i - 1])
        {
            duplicate = 1;
            printf("\n\nDuplicate found: %d\n", arr[i]);
            break;
        }
    }

    if (!duplicate)
    {
        printf("\n\nAll elements are unique.\n");
    }

    return 0;
}