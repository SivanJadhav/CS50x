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
    for (int i = 0; i <= b; i++)
    {
        printf("#\n");
    }
}