#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hours(int hours[], int weeks, char output);

int main(void)
{
    int weeks = get_int("Number of weeks taking CS50: ");
    int hours[weeks];

    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("Week %i HW Hours: ", i);
    }

    char output;
    do
    {
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));
    }
    while (output != 'T' && output != 'A');

    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}

// TODO: complete the calc_hours function
float calc_hours(int hours[], int weeks, char output)
{
    // Declaring and Initializing a Variable
    int total_hours = 0;

    // Totalling Up the Hours
    for (int i = 0; i < weeks; i++)
    {
        total_hours += hours[i];
    }

    // Returning Total Hours If Asked by User
    if (output == 'T')
    {
        return total_hours;
    }

    // Returning Average of The Hours If Asked by User
    if (output == 'A')
    {
        float average = ((float) total_hours / weeks);

        return average;
    }
    return 1;
}
