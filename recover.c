/**
 * FILE: recover.c
 * DESCRIPTION:
 * A forensic utility that recovers JPEGs from a forensic image (raw data).
 * It scans 512-byte blocks looking for the distinct "magic bytes" that 
 * signal the start of a JPEG file.
 *
 * USAGE:
 * ./recover card.raw
 *
 * TECHNICAL CONCEPTS:
 * 1. File I/O: Uses fopen, fread, and fwrite to handle binary data streams.
 * 2. Bitwise Operations: Uses (file[3] & 0xf0) == 0xe0 to identify the 
 * fourth byte of a JPEG header (which can range from 0xe0 to 0xef).
 * 3. File Buffering: Processes data in 512-byte blocks, matching the
 * standard block size of FAT file systems.
 * 4. Dynamic Naming: Uses sprintf to generate incrementing filenames (000.jpg, 001.jpg).
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isJpeg(uint8_t *file);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./recover filename\n");
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
                printf("Couldn't create file %s\n", filename);
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
    // Scans the first 4 bytes for JPEG signatures: ff d8 ff e[0-f]
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
