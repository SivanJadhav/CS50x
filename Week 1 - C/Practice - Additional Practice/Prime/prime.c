#include <math.h>
#include <stdio.h>
#include <stdbool.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        printf("Minimum: ");
        scanf("%d", &min);
    }
    while (min < 1);

    int max;
    do
    {
        printf("Maximum: ");
        scanf("%d", &max);
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    // If Number is One Return False
    if (number == 1)
    {
        return false;
    }
    // If Number is Two Return True
    if (number == 2)
    {
        return true;
    }

    // Finding Square Root of It
    int near_sqrt = ((int) round(sqrt(number)));

    // Calculating if it is prime
    for (int i = 2; i <= near_sqrt; i++)
    {
        if ((number % i) == 0)
        {
            return false;
        }
    }
    return true;
}
