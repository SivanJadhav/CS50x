// Finds the arithmetic mean of the given Scores

#include <cs50.h>
#include <stdio.h>

// Constant
const int N = 3;

// Scores Variable
int scores[N];

// Prototype
float average(int length, int array[]);

int main(void)
{
    // Scores
    for (int i = 0; i < N; i++)
    {
        scores[i] = get_int("Score: ");
    }

    // Calculating and Printing the Average
    printf("Average Score: %f\n", average(N, scores));
}

// Average Function
float average(int length, int array[])
{
    // Divisor Value
    int divisor = 0;

    for (int z = 0; z < length; z++)
    {
        divisor += array[z];
    }

    return divisor / (float) length;
}
