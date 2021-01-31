/*********************************************************************************
 * helpers.c
 *
 * Programmeren 1
 *
 * Rivka Vollebregt
 * 12164968
 *
 * helpers contains the functions for filter.c.
 * The functions are
 * - grayscale: convert image into grayscale
 * - sepia: convert image into sepia
 * - reflect: mirrors the image
 * - blur: blurs the image
*********************************************************************************/

#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate over every row
    for (int row = 0; row < height; row++)
    {
        // iterate over every column with pixels
        for (int column = 0; column < width; column++)
        {
            // calculate the average of the three colours,
            // (add the number of red, blue and green and divide it by 3)
            int scale = round((image[row][column].rgbtRed
                               + image[row][column].rgbtBlue
                               + image[row][column].rgbtGreen) / 3.0);

            // assign new colour value to rgbt.red, blue and green resprectively
            image[row][column].rgbtRed = scale;
            image[row][column].rgbtBlue = scale;
            image[row][column].rgbtGreen = scale;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            // calculate new colour values for sepia-Red, Blue and Green
            int sepia_red = round(.393 * image[row][column].rgbtRed +
                                  .769 * image[row][column].rgbtGreen +
                                  .189 * image[row][column].rgbtBlue);
            int sepia_green = round(.349 * image[row][column].rgbtRed +
                                    .686 * image[row][column].rgbtGreen +
                                    .168 * image[row][column].rgbtBlue);
            int sepia_blue = round(.272 * image[row][column].rgbtRed +
                                   .534 * image[row][column].rgbtGreen +
                                   .131 * image[row][column].rgbtBlue);

            // if the sepiaRed value is larger than 255, change into 255
            if (sepia_red > 255)
            {
                sepia_red = 255;
            }

            // if the sepiaGreen value is larger than 255, change into 255
            if (sepia_green > 255)
            {
                sepia_green = 255;
            }

            // if the sepiaBlue value is larger than 255, change into 255
            if (sepia_blue > 255)
            {
                sepia_blue = 255;
            }

            // assign the new sepia colour values to rgbt.red, blue and green
            image[row][column].rgbtRed = sepia_red;
            image[row][column].rgbtBlue = sepia_blue;
            image[row][column].rgbtGreen = sepia_green;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        // for half of the column, switch the pixel from position with pixel at other half
        for (int column = 0; column < width / 2; column++)
        {
            // switch RGB information of current column with pixel at width - column
            // do this using temporary RGBTRIPLE tempReverse
            RGBTRIPLE temp_reverse = image[row][column];
            image[row][column] = image[row][width - column - 1];
            image[row][width - column - 1] = temp_reverse;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // make temporary RGBTRIPLE with same dimensions as image
    RGBTRIPLE temp[height][width];

    // copy image into temp
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            temp[row][column] = image[row][column];
        }
    }

    // calculate new value for every pixel: average of 3x3 surrounding pixels
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            float counter = 0;
            int sum_red = 0, sum_blue = 0, sum_green = 0;

            // adds rbg of current pixel to sum
            if (row >= 0 && column >= 0)
            {
                sum_red += temp[row][column].rgbtRed;
                sum_green += temp[row][column].rgbtGreen;
                sum_blue += temp[row][column].rgbtBlue;
                counter++;
            }

            // if current pixel is in top row, left column, skip
            // adds rbg of top left pixel to sum
            if (row - 1 >= 0 && column - 1 >= 0)
            {
                sum_red += temp[row - 1][column - 1].rgbtRed;
                sum_green += temp[row - 1][column - 1].rgbtGreen;
                sum_blue += temp[row - 1][column - 1].rgbtBlue;
                counter++;
            }

            // if current pixel is in top row, skip
            // adds rbg of top pixel to sum
            if (row - 1 >= 0 && column >= 0)
            {
                sum_red += temp[row - 1][column].rgbtRed;
                sum_green += temp[row - 1][column].rgbtGreen;
                sum_blue += temp[row - 1][column].rgbtBlue;
                counter++;
            }

            // if current pixel is in last column or in top row, skip
            // adds rbg of top right pixel to sum
            if ((row - 1 >= 0 && column + 1 >= 0) && (row - 1 >= 0 && column + 1 < width))
            {
                sum_red += temp[row - 1][column + 1].rgbtRed;
                sum_green += temp[row - 1][column + 1].rgbtGreen;
                sum_blue += temp[row - 1][column + 1].rgbtBlue;
                counter++;
            }

            // if current pixel is in left column, skip
            // adds rbg of left pixel to sum
            if (row >= 0 && column - 1 >= 0)
            {
                sum_red += temp[row][column - 1].rgbtRed;
                sum_green += temp[row][column - 1].rgbtGreen;
                sum_blue += temp[row][column - 1].rgbtBlue;
                counter++;
            }

            // if current pixel is in last column, skip
            // adds rbg of right pixel to sum
            if ((row >= 0 && column + 1 >= 0) && (row >= 0 && column + 1 < width))
            {
                sum_red += temp[row][column + 1].rgbtRed;
                sum_green += temp[row][column + 1].rgbtGreen;
                sum_blue += temp[row][column + 1].rgbtBlue;
                counter++;
            }

            // if current pixel is in last row or left column, skip
            // adds rbg of bottom left pixel to sum
            if ((row + 1 >= 0 && column - 1 >= 0) && (row + 1 < height && column - 1 >= 0))
            {
                sum_red += temp[row + 1][column - 1].rgbtRed;
                sum_green += temp[row + 1][column - 1].rgbtGreen;
                sum_blue += temp[row + 1][column - 1].rgbtBlue;
                counter++;
            }

            // if current pixel is in last row, skip
            // adds rbg of bottom pixel to sum
            if ((row + 1 >= 0 && column >= 0) && (row + 1 < height && column >= 0))
            {
                sum_red += temp[row + 1][column].rgbtRed;
                sum_green += temp[row + 1][column].rgbtGreen;
                sum_blue += temp[row + 1][column].rgbtBlue;
                counter++;
            }

            // if current pixel is in last row or last column, skip
            // adds rbg of bottom right pixel to sum
            if ((row + 1 >= 0 && column + 1 >= 0) && (row + 1 < height && column + 1 < width))
            {
                sum_red += temp[row + 1][column + 1].rgbtRed;
                sum_green += temp[row + 1][column + 1].rgbtGreen;
                sum_blue += temp[row + 1][column + 1].rgbtBlue;
                counter++;
            }

            // calculate average values and assign to image
            image[row][column].rgbtRed = roundf(sum_red / counter);
            image[row][column].rgbtBlue = roundf(sum_blue / counter);
            image[row][column].rgbtGreen = roundf(sum_green / counter);
        }
    }

    return;
}
