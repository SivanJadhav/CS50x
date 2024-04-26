// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Function Prototype
string replace(string word);

int main(int argc, string argv[])
{
    // Checking for Potential Errors
    if (argc != 2)
    {
        printf("Usage: ./no-vowels word\n");
        return 1;
    }

    // Calling Replace Function
    printf("%s\n", replace(argv[1]));
}

// Replace Function: Takes in an word, replaces its vowels with relevant characters
string replace(string word)
{
    // Iterating Through Each Letter
    for (int i = 0, string_length = strlen(word); i < string_length; i++)
    {
        switch (word[i])
        {
            case 'a':
                word[i] = '6';
                break;
            case 'e':
                word[i] = '3';
                break;
            case 'i':
                word[i] = '1';
                break;
            case 'o':
                word[i] = '0';
                break;
            default:
                word[i] = word[i];
                break;
        }
    }
    // Returning String
    return word;
}
