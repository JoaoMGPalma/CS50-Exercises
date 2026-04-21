#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isJpeg(uint8_t *file);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./recover filename");
        return 1;
    }

    char *infile = argv[1];

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    // Handles output file naming
    char *naming_pattern = "###.jpg";
    char filename[strlen(naming_pattern) + 1];

    // Read file data
    uint8_t buffer[512];
    int file_count = 0;
    FILE *outfile = NULL;

    while (fread(buffer, 1, 512, inptr))
    {
        if (isJpeg(buffer))
        {
            // First image found
            if (file_count != 0)
            {
                fclose(outfile);
            }

            // Create a new image with naming pattern "###.jpg"
            sprintf(filename, "%03i.jpg", file_count);
            outfile = fopen(filename, "w");

            if (outfile == NULL)
            {
                printf("Couldn't create file %s", filename);
                return 2;
            }

            file_count++;
        }

        // Continue writing to the previous image found
        if (outfile != NULL)
        {
            fwrite(buffer, 1, 512, outfile);
        }
    }

    // Memory clear
    if (outfile != NULL)
    {
        fclose(outfile);
    }

    fclose(inptr);

    return 0;
}

int isJpeg(uint8_t *file)
{
    if (file[0] == 0xff)
    {
        if (file[1] == 0xd8)
        {
            if (file[2] == 0xff)
            {
                if ((file[3] & 0xf0) == 0xe0)
                {
                    return 1;
                }
            }
        }
    }

    return 0;
}
