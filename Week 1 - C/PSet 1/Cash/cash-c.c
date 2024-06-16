#include <stdio.h>

// Declaring Variable for Amount Owed
int amount;

// Declaring Coins Used Counter Variable
int coins;

// Defining Fuctions
// Algorithms for Finding Number of times a specific Coin is Used
int greedy_alg(int amount);

int main(void)
{
    // Get Amount Owed Value from The User
    do
    {
        printf("Amount Owed (¢): ");
        scanf("%i", &amount);
    }
    while (amount < 1);

    coins = greedy_alg(amount);

    // Printing amount of Coins Required
    printf("%i\n", coins);
}

// Algorithms for Finding How many Coins are used
int greedy_alg(int amount)
{
    int counterr;

    int coins[4] = {25, 10, 5, 1};

    for(int i = 0; amount != 0; i++)
    {
        if (amount >= coins[i])
        {
            amount -= coins[i];
            counterr++;
        }
    }

    return counterr;
}