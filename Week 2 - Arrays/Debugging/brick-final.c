#include <cs50.h>
#include <stdio.h>

// Prototyping brick printing function
void brick(int b);

int main(void)
{
    // Taking User Input
    int h = get_int("Height of Collumn: ");

    brick(h);
}

// Brick Printing Function
void brick(int b)
{
    for (int i = 0; i < b; i++)
    {
        // Print Brick and move to next line
        printf("#\n");
    }
}
