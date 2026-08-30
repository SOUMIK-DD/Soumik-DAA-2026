#include <stdio.h>
#include <stdlib.h>

long long count2, count3;

/* ---------- 2-WAY MERGE SORT ---------- */

void merge2(int a[], int l, int m, int r)
{
    int i = l, j = m + 1, k = 0;
    int n = r - l + 1;
    int *temp = (int *)malloc(n * sizeof(int));

    while (i <= m && j <= r)
    {
        count2++;

        if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= m)
        temp[k++] = a[i++];

    while (j <= r)
        temp[k++] = a[j++];

    for (i = l, k = 0; i <= r; i++, k++)
        a[i] = temp[k];

    free(temp);
}

void mergeSort2(int a[], int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;

        mergeSort2(a, l, m);
        mergeSort2(a, m + 1, r);

        merge2(a, l, m, r);
    }
}


/* ---------- 3-WAY MERGE SORT ---------- */

void merge3(int a[], int l, int m1, int m2, int r)
{
    int i = l;
    int j = m1 + 1;
    int k = m2 + 1;
    int x = 0;

    int n = r - l + 1;
    int *temp = (int *)malloc(n * sizeof(int));

    while (i <= m1 || j <= m2 || k <= r)
    {
        int min = 1000000000;

        if (i <= m1)
        {
            count3++;
            if (a[i] < min)
                min = a[i];
        }

        if (j <= m2)
        {
            count3++;
            if (a[j] < min)
                min = a[j];
        }

        if (k <= r)
        {
            count3++;
            if (a[k] < min)
                min = a[k];
        }

        temp[x++] = min;

        if (i <= m1 && a[i] == min)
            i++;
        else if (j <= m2 && a[j] == min)
            j++;
        else
            k++;
    }

    for (i = l, x = 0; i <= r; i++, x++)
        a[i] = temp[x];

    free(temp);
}

void mergeSort3(int a[], int l, int r)
{
    if (l < r)
    {
        int n = r - l + 1;

        int third = n / 3;

        int m1 = l + third - 1;
        int m2 = l + 2 * third - 1;

        /* Handle small subarrays */
        if (third == 0)
        {
            if (a[l] > a[r])
            {
                int temp = a[l];
                a[l] = a[r];
                a[r] = temp;
            }
            return;
        }

        mergeSort3(a, l, m1);
        mergeSort3(a, m1 + 1, m2);
        mergeSort3(a, m2 + 1, r);

        merge3(a, l, m1, m2, r);
    }
}


/* ---------- MAIN ---------- */

int main()
{
    FILE *fp;
    int sizes[] = {
        100, 200, 500, 1000, 2000,
        5000, 10000, 20000, 50000
    };

    int total = sizeof(sizes) / sizeof(sizes[0]);

    fp = fopen("data.txt", "w");

    if (fp == NULL)
    {
        printf("Error creating file.\n");
        return 1;
    }

    fprintf(fp, "# n  2-way  3-way\n");

    for (int s = 0; s < total; s++)
    {
        int n = sizes[s];

        int *a = (int *)malloc(n * sizeof(int));
        int *b = (int *)malloc(n * sizeof(int));

        /* Same input for both algorithms */
        for (int i = 0; i < n; i++)
        {
            a[i] = n - i;
            b[i] = n - i;
        }

        count2 = 0;
        count3 = 0;

        mergeSort2(a, 0, n - 1);
        mergeSort3(b, 0, n - 1);

        fprintf(fp, "%d %lld %lld\n",
                n, count2, count3);

        printf("n = %d : 2-way = %lld , 3-way = %lld\n",
               n, count2, count3);

        free(a);
        free(b);
    }

    fclose(fp);

    /* Create gnuplot script */
    fp = fopen("plot.gp", "w");

    fprintf(fp,
        "set title '2-Way vs 3-Way Merge Sort'\n"
        "set xlabel 'Input Size (n)'\n"
        "set ylabel 'Number of Comparisons'\n"
        "set grid\n"
        "plot 'data.txt' using 1:2 with linespoints "
        "title '2-Way Merge Sort', "
        "'data.txt' using 1:3 with linespoints "
        "title '3-Way Merge Sort'\n");

    fclose(fp);

    printf("\nData saved in data.txt\n");
    printf("Run gnuplot using: gnuplot plot.gp\n");

    return 0;
}