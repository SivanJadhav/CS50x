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

    // Giving Next A Adress
    n->next = NULL;

    // Making List Equivalent To It
    list = n;

    // Checking By printf
    printf("%d - List's Number\n", list->number);
    printf("%p - List's Next Adress\n", list->next);

    // Linking Something New To It
    node *n1 = malloc(sizeof(node));

    n1->number = 2;
    n1->next = list;

    list = n1;

    printf("%p - Next of List", list->next);

    // Freeing Things
    free(n);
    free(n1);
}