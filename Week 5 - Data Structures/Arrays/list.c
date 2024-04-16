#include <stdio.h>

int main(void)
{
    // Creating A List Array
    int list[3];

    // Giving Value To Its Elements
    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    // Printing The Elemtents Of Array
    for (int i = 0; i < 3; i++)
    {
        printf("%i\n", list[i]);
    }
}