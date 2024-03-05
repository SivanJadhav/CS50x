#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Prototype for Score Calculator
int score_calc(string word);

// Score to Be Given Respective to Its Location in the Alphabet
int scores[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    // Getting the Word Inputs of Players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Calculating the Scores
    int score1 = score_calc(word1);
    int score2 = score_calc(word2);

    // Printing the Winner or Tie
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int score_calc(string word)
{
    // Initializing the Score Value to 0
    int score = 0;

    // Calculating the Score
    for (int i = 0, length = strlen(word); i < length; i++)
    {
        // If Uppercase
        if (isupper(word[i]))
        {
            score += scores[word[i] - 'A'];
        }

        // If Lowercase
        if (islower(word[i]))
        {
            score += scores[word[i] - 'a'];
        }
    }

    return score;
}
