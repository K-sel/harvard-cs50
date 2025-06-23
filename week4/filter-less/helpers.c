#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg;
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            avg = (image[row][col].rgbtBlue + image[row][col].rgbtGreen + image[row][col].rgbtRed) / 3.0;

            image[row][col].rgbtBlue = round(avg);
            image[row][col].rgbtGreen = round(avg);
            image[row][col].rgbtRed = round(avg);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE originalRed;
    BYTE originalGreen;
    BYTE originalBlue;
    int sepiaRed, sepiaGreen, sepiaBlue;

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            originalRed = image[row][col].rgbtRed;
            originalGreen = image[row][col].rgbtGreen;
            originalBlue = image[row][col].rgbtBlue;

            sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            if (sepiaRed > 255) sepiaRed = 255;
            if (sepiaGreen > 255) sepiaGreen = 255;
            if (sepiaBlue > 255) sepiaBlue = 255;

            image[row][col].rgbtRed = sepiaRed;
            image[row][col].rgbtGreen = sepiaGreen;
            image[row][col].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width / 2; col++)
        {
            tmp = image[row][col];
            image[row][col] = image[row][width - 1 - col];
            image[row][width - 1 - col] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    float avgRed = 0;
    float avgGreen = 0;
    float avgBlue = 0;
    int count = 0;
    int newRow;
    int newCol;

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            avgRed = 0;
            avgGreen = 0;
            avgBlue = 0;
            count = 0;

            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    newRow = row + i;
                    newCol = col + j;

                    if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width)
                    {
                        avgRed += copy[newRow][newCol].rgbtRed;
                        avgGreen += copy[newRow][newCol].rgbtGreen;
                        avgBlue += copy[newRow][newCol].rgbtBlue;
                        count++;
                    }
                }
            }

            image[row][col].rgbtRed = round(avgRed / count);
            image[row][col].rgbtGreen = round(avgGreen / count);
            image[row][col].rgbtBlue = round(avgBlue / count);
        }
    }
    return;
}
