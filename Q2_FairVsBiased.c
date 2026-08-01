#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int n, i;
    int heads = 0, tails = 0;

    printf("Enter number of tosses: ");
    scanf("%d", &n);

    srand(time(NULL));

    heads = tails = 0;

    for(i = 0; i < n; i++)
    {
        if(rand() % 2 == 0)
            heads++;
        else
            tails++;
    }

    printf("\n--- Fair Coin ---\n");
    printf("Heads = %d\n", heads);
    printf("Tails = %d\n", tails);
    printf("Probability of Head = %.4f\n",
           (float)heads / n);

    heads = tails = 0;

    for(i = 0; i < n; i++)
    {
        double r = (double)rand() / RAND_MAX;

        if(r < 0.7)
            heads++;
        else
            tails++;
    }

    printf("\n--- Biased Coin (70%% Head) ---\n");
    printf("Heads = %d\n", heads);
    printf("Tails = %d\n", tails);
    printf("Probability of Head = %.4f\n",
           (float)heads / n);

    return 0;
}