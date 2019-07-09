#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "func.h"

int main()
{
    int no_coins;
    int amount;
    printf("Number of coins:\n");
    scanf("%d", &no_coins);
    printf("Amount:\n");
    scanf("%d", &amount);

    if (amount == 0)
    {
        printf("0");
        return 0;
    }
    if (amount < 0)
    {
        printf("Amount is a negative value!");
        return 0;
    }

    // used for computing running time of a code block
    clock_t start, finish;
    double  duration;

    int coins[no_coins];
    int cache[amount+1];

    for (size_t i = 0; i < amount + 1; i++)
    {
        cache[i] = 0;
    }

    printf("Coins:\n");
    for(size_t i = 0; i < no_coins; i++)
    {
        scanf("%d", &coins[i]);
    }

    start = clock();

    printf("\n Bottom up approach: \n");
    int c = recursiveTree(coins, amount, cache, no_coins);
    printf("%d\n", c);

    finish = clock();
    duration = ((float)(finish - start) / CLOCKS_PER_SEC) * 1000;
    printf("%.3fms\n", duration);

    start = clock();

    printf("\n Recursive tree approach: \n");
    int c1 = bottomUp(coins, amount, no_coins);
    printf("%d\n", c1);

    finish = clock();
    duration = ((float)(finish - start) / CLOCKS_PER_SEC) * 1000;
    printf("%.3fms\n", duration);
}
