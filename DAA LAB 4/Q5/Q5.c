#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int start;
    int end;
} Interval;

/* Compare intervals by starting time */
int compare(const void *a, const void *b)
{
    Interval *i1 = (Interval *)a;
    Interval *i2 = (Interval *)b;

    return i1->start - i2->start;
}

int main()
{
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    Interval *intervals =
        (Interval *)malloc(n * sizeof(Interval));

    Interval *result =
        (Interval *)malloc(n * sizeof(Interval));

    if (intervals == NULL || result == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter intervals (start end):\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d",
              &intervals[i].start,
              &intervals[i].end);
    }

    /* Step 1: Sort intervals */
    qsort(intervals, n, sizeof(Interval), compare);

    /* Step 2: Initialize current interval */
    int resultCount = 0;

    int currentStart = intervals[0].start;
    int currentEnd = intervals[0].end;

    /* Step 3: Merge intervals */
    for (int i = 1; i < n; i++)
    {
        if (intervals[i].start <= currentEnd)
        {
            /* Intervals overlap */
            if (intervals[i].end > currentEnd)
                currentEnd = intervals[i].end;
        }
        else
        {
            /* No overlap */
            result[resultCount].start = currentStart;
            result[resultCount].end = currentEnd;
            resultCount++;

            currentStart = intervals[i].start;
            currentEnd = intervals[i].end;
        }
    }

    /* Add the last interval */
    result[resultCount].start = currentStart;
    result[resultCount].end = currentEnd;
    resultCount++;

    /* Print result */
    printf("\nMerged intervals:\n");

    for (int i = 0; i < resultCount; i++)
    {
        printf("(%d, %d) ",
               result[i].start,
               result[i].end);
    }

    printf("\n");

    free(intervals);
    free(result);

    return 0;
}