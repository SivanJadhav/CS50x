// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Size
int size_x = 0;
int *size_of = &size_x;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table (prime number)
const unsigned int N = 65537;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Convert word to lowercase
    char lowercase_word[LENGTH + 1];
    int i = 0;
    while (word[i] != '\0')
    {
        lowercase_word[i] = tolower(word[i]);
        i++;
    }
    lowercase_word[i] = '\0';

    // Hashing The Word
    unsigned int hash_val = hash(lowercase_word);

    for (node *cursor = table[hash_val]; cursor != NULL; cursor = cursor->next)
    {
        if (strcasecmp(lowercase_word, cursor->word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash_val = 0;

    // Iterate over the characters of the word
    for (int i = 0; word[i] != '\0'; i++)
    {
        // Update hash_val using a simple operation
        hash_val += word[i];
    }

    // Return a simple hash value without mapping
    return hash_val;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Opening File
    FILE *source = fopen(dictionary, "r");

    if (source == NULL)
    {
        return false;
    }

    // Buffer To Read Words Into
    char BUFFER[LENGTH + 1];

    // Read Each Word
    while (fscanf(source, "%s", BUFFER) != EOF)
    {
        // Allocating Memory for New Node
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            fclose(source);
            return false;
        }

        // Add Each word
        strcpy(n->word, BUFFER);

        // Getting Hash Value
        unsigned int hash_val = hash(n->word);

        // Prepending It To The Hash Table's Index
        n->next = table[hash_val];
        table[hash_val] = n;

        (*size_of)++;
    }
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return (*size_of);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (unsigned int i = 0; i < N; i++)
    {
        for (node *cursor = table[i]; cursor != NULL;)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
