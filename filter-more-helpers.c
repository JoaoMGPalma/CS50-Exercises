/**
 * FILE: filter.c
 * DESCRIPTION:
 * A collection of image processing filters designed to manipulate 24-bit 
 * BMP images. This file implements four core computer vision techniques:
 * Grayscale, Horizontal Reflection, Box Blur, and Sobel Edge Detection.
 *
 * USAGE:
 * Part of a larger BMP manipulation suite. Functions operate on a 2D array
 * of RGBTRIPLE structs representing the image pixels.
 *
 * ALGORITHMS:
 * 1. Grayscale: Averages RGB values for each pixel.
 * 2. Reflection: Swaps pixels horizontally across the center axis.
 * 3. Box Blur: Applies a 3x3 kernel averaging the color of a pixel with its 
 * surrounding neighbors.
 * 4. Sobel Edge Detection: Uses Gx and Gy convolution kernels to calculate
 * the gradient magnitude of color changes, effectively finding edges.
 */

#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Average the three color channels
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            
            // Standard cap at 255 for 8-bit color channels
            if (avg > 255)
            {
                avg = 255;
            }

            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Process row by row
    for (int i = 0; i < height; i++)
    {
        // Only iterate halfway through the width to swap
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy to read from so original values aren't lost mid-process
    RGBTRIPLE copy_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy_image[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sum_Red = 0, sum_Green = 0, sum_Blue = 0;
            int px_count = 0;

            // Iterate through 3x3 grid centered on pixel [i][j]
            for (int h = i - 1; h <= i + 1; h++)
            {
                for (int k = j - 1; k <= j + 1; k++)
                {
                    // Boundary check
                    if (h >= 0 && k >= 0 && h < height && k < width)
                    {
                        sum_Red += copy_image[h][k].rgbtRed;
                        sum_Green += copy_image[h][k].rgbtGreen;
                        sum_Blue += copy_image[h][k].rgbtBlue;
                        px_count++;
                    }
                }
            }

            image[i][j].rgbtRed = round(sum_Red / px_count);
            image[i][j].rgbtGreen = round(sum_Green / px_count);
            image[i][j].rgbtBlue = round(sum_Blue / px_count);
        }
    }
    return;
}

// Detect edges (Sobel Operator)
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Gx and Gy kernels
    int gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int gy[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    RGBTRIPLE copy_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy_image[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float gx_Red = 0, gx_Green = 0, gx_Blue = 0;
            float gy_Red = 0, gy_Green = 0, gy_Blue = 0;

            for (int h = -1; h <= 1; h++)
            {
                for (int k = -1; k <= 1; k++)
                {
                    // Boundary check: skip if outside image bounds
                    if (i + h < 0 || i + h >= height || j + k < 0 || j + k >= width)
                    {
                        continue;
                    }

                    gx_Red   += copy_image[i + h][j + k].rgbtRed   * gx[h + 1][k + 1];
                    gx_Green += copy_image[i + h][j + k].rgbtGreen * gx[h + 1][k + 1];
                    gx_Blue  += copy_image[i + h][j + k].rgbtBlue  * gx[h + 1][k + 1];

                    gy_Red   += copy_image[i + h][j + k].rgbtRed   * gy[h + 1][k + 1];
                    gy_Green += copy_image[i + h][j + k].rgbtGreen * gy[h + 1][k + 1];
                    gy_Blue  += copy_image[i + h][j + k].rgbtBlue  * gy[h + 1][k + 1];
                }
            }

            // Calculate final magnitude: sqrt(Gx^2 + Gy^2)
            int v_red   = round(sqrt(gx_Red * gx_Red + gy_Red * gy_Red));
            int v_green = round(sqrt(gx_Green * gx_Green + gy_Green * gy_Green));
            int v_blue  = round(sqrt(gx_Blue * gx_Blue + gy_Blue * gy_Blue));

            image[i][j].rgbtRed   = (v_red > 255) ? 255 : v_red;
            image[i][j].rgbtGreen = (v_green > 255) ? 255 : v_green;
            image[i][j].rgbtBlue  = (v_blue > 255) ? 255 : v_blue;
        }
    }
    return;
}
