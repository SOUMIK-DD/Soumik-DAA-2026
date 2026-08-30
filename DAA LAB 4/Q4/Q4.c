#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int time;
    int type;   // +1 = entry, -1 = exit
} Event;

/* Comparator for qsort */
int compare(const void *a, const void *b)
{
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    return e1->time - e2->time;
}

int main()
{
    int n;

    printf("Enter number of persons: ");
    scanf("%d", &n);

    Event *events = malloc(2 * n * sizeof(Event));

    if (events == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter entry and exit time for each person:\n");

    for (int i = 0; i < n; i++)
    {
        int entry, exit;

        printf("Person %d: ", i + 1);
        scanf("%d %d", &entry, &exit);

        events[2 * i].time = entry;
        events[2 * i].type = 1;

        events[2 * i + 1].time = exit;
        events[2 * i + 1].type = -1;
    }

    /* Sort all events by time */
    qsort(events, 2 * n, sizeof(Event), compare);

    int current = 0;
    int maxPeople = 0;
    int maxTime = 0;

    /* Sweep through sorted events */
    for (int i = 0; i < 2 * n; i++)
    {
        current += events[i].type;

        if (current > maxPeople)
        {
            maxPeople = current;
            maxTime = events[i].time;
        }
    }

    printf("\nMaximum number of people present = %d\n", maxPeople);
    printf("Time when maximum occurred = %d\n", maxTime);

    free(events);

    return 0;
}