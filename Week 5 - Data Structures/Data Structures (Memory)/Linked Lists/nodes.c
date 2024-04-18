#include <stdio.h>
#include <stdlib.h>

// Node Structure
typedef struct node
{
    int number;
    struct node *next;
} node;

int main(void)
{
    // Creating A Node
    node *list = NULL;

    // Temporary Node Pointer
    node *n = malloc(sizeof(node));

    if (n == NULL)
    {
        return 1;
    }

    // Giving It A Int Value
    n->number = 1;

    // Giving It A Adress
    n->next =  NULL;

    // Making List Equivalent To It 
    list = n;
}