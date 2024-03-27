#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *n = malloc(32);

    *n;

    printf("n: ");

    scanf("%c", &n);

    printf("N: %c\n", n);
}
