#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char buffer[8]; // 7 characters for the plate number + 1 for null terminator

    // Open the file
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    // Read and print plate numbers
    while (fgets(buffer, sizeof(buffer), infile) != NULL)
    {
        // Remove newline character if present
        buffer[strcspn(buffer, "\n")] = '\0';
        printf("%s\n", buffer);
    }

    // Close the file
    fclose(infile);

    return 0;
}
