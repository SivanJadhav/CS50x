#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Initializing Some Variables That May Come Handy Later
int letters, words, sentences;
string text;
int len;

// Prototypes
int calc_letters(string text);
int calc_words(string text);
int calc_sentences(string text);

int main(void)
{
    // Taking User Text Input
    string input = get_string("Provide the Text: ");

    // Finding the Length of the Input
    len = strlen(input);

    // Calculating the Letters, Words and Sentences
    int letter = calc_letters(input);
    int word = calc_words(input);
    int sentence = calc_sentences(input);

    // Coleiman-Liau Index Calculator
    float L = (float) letter / word * 100;
    float S = (float) sentence / word * 100;

    float index = 0.0588 * L - 0.296 * S - 15.8;

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}

// Function for Calculating the Number of Letters in the Given Input
int calc_letters(string texts)
{
    letters = 0;

    for (int i = 0; i < len; i++)
    {
        if (islower(texts[i]))
        {
            letters++;
        }
        if (isupper(texts[i]))
        {
            letters++;
        }
    }

    return letters;
}

// Function for Calculating the Number of Words in the Given Input
int calc_words(string texts)
{
    words = 1;

    for (int i = 0; i < len; i++)
    {
        if (texts[i] == ' ')
        {
            words++;
        }
    }

    return words;
}

// Function for Calculating the Number of Sentences in the Given Input
int calc_sentences(string texts)
{
    sentences = 0;

    for (int i = 0; i < len; i++)
    {
        if (texts[i] == '.')
        {
            sentences++;
        }
        if (texts[i] == '!')
        {
            sentences++;
        }
        if (texts[i] == '?')
        {
            sentences++;
        }
    }

    return sentences;
}
