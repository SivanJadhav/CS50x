#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototypes
int usage_error();

int main(int argc, string argv[])
{
    // Number of Arguments Test
    // Not Taking More Than 2 Arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Converting and Declaring Argv[1] as Key
    int key = atoi(argv[1]);

    // Non-Negative Integer Check
    for (int i = 0, len = strlen(argv[1]); i < len; i++)
    {
        if (isalpha(argv[1][i]))
        {
            usage_error();
            return 1;
        }
        if (key < 0)
        {
            usage_error();
            return 1;
        }
    }

    // Taking Plaintext
    string plaintxt = get_string("plaintext:  ");

    // Enchiphering and Printing
    if (key > 25)
    {
        key -= 26;
    }

    // Printing Cyphertext
    printf("ciphertext: ");

    // Enciphering
    for (int i = 0, len = strlen(plaintxt); i < len; i++)
    {
        if (isupper(plaintxt[i]))
        {
            printf("%c", (plaintxt[i] - 65 + key) % 26 + 65);
        }
        else if (islower(plaintxt[i]))
        {
            printf("%c", (plaintxt[i] - 97 + key) % 26 + 97);
        }
        else
        {
            printf("%c", plaintxt[i]);
        }
    }
    printf("\n");
}

int usage_error()
{
    printf("Usage: ./caesar key\n");
    return 1;
}
