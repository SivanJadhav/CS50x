#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Creating Filetype
    uint8_t buffer[512];

    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    {
        return 1;
    }

    // While there's still data left to read from the memory card
    // Creating A Counter of Files Opened
    int counter = 0;
    FILE *image = NULL;
    char filename[12];

    // Loop For Reading Data
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Checking If The Data Is a Jpeg File
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // Closing File If Already Open
            if (image != NULL)
            {
                fclose(image);
            }

            // Creating A Jpeg File
            sprintf(filename, "%03i.jpg", counter);

            // Opening An Image
            image = fopen(filename, "w");

            if (image == NULL)
            {
                fclose(card);
                return 1;
            }

            // Writing Data Into It
            fwrite(buffer, 1, 512, image);

            // Incrementing The Counter
            counter++;
        }

        // Read Already Opened File
        else if (image != NULL)
        {
            // Writing Data Into It
            fwrite(buffer, 1, 512, image);
        }
    }

    // Closing Last Files
    fclose(card);

    if (image != NULL)
    {
        fclose(image);
    }
}
