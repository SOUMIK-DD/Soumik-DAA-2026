#include <stdio.h>

int defectiveCoin(int a[], int left, int right, int good)
{
    // Only one candidate coin remains
    if (left == right)
    {
        if (a[left] < a[good])
            return left;       // defective coin found
        else
            return -1;         // no defective coin
    }

    int mid = (left + right) / 2;

    int leftSum = 0, rightSum = 0;

    // Calculate weight of left half
    for (int i = left; i <= mid; i++)
        leftSum += a[i];

    // Calculate weight of right half
    for (int i = mid + 1; i <= right; i++)
        rightSum += a[i];

    if (leftSum < rightSum)
        return defectiveCoin(a, left, mid, good);

    else if (rightSum < leftSum)
        return defectiveCoin(a, mid + 1, right, good);

    else
        return -1;   // Both halves equal -> no defective coin
}

int main()
{
    int n;

    printf("Enter number of coins: ");
    scanf("%d", &n);

    int a[n];

    printf("Enter weights of coins:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    // Assume coin 0 is initially the known-good reference.
    // In practice, for this simple implementation, use a normal/reference
    // coin supplied separately.
    int good = 0;

    int result = defectiveCoin(a, 1, n - 1, good);

    if (result == -1)
        printf("No defective coin found.\n");
    else
        printf("Defective coin is coin %d.\n", result + 1);

    return 0;
}