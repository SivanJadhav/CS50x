#include <stdio.h>

int main(void)
{
    // Defining Person Structure
    typedef struct
    {
        char *name;
        char *phone_number;
    } person;

    // Creating Queue Struct
    const int capacity = 50;

    typedef struct
    {
        person people[capacity];
        int size;
    } stack;
}