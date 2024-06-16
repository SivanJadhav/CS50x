#include <stdio.h>

// Telling that this functions are present later in the code (To avoid error)
void triangle(int n);

int main(void)
{
    // Defining and Initializing Variable
    int height = 0;

    // Asks user for a positive integer between 1 and 8 inclusive
    do
    {

        printf("Height: ");

        scanf("%i", &height);
    }
    while (height < 1 || height > 8);

    // Printing Triangles
    triangle(height);
}

// Function for Printing Triangle
void triangle(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1 - i; j >= 1; j--)
        {
            printf(" "); // Printing Spaces
        }
        for (int j = 1; j < i + 2; j++)
        {
            printf("#"); // Printing Hashes
        }
        printf("  ");

        for (int j = 1; j < i + 2; j++)
        {
            printf("#"); // Printing Hashes
        }

        printf("\n");
    }
}
