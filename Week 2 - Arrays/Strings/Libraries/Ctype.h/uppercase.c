#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string b = get_string("Before:  ");

    printf("After: ");

    for (int i = 0, n = strlen(b); i < n; i++)
    {
        printf("%c", toupper(b[i]));
    }
    printf("\n");
}
