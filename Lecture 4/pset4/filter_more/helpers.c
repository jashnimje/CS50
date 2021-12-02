#include "helpers.h"
#include <math.h>
#include <stdio.h>

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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

    // Weighted array
    int xArr[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int yArr[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int li = i - 1, lj = j - 1, ui = i + 1, uj = j + 1;
            int gxRed = 0, gxGreen = 0, gxBlue = 0, gyRed = 0, gyBlue = 0, gyGreen = 0;

            // Iterate over each pixel
            for (int k = li; k <= ui; k++)
            {
                for (int l = lj; l <= uj; l++)
                {
                    int pRed = temp[k][l].rgbtRed;
                    int pGreen = temp[k][l].rgbtGreen;
                    int pBlue = temp[k][l].rgbtBlue;

                    // Excluding lower limit and upper limit
                    if (!(k < 0 || l < 0 || k > height - 1 || l > width - 1))
                    {
                        gxRed += pRed * xArr[k - li][l - lj];
                        gxGreen += pGreen * xArr[k - li][l - lj];
                        gxBlue += pBlue * xArr[k - li][l - lj];

                        gyRed += pRed * yArr[k - li][l - lj];
                        gyGreen += pGreen * yArr[k - li][l - lj];
                        gyBlue += pBlue * yArr[k - li][l - lj];
                    }
                }
            }

            int value;

            // Calculate the Red Pixel
            value = round(sqrt((gxRed * gxRed) + (gyRed * gyRed)));
            if (value > 255)
            {
                value = 255;
            }
            image[i][j].rgbtRed = value;


            // Calculate the Green Pixel
            value = round(sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)));
            if (value > 255)
            {
                value = 255;
            }
            image[i][j].rgbtGreen = value;


            // Calculate the Blue Pixel
            value = round(sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)));
            if (value > 255)
            {
                value = 255;
            }
            image[i][j].rgbtBlue = value;

        }
    }
    return;
}
