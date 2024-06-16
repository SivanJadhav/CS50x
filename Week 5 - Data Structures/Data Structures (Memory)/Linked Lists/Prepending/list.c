#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int number;
    struct node *next;
} node;

int main(int argc, char *argv[])
{
    node *list = NULL;

    for (int i = argc - 1; i >= 1; i--)
    {
        int number = atoi(argv[i]);

        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            free(list);
            return 1;
        }

        n->number = number;
        n->next = list;
        list = n;
    }

    // Print Whole List
    node *ptr = list;
    while (ptr != NULL)
    {
        printf("%i\n", ptr->number);
        ptr = ptr->next;
    }

    // Freeing Stuff
    free(list);
    free(ptr);
}