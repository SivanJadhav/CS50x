#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b);

int main(void)
{
    int x = 5;
    int y = 11;

    printf("Before x was: %i, and y was: %i\n", x, y);

    swap(&x, &y);

    printf("After x is: %i, and y is: %i\n", x, y);
}

void swap(int *a, int *b)
{
    int tmp = *a;

    *a = *b;

    *b = tmp;
}
