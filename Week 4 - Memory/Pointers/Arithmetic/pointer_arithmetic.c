#include <stdio.h>

int main(void)
{
    int i = 0;

    char *s = "HI!";

    while (i != \0)
    {
        printf("%c\n", *s);
        i++;
    }
}
