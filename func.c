#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "func.h"

//Function that returns the minimum of 2 values
int mini(int a, int b)
{
    if (a < b)
    {
        return a;
    }
    else if (b < a)
    {
        return b;
    }
    else if (a == b)
    {
        return a;
    }

    return -1;
}


int bottomUp(int coins[], int amount, int no_coins)
{
    //We need an array to cache the answers to our subproblems
    int cache[amount+1];

    /*
    We fill the array with default values, amount + 1, arbitrary value.
    The arbitrary value must be grater than our amount;
    */
    for (size_t i = 0; i < amount + 1; i++)
    {
        cache[i] = amount + 1;
    }

    /*
    The minimum coins to make change for 0 will always be 0,
    we need to state this in order to solve the subproblems;
    */
    cache[0] = 0;

    /*
    We solve every subproblem starting with 1 up to the amount
    and cache the answers;
    */
    for (size_t i = 1; i <= amount; i++)
    {
        /*
        We take every coin and solve it's subproblem,
        if the coins is less or equal to the subproblem amount
        we compare it to the last cached solution an see if it gives us a more optimal solution;
        */
        for (size_t j = 0; j < no_coins; j++)
        {
            if (coins[j] <= i)
            {
                /*
                E.g. for i = 2; j = 0; Coins: 1 2 5;

                coins[0] = 1;
                i = 2;
                1 <= 2 (TRUE)
                cache[i] = 12;
                cache[2] = mini(12, (2-1) + 1) (returns 2)
                ==> cache[i] = 2; first found solution for this subproblem is 2, we go on and increment j;

                j = 1;
                coins[1] = 2
                i = 2;
                2 <= 2(TRUE)
                cache[i] = 2;
                cache[2] = mini(2, (2-2) + 1) (return 1)
                ==> cache[i] = 1; second found solution for this subproblem is 1, we go on and increment j;

                j = 2;
                coins[2] = 5;
                5 <= 2 (FALSE);
                WE STOP, the best solution for this subproblem is 1, and we cached it;
                */
                cache[i] = mini(cache[i], cache[i - coins[j]] + 1);
            }
        }
    }

    /*
    If we don't have an answer, cache[amount] will be greater
    than the amount (equal to amount+1, the arbitrary value) so we will return -1,
    else we just return out cached solution of the amount which is the solution we
    are looking for;
    */
    if (cache[amount] > amount)
    {
        return -1;
    }
    else
    {
        return cache[amount];
    }
}

int recursiveTree(int coins[], int amount, int cache[], int no_coins)
{
    //If the amount to make change for is 0 we return 0;
    if (amount == 0)
    {
        return 0;
    }
    //If the amount to make change for is negative we return -1;
    if (amount < 0)
    {
        return -1;
    }
    //If we have the answer cached we return it;
    if (cache[amount] != 0)
    {
        return cache[amount];
    }

    //Set the minimum to an arbitrary big value
    int minimum = INT_MAX;
    int result = 0;

    //For each
    for (size_t i = 0; i < no_coins; i++)
    {
        //We go depth first and solve all subproblem's caching the answers
        result = recursiveTree(coins, amount - coins[i], cache, no_coins);

        //If possible to make change and the result is better we add 1 to the smallest value
        if (result >= 0 && result < minimum)
        {
            minimum = result + 1;
        }
    }
    //If we find no answer we return -1, otherwise the subproblem's answer is minimum so we cache it;
    if (minimum == INT_MAX)
    {
        cache[amount] = -1;
    }
    else
    {
        cache[amount] = minimum;
    }

    //Return the subproblem's cached answer;
    return cache[amount];
}
