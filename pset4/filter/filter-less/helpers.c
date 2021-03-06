#include "helpers.h"
#include <math.h> // this is needed for round
// Convert image to grayscale

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avrg = (image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen);
            image[i][j].rgbtRed = round(avrg / 3.0); // divide by 3.0 to cast the operation to float
            image[i][j].rgbtBlue = round(avrg / 3.0);
            image[i][j].rgbtGreen = round(avrg / 3.0);
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaR = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaG = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaB = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            image[i][j].rgbtRed = sepiaR < 255 ? sepiaR : 255;
            image[i][j].rgbtGreen = sepiaG < 255 ? sepiaG : 255;
            image[i][j].rgbtBlue = sepiaB < 255 ? sepiaB : 255;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++) //we loop until half the image
        {
            temp = image[i][j];
            image[i][j] = image[i][(width - 1) - j]; // minus 1 because we start counting from 0
            image[i][(width - 1) - j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create a new pixel data structure with all the attributes needed for this function
    typedef struct
    {
        float rSum;
        float gSum;
        float bSum;
        float cnt;
    } RGBTRIPLEBLUR;

    RGBTRIPLEBLUR temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j].rSum = 0;
            temp[i][j].gSum = 0;
            temp[i][j].bSum = 0;
            temp[i][j].cnt = 0;

            // k and l are used to loop the surroundings of the pixel, they can be -1, 0 or 1, that way we get the 9 pixels surrounding the current pixel (included)
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (i + k >= 0 && i + k < height && j + l >= 0 && j + l < width)
                    {
                        temp[i][j].rSum += image[i + k][j + l].rgbtRed;
                        temp[i][j].gSum += image[i + k][j + l].rgbtBlue;
                        temp[i][j].bSum += image[i + k][j + l].rgbtGreen;
                        temp[i][j].cnt++;
                    }
                }
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = round(temp[i][j].rSum / temp[i][j].cnt);
            image[i][j].rgbtBlue = round(temp[i][j].gSum / temp[i][j].cnt);
            image[i][j].rgbtGreen = round(temp[i][j].bSum / temp[i][j].cnt);
        }
    }
}
