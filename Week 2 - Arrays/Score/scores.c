#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Taking User Input of Scores
    double score1 = get_int("Give me a Score: ");
    double score2 = get_int("Give me a Score: ");
    double score3 = get_int("Give me a Score: ");

    // Calculating and Printing the Average
    printf("Average Score: %f\n", (score1 + score2 + score3) /3);
}
