/**
 * FILE: volume.c
 * DESCRIPTION:
 * Modifies the volume of a WAV file by scaling each audio sample by a 
 * specified factor. It preserves the 44-byte WAV header while 
 * manipulating the 16-bit audio data that follows.
 *
 * USAGE:
 * ./volume input.wav output.wav factor
 * * LOGIC:
 * 1. Header Preservation: Reads and writes the first 44 bytes (HEADER_SIZE) 
 * without modification to ensure the output remains a valid WAV file.
 * 2. Sample Scaling: Iterates through the rest of the file in 2-byte 
 * (int16_t) increments, multiplying each by the provided float 'factor'.
 * 3. File I/O: Uses binary read/write modes to handle the raw audio data.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    // Using "rb" and "wb" is technically more standard for binary files
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input to output
    uint8_t header_section[HEADER_SIZE];
    fread(header_section, HEADER_SIZE, 1, input);
    fwrite(header_section, HEADER_SIZE, 1, output);

    // Read single samples from input file and write updated data to output file
    int16_t buffer;
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
