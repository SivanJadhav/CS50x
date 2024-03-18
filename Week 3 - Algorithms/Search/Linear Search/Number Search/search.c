#include <cs50.h>
#include <stdio.h>

int main()
{
    int numbers[] = {20, 1, 3, 67, 40, 69, 50};

    int n = get_int("Number: ");

    for (int i = 0; i < 7; i++)
    {
        if (numbers[i] == n)
        {
            printf("Got It at %i location in array!\n", i + 1);
            return 0;
        }
    }
    printf("Not Here In Array!\n");
    return 1;
}
