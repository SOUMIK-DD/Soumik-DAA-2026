#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int point;
    int type;       // +1 = start, -1 = end
} Event;

/* Compare events */
int compare(const void *a, const void *b)
{
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    /* Sort by point */
    if (e1->point != e2->point)
        return e1->point - e2->point;

    /*
     * If points are equal, start (+1)
     * must come before end (-1)
     */
    return e2->type - e1->type;
}

int main()
{
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    Event *events = (Event *)malloc(2 * n * sizeof(Event));

    if (events == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter intervals (left right):\n");

    for (int i = 0; i < n; i++)
    {
        int l, r;

        scanf("%d %d", &l, &r);

        /* Start event */
        events[2 * i].point = l;
        events[2 * i].type = 1;

        /* End event */
        events[2 * i + 1].point = r;
        events[2 * i + 1].type = -1;
    }

    /* Sort all events */
    qsort(events, 2 * n, sizeof(Event), compare);

    int current = 0;
    int maxCount = 0;
    int bestPoint = 0;

    /* Sweep through events */
    for (int i = 0; i < 2 * n; i++)
    {
        current += events[i].type;

        if (current > maxCount)
        {
            maxCount = current;
            bestPoint = events[i].point;
        }
    }

    printf("\nPoint with maximum overlap = %d\n", bestPoint);
    printf("Maximum number of intervals = %d\n", maxCount);

    free(events);

    return 0;
}