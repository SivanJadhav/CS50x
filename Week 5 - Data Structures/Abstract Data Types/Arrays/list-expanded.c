#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Constant Int For Array Length
    const int array_length = 4;
    
    // Creating A List Array
    int *list = malloc(3 * sizeof(int));

    if (list == NULL)
    {
        printf("Error");
        return 1;
    }

    // Giving Value To Its Elements
    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    // Expanding The Array
    int *tmp = malloc(array_length * sizeof(int));

    if (tmp == NULL)
    {
        free(list);
        return 1;
    }

    // Copying The Old Array
    for (int i = 0; i < 3; i++)
    {
        tmp[i] = list[i];
    }

    tmp[3] = 4;

    // Freeing The Old List
    free(list);

    // Changing List's Old Elements
    list = tmp;

    // Printing The Elemtents Of Array
    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", list[i]);
    }

    free(list);
    return 0;
}