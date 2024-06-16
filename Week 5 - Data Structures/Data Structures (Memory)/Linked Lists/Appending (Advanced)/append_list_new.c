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

        else if (n->number < list->number)
        {
            n->next = list;
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
                else if (n->number < ptr->next->number)
                {
                    n->next = ptr->next;
                    ptr->next = n;
                    break;
                }
            }
        }
    }

    node *ptr = list;

    while (ptr != NULL)
    {
        printf("%i\n", ptr->number);
        ptr = ptr->next;
    }
}
