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
            int avg =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
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
    RGBTRIPLE copy_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy_image[i][j].rgbtRed = image[i][j].rgbtRed;
            copy_image[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy_image[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][width - j - 1].rgbtRed = copy_image[i][j].rgbtRed;
            image[i][width - j - 1].rgbtGreen = copy_image[i][j].rgbtGreen;
            image[i][width - j - 1].rgbtBlue = copy_image[i][j].rgbtBlue;
        }
    }
    return;
}

// Blur image

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy_image[i][j].rgbtRed = image[i][j].rgbtRed;
            copy_image[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy_image[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    int grid = 3;

    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j<width; j++)
        {
            float sum_Red = 0, sum_Green = 0, sum_Blue = 0;
            int px_count = 0;

            for (int h = i-1; h <= i+1; h++)
            {
                for (int k = j-1; k <= j+1; k++)
                {
                    if (h >= 0 && k >= 0 &&
                        h < height && k < width)
                    {
                        sum_Red += copy_image[h][k].rgbtRed;
                        sum_Green += copy_image[h][k].rgbtGreen;
                        sum_Blue += copy_image[h][k].rgbtBlue;

                        px_count++;
                    }
                }
            }

            int avg_Red, avg_Green, avg_Blue;
            avg_Red = round(sum_Red/px_count);
            avg_Green = round(sum_Green/px_count);
            avg_Blue = round(sum_Blue/px_count);

            image[i][j].rgbtRed = avg_Red;
            image[i][j].rgbtGreen = avg_Green;
            image[i][j].rgbtBlue = avg_Blue;
        }
    }
    return;
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Gx and Gy kernels as matrixes
    int gx[3][3];
    int gy[3][3];

    gx[0][0] = -1; gx[0][1] = 0; gx[0][2] = 1;
    gx[1][0] = -2; gx[1][1] = 0; gx[1][2] = 2;
    gx[2][0] = -1; gx[2][1] = 0; gx[2][2] = 1;

    gy[0][0] =-1; gy[0][1] =-2; gy[0][2] =-1;
    gy[1][0] = 0; gy[1][1] = 0; gy[1][2] = 0;
    gy[2][0] = 1; gy[2][1] = 2; gy[2][2] = 1;

    RGBTRIPLE copy_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy_image[i][j].rgbtRed = image[i][j].rgbtRed;
            copy_image[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy_image[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    int grid = 3;
    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j<width; j++)
        {
            float gx_Red=0, gx_Green=0, gx_Blue=0, gy_Red=0, gy_Green=0, gy_Blue=0;
            for (int h = -1; h < grid-1; h++)
            {
                for (int k = -1; k < grid-1; k++)
                {
                    if (i + h < 0 || i + h > height-1 ||
                        k + j < 0 || k + j > width-1)
                    {
                        continue;
                    }
                    else
                    {
                        gx_Red += copy_image[i+h][j+k].rgbtRed * gx[h+1][k+1];
                        gx_Green += copy_image[i+h][j+k].rgbtGreen * gx[h+1][k+1];
                        gx_Blue += copy_image[i+h][j+k].rgbtBlue * gx[h+1][k+1];

                        gy_Red += copy_image[i+h][j+k].rgbtRed * gy[h+1][k+1];
                        gy_Green += copy_image[i+h][j+k].rgbtGreen * gy[h+1][k+1];
                        gy_Blue += copy_image[i+h][j+k].rgbtBlue * gy[h+1][k+1];
                    }
                }
            }

            int v_red = round(sqrt((gx_Red*gx_Red)+(gy_Red*gy_Red)));
            if (v_red < 0)
            {
                v_red = 0;
            }
            else if(v_red > 255)
            {
                v_red = 255;
            }

            int v_green = round(sqrt((gx_Green*gx_Green)+(gy_Green*gy_Green)));
            if (v_green < 0)
            {
                v_green = 0;
            }
            else if(v_green > 255)
            {
                v_green = 255;
            }

            int v_blue = round(sqrt((gx_Blue*gx_Blue)+(gy_Blue*gy_Blue)));
            if (v_blue < 0)
            {
                v_blue = 0;
            }
            else if(v_blue > 255)
            {
                v_blue = 255;
            }

            image[i][j].rgbtRed = v_red;
            image[i][j].rgbtGreen = v_green;
            image[i][j].rgbtBlue = v_blue;
        }
    }

    return;
}
