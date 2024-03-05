#include <cs50.h>
#include <stdio.h>

int string_length(string name_of_person);

int i;

int main(void)
{
    string name = get_string("Name: ");

    // Calculating the Length
    int length = string_length(name);

    printf("Length of the String is: %i\n", i);
}

int string_length(string name_of_person)
{
    i = 0;

    while (name_of_person[i] != '\0')
    {
        i++;
    }

    return i;
}
