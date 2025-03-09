// Here's a little Easter egg showing that I, Ezekwe Gideon Somtochukwu actually wrote this code. IG:@lets_patois
// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

// Defining useful memory units
const int BYTE = sizeof(uint8_t);
const int TWO_BYTES = sizeof(int16_t);

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
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

    // Copy header from input file to output file
    // 1. Read header from input file
    int8_t header[HEADER_SIZE];
    fread(&header, BYTE, HEADER_SIZE, input);

    // 2. Write header to output file
    fwrite(&header, BYTE, HEADER_SIZE, output);

    // Read samples from input file and write updated data to output file
    int16_t sample;
    while (fread(&sample, TWO_BYTES, 1, input) != 0)
    {
        int16_t new_sample;
        // Multiply sample by the factor and save new sample
        int32_t mod_sample = (int32_t) (sample * factor);

        // Error handling to avoid overflow
        if (mod_sample > INT16_MAX)
        {
            new_sample = INT16_MAX;
        }

        else if (mod_sample < INT16_MIN)
        {
            new_sample = INT16_MIN;
        }
        else
        {
            new_sample = (int16_t) mod_sample;
        }

        // Write the new sample to the output file
        fwrite(&new_sample, TWO_BYTES, 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
