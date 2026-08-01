#include <stdio.h>

int findPartition(int arr[], int n)
{
    int low = 0, high = n - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == 0)
        {
            low = mid + 1;
        }
        else
        {
            if (mid == 0 || arr[mid - 1] == 0)
                return mid;

            high = mid - 1;
        }
    }

    return -1;
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter elements (0s followed by 1s):\n");

    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int partition = findPartition(arr, n);

    if(partition == -1)
        printf("No transition point found (all elements are 0).\n");
    else
        printf("Transition point (first 1) is at index %d\n", partition);

    return 0;
}