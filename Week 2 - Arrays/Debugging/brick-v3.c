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
        // Found the error, and fixed it. From i <= b --> i < b.
        printf("i is %i", i);
        
        // Print Brick and move to next line
        printf("#\n");
    }
}