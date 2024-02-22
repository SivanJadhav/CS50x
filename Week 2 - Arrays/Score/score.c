#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Taking User Input of Scores
    int scores[3];

    for (int i = 0; i < 3; i++)
    {
        scores[i] = get_int("Score: ");
    }
    
    // Calculating and Printing the Average
    printf("Average Score: %f\n", (scores[0] + scores[1] + scores[2]) /3.0);
}
