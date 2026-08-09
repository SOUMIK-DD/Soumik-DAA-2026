#include <stdio.h>
#include <stdlib.h>

long long count1, count2;

/* Merge two sorted arrays */
void merge(int a[], int b[], int c[], int n1, int n2, long long *count)
{
    int i = 0, j = 0, k = 0;

    while (i < n1 && j < n2)
    {
        (*count)++;

        if (a[i] <= b[j])
            c[k++] = a[i++];
        else
            c[k++] = b[j++];
    }

    while (i < n1)
        c[k++] = a[i++];

    while (j < n2)
        c[k++] = b[j++];
}


/* ---------- METHOD 1 ---------- */

long long method1(int n, int k)
{
    int *result;
    int *temp;

    int size = n;

    result = malloc(n * sizeof(int));

    /* First sorted array */
    for (int i = 0; i < n; i++)
        result[i] = i * k;

    count1 = 0;

    for (int arr = 1; arr < k; arr++)
    {
        temp = malloc((size + n) * sizeof(int));

        int *next = malloc(n * sizeof(int));

        for (int i = 0; i < n; i++)
            next[i] = i * k + arr;

        merge(result, next, temp, size, n, &count1);

        free(result);
        free(next);

        result = temp;
        size += n;
    }

    free(result);

    return count1;
}


/* ---------- METHOD 2 ---------- */

long long method2(int n, int k)
{
    int arrays = k;
    int size = n;

    count2 = 0;

    while (arrays > 1)
    {
        arrays /= 2;
        size *= 2;

        /* At every level, kn elements are processed */
        count2 += (long long)k * n;
    }

    return count2;
}


/* ---------- MAIN ---------- */

int main()
{
    FILE *fp;

    int n_values[] = {100, 200, 500, 1000};
    int k_values[] = {2, 4, 8, 16, 32};

    fp = fopen("data1.txt", "w");

    if (fp == NULL)
    {
        printf("Error creating data1.txt\n");
        return 1;
    }

    fprintf(fp, "# n k Method1 Method2\n");

    for (int i = 0; i < 4; i++)
    {
        int n = n_values[i];

        for (int j = 0; j < 5; j++)
        {
            int k = k_values[j];

            long long m1 = method1(n, k);
            long long m2 = method2(n, k);

            printf("n=%d k=%d  Method1=%lld  Method2=%lld\n",
                   n, k, m1, m2);

            fprintf(fp, "%d %d %lld %lld\n",
                    n, k, m1, m2);
        }
    }

    fclose(fp);

    printf("\nData saved to data1.txt\n");

    return 0;
}