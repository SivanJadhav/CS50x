#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Average
            int average = (int) round(
                ((float) (image[i][j].rgbtRed) + (image[i][j].rgbtBlue) + (image[i][j].rgbtGreen)) /
                3.0);

            // Update Pixel
            image[i][j].rgbtRed = average;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Algorithm
            int sepia_value[3]; // [0] == Red, [1] == Green, [2] == Blue

            sepia_value[0] =
                (int) round((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) +
                            (0.189 * image[i][j].rgbtBlue));
            sepia_value[1] =
                (int) round((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) +
                            (0.168 * image[i][j].rgbtBlue));
            sepia_value[2] =
                (int) round((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) +
                            (0.131 * image[i][j].rgbtBlue));

            for (int k = 0; k < 3; k++)
            {
                if (sepia_value[k] > 255)
                {
                    sepia_value[k] = 255;
                }
                else
                {
                    break;
                }
            }

            // update
            image[i][j].rgbtRed = sepia_value[0];
            image[i][j].rgbtGreen = sepia_value[1];
            image[i][j].rgbtBlue = sepia_value[2];
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE arr_rev[height][width];

    // Loop
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            arr_rev[i][j].rgbtRed = image[i][(width - 1) - j].rgbtRed;
            arr_rev[i][j].rgbtGreen = image[i][(width - 1) - j].rgbtGreen;
            arr_rev[i][j].rgbtBlue = image[i][(width - 1) - j].rgbtBlue;
        }
        for (int k = 0; k < width; k++)
        {
            // Writing new Data
            image[i][k].rgbtRed = arr_rev[i][k].rgbtRed;
            image[i][k].rgbtGreen = arr_rev[i][k].rgbtGreen;
            image[i][k].rgbtBlue = arr_rev[i][k].rgbtBlue;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary image array to hold blurred values
    RGBTRIPLE copy[height][width];

    // Iterate over each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0, sumGreen = 0, sumBlue = 0;
            int count = 0;

            // Iterate over neighboring pixels
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // Check if neighboring pixel is within bounds
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        // Accumulate RGB values
                        sumRed += image[ni][nj].rgbtRed;
                        sumGreen += image[ni][nj].rgbtGreen;
                        sumBlue += image[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculate average RGB values
            copy[i][j].rgbtRed = round((float) sumRed / count);
            copy[i][j].rgbtGreen = round((float) sumGreen / count);
            copy[i][j].rgbtBlue = round((float) sumBlue / count);
        }
    }

    // Copy blurred values back to original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
}
