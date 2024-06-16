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

    for (int i = 0; i < argc; i++)
    {
        int number = atoi(argv[i]);

        node *n = malloc(sizeof(node));

        n->number = number;
        n->next = NULL;

        if (n == NULL)
        {
            free(list);
            return 1;
        }

        if (list == NULL)
        {
            list = n;
        }

        else
        {
            for (node *ptr = list; ptr != NULL; ptr = ptr->next)
            {
                if (ptr->next == NULL)
                {
                    ptr->next = n;
                    break;
                }
            }
        }
    }

    for (node *ptr = list; ptr->next != NULL; ptr = ptr->next)
    {
        printf("%i\n", list->number);
    }
}
