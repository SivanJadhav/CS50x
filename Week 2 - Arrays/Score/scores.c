#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Taking User Input of Scores
    int score1 = get_int("Give me a Score: ");
    int score2 = get_int("Give me a Score: ");
    int score3 = get_int("Give me a Score: ");

    // Calculating and Printing the Average
    printf("Average Score: %f\n", (score1 + score2 + score3) /3);
}
