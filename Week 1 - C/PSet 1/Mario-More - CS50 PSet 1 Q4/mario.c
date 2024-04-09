#include <stdio.h>

// Telling that this functions are present later in the code (To avoid error)
void prinths(int p);
void prints(int q);

int main(void)
{

    // Defining some Important Variables
    int h, hs, r, s;

    // Asks user for a positive integer between 1 and 8 inclusive
    do
    {
        h;

        printf("Height: ");

        scanf("%i", &h);
    }
    while (h < 1 || h > 8);

    // Initializing Variables (To avoid Unintialized error later)
    hs = 1;
    r = 1;

    for (int o = 0; o < h; o++)
    {

        // Number of Spaces Dermining Formula
        s = h - r;

        // Printing Spaces
        prints(s);

        // Printing Hashes
        prinths(hs);

        // Printing 2 Spaces
        prints(2);

        // Printing Hashes Again
        prinths(hs);

        // Move Cursor to the Next Line
        printf("\n");

        // Incrementing Variable
        hs++;
        r++;
    }
}

// Function for Printing Hashes ("#")
void prinths(int p)
{
    for (int i = 0; i < p; i++)
    {
        printf("#");
    }
}

// Funtion for Printing Spaces (" ")
void prints(int q)
{
    for (int w = 0; w < q; w++)
    {
        printf(" ");
    }
}
