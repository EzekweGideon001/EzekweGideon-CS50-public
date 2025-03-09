// Here's a little Easter egg showing that I, Ezekwe Gideon Somtochukwu actually wrote this code. IG:@lets_patois
#include "helpers.h"
#include <stdint.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over each row
    for (int i = 0; i < height; i++)
    {
        // Loop over each pixel
        for (int j = 0; j < width; j++)
        {
            // Take an average of the rgb values
            BYTE average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue + 1) / 3;

            // Modify the rgb values of all pixel to be equal to the average
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over each row
    for (int i = 0; i < height; i++)
    {
        // Loop over each pixel
        for (int j = 0; j < width; j++)
        {
            // Extract the original rgb values
            BYTE originalRed = image[i][j].rgbtRed;
            BYTE originalGreen = image[i][j].rgbtGreen;
            BYTE originalBlue = image[i][j].rgbtBlue;

            // Use the values to apply the sepia filter
            float sepiaRed = .393f * originalRed + .769f * originalGreen + .189f * originalBlue;
            float sepiaGreen = .349f * originalRed + .686f * originalGreen + .168f * originalBlue;
            float sepiaBlue = .272f * originalRed + .534f * originalGreen + .131f * originalBlue;

            // Round the values and clamp them to the range [0, 255]. Made use of fminf, fmaxf and roundf from math.h (learnt from youtube and internet research)
            image[i][j].rgbtRed = (BYTE)fminf(255.0f, fmaxf(0.0f, roundf(sepiaRed)));
            image[i][j].rgbtGreen = (BYTE)fminf(255.0f, fmaxf(0.0f, roundf(sepiaGreen)));
            image[i][j].rgbtBlue = (BYTE)fminf(255.0f, fmaxf(0.0f, roundf(sepiaBlue)));
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over each row
    for (int i = 0; i < height; i++)
    {
        // Loop over the first half of the row
        for (int j = 0; j < width / 2; j++)
        {
            // Store the current rgb values in temporary variables
            BYTE temp_red = image[i][j].rgbtRed;
            BYTE temp_green = image[i][j].rgbtGreen;
            BYTE temp_blue = image[i][j].rgbtBlue;

            // Replace values with the opposite pixel
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            // Replace opposite values with the one's temporarily stored
            image[i][width - j - 1].rgbtRed = temp_red;
            image[i][width - j - 1].rgbtGreen = temp_green;
            image[i][width - j - 1].rgbtBlue = temp_blue;
        }
    }
    return;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the original image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Loop through each row in the image
    for (int i = 0; i < height; i++)
    {
        // Loop through each pixel
        for (int j = 0; j < width; j++)
        {
            int sum_red = 0;
            int sum_green = 0;
            int sum_blue = 0;
            int count = 0;

            // Loop through the neighboring pixels (3x3 grid)
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // Verify if the neighbor is within the bounds of the image
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        sum_red += copy[ni][nj].rgbtRed;
                        sum_green += copy[ni][nj].rgbtGreen;
                        sum_blue += copy[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculate the average RGB values and assign them to the pixel. Made use of round function from math.h (learnt from YouTube and internet) and type conversion
            // Make sure to avoid division by zero
            if (count > 0)
            {
                image[i][j].rgbtRed = (int)round((double)sum_red / count);
                image[i][j].rgbtGreen = (int)round((double)sum_green / count);
                image[i][j].rgbtBlue = (int)round((double)sum_blue / count);
            }
        }
    }
}
