#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // Calculating String Length
    int strln = ((strlen(input)));

    // Base Case
    if (strln == 1)
    {
        return input[0] - 48;
    }

    else
    {
        // Getting The Last Char
        int last_char = input[strln - 1] - 48;

        // Shortening the String
        input[strln - 1] = '\0';

        return (last_char + 10 * convert(input));
    }
}
