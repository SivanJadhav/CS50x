// Debugged Code
#include <stdio.h>

// Prototyping brick printing function
void brick(int b);

int main(void)
{
    brick(3);
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