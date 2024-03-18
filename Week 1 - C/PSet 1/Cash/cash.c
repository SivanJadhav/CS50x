#include <cs50.h>
#include <stdio.h>

// Declaring Variable for Amount Owed
int a;

// Declaring Coins Used Counter Variable
int cents;

// Declaring Coin Remainder Variables
int quarters;
int dimes;
int nickels;
int pennies;

// Defining Fuctions
// Algorithms for Finding Number of times a specific Coin is Used
void quarter();
void dime();
void nickel();
void penny();

int main(void)
{
    // Get Amount Owed Value from The User
    do
    {
        a = get_int("Amount Owed (¢): ");
    }
    while (a < 1);

    // Using greedyalg
    if (a >= 25)
    {
        quarter();
        a %= 25;
    }

    if (a >= 10 && a < 25)
    {
        dime();
        a %= 10;
    }

    if (a >= 5 && a < 10)
    {
        nickel();
        a %= 5;
    }

    if (a >= 1 && a < 5)
        penny();

    // Calculating Cents
    cents = quarters + dimes + nickels + pennies;

    // Printing amount of Coins Required
    printf("%i\n", cents);
}

// Algorithms for Finding How many times is a specific type of Coin is Used
// Quarters Used Algorithm
void quarter()
{
    quarters += a / 25;
    a %= 25;
}

// Dimes Used Algorithm
void dime()
{
    dimes += a / 10;
    a %= 10;
}

// Nickels Used Algorithm
void nickel()
{
    nickels += a / 5;
    a %= 5;
}

// Pennies Used Algorithm
void penny()
{
    pennies += a;
}
