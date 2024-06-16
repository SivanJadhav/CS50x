#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b);

int main(void)
{
    int *x = malloc(sizeof(int));
    int *y = malloc(sizeof(int));

    // Getting Value of X
    printf("x: ");

    scanf("%i", x);

    if (x == NULL)
    {
        return 1;
    }

    // Getting Value of Y
    printf("y: ");

    scanf("%i", y);
    
    if (y == NULL)
    {
        return 1;
    }

    printf("Before x Was: %i| Before y Was: %i\n", *x, *y);

    swap(x, y);

    printf("Now x Is: %i| Now y Is: %i\n", *x, *y);

    free(x);
    free(y);
}

void swap(int *a, int *b)
{
    int tmp = *b;

    *b = *a;

    *a = tmp;
}