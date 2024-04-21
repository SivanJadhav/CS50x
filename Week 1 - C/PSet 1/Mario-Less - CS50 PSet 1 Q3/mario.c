#include <cs50.h>
#include <stdio.h>

// Telling that this functions are present later in the code (To avoid error)
void triangle(int n);

int main(void)
{
    // Declaring And Initializing Height Variable
    int height = 0;

    // Asks user for a positive integer
    do
    {
        height;
        printf("Height: ");
        scanf("%d", &height);
    }
    while (height < 1);

    // Printing Triangle Staircase
    triangle(height);
}

// Function for Printing Triangles
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
		printf("\n");
	}
}