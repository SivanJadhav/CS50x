#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main()
{
    string strings[4] = {"battleship", "hello", "poop", "daunting"};

    string s = get_string("String: ");

    for (int i = 0; i < 4; i++)
    {
        if (strcmp(strings[i], s) == 0)
        {
            printf("Got It at %i location in array!\n", i + 1);
            return 0;
        }
    }
    printf("Not Here In Array!\n");
    return 1;
}
