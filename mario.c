/*
    Mario Double-Pyramid

    This program draws a double half‑pyramid of a user‑specified height,
    similar to the “Mario” problem from CS50. The user is prompted to
    enter a height, and the program validates the input before printing
    two side‑by‑side pyramids separated by two spaces.

    Features:
    - Prompts the user for a height value
    - Validates that the height is within an acceptable range
    - Prints left and right pyramids aligned by height
    - Uses only standard C input/output functions

    For testing provide a value between 1-9
    Expected output:
    
    Height: 6
         #  #
        ##  ##
       ###  ###
      ####  ####
     #####  #####
    ######  ######

*/

#include <stdio.h>

void draw_pyramid(int totalHeight);

int main()
{
    int height = -1;
    do
    {
        if (height < 1)
        {
            printf("Choose a number between 1 and 9\n");
        }
        else
        {
            printf("Choose a number between 1 and 9\n");
        }

        printf("Height: ");
        scanf("%d", &height);

    }
    while (height <= 0 || height >= 100);

    draw_pyramid(height);
}

void draw_pyramid(int totalHeight)
{

    for (int i = 0; i < totalHeight; i++)
    {
        for (int j = 0; j < totalHeight - (i + 1); j++)
        {
            printf(" ");
        }
        for (int h = 0; h < totalHeight - (totalHeight - (i + 1)); h++)
        {
            printf("#");
        }
        for (int l = 0; l < 2; l++)
        {
            printf(" ");
        }
        for (int h = 0; h < totalHeight - (totalHeight - (i + 1)); h++)
        {
            printf("#");
        }

        printf("\n");
    }
}