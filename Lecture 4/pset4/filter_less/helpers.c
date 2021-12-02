#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Average of all the rgb values and round off
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int ogBlue = image[i][j].rgbtBlue;
            int ogRed = image[i][j].rgbtRed;
            int ogGreen = image[i][j].rgbtGreen;

            // Sepia Formula to calculate the sepia tone of each pixel
            int sepiaRed = round(.393 * ogRed + .769 * ogGreen + .189 * ogBlue);
            int sepiaGreen = round(.349 * ogRed + .686 * ogGreen + .168 * ogBlue);
            int sepiaBlue = round(.272 * ogRed + .534 * ogGreen + .131 * ogBlue);

            // Check edge cases where value of color is greater than 255.
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            // Apply the color to the image
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap the pixel colors 1st and last and so on..

            // Temp Variable to store the value of the rgb color
            int tempBlue = image[i][j].rgbtBlue;
            int tempRed = image[i][j].rgbtRed;
            int tempGreen = image[i][j].rgbtGreen;

            // store it in the value
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;

            // Store the temp variables in the actual location
            image[i][width - j - 1].rgbtBlue = tempBlue;
            image[i][width - j - 1].rgbtRed = tempRed;
            image[i][width - j - 1].rgbtGreen = tempGreen;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create temp array to store og pixels
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalR = 0, totalG = 0, totalB = 0, count = 0;
            int li = i - 1, lj = j - 1, ui = i + 1, uj = j + 1;

            // Corner edge cases to reduce the limits
            // Lower Limit
            if (li < 0)
            {
                li = 0;
            }
            if (lj < 0)
            {
                lj = 0;
            }

            // Upper Limit
            if (ui > height - 1)
            {
                ui = height - 1;
            }
            if (uj > width - 1)
            {
                uj = width - 1;
            }

            // Iterate over each pixel
            for (int k = li; k <= ui; k++)
            {
                for (int l = lj; l <= uj; l++)
                {
                    // Calculate total rgb values and count
                    totalR += temp[k][l].rgbtRed;
                    totalG += temp[k][l].rgbtGreen;
                    totalB += temp[k][l].rgbtBlue;
                    count++;
                }
            }

            // Calculate averages
            int avgR = round((float)(totalR) / count);
            int avgG = round((float)(totalG) / count);
            int avgB = round((float)(totalB) / count);

            // Store in actual location
            image[i][j].rgbtRed = avgR;
            image[i][j].rgbtGreen = avgG;
            image[i][j].rgbtBlue = avgB;
        }
    }
    return;
}
