#include <stdio.h>
#include <stdlib.h>

/* Compare function for qsort */
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

/*
 * Checks whether k elements starting from index 'start'
 * can add up to target.
 */
int kSum(int arr[], int n, int start, int k, long long target)
{
    int i;

    /* Base case: 2-Sum */
    if (k == 2)
    {
        int left = start;
        int right = n - 1;

        while (left < right)
        {
            long long sum = (long long)arr[left] + arr[right];

            if (sum == target)
                return 1;

            if (sum < target)
                left++;
            else
                right--;
        }

        return 0;
    }

    /*
     * Fix one element and recursively search
     * for k-1 elements.
     */
    for (i = start; i <= n - k; i++)
    {
        /* Skip duplicate elements */
        if (i > start && arr[i] == arr[i - 1])
            continue;

        if (kSum(arr, n, i + 1, k - 1,
                 target - arr[i]))
            return 1;
    }

    return 0;
}

int main()
{
    int n, k, i;
    long long T;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    if (arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integers:\n", n);

    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter k: ");
    scanf("%d", &k);

    printf("Enter target T: ");
    scanf("%lld", &T);

    if (k < 2 || k > n)
    {
        printf("Invalid value of k.\n");
        free(arr);
        return 1;
    }

    /* Sort the input */
    qsort(arr, n, sizeof(int), compare);

    if (kSum(arr, n, 0, k, T))
        printf("YES: %d elements add up to %lld.\n", k, T);
    else
        printf("NO: No %d elements add up to %lld.\n", k, T);

    free(arr);

    return 0;
}