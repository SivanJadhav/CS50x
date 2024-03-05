#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string name = get_string("Name: ");

    // Calculating the Length
    int length = strlen(name);

    printf("Length of the String is: %i\n", length);
}
