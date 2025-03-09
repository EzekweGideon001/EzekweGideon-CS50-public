// Here's a little Easter egg showing that I, Ezekwe Gideon Somtochukwu actually wrote this code. IG:@lets_patois
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // For uint8_t
#include <stdbool.h> // For booleans


#define IMAGE_SIZE 512       // 512 bytes for the JPEG image


int main(int argc, char *argv[])
{
    // Verify accurate usage with command line arguments
    if (argc != 2)
    {
        printf ("Usage: ./recover FILE\n");
        return 1;
    }

    // Open memory card.
    FILE *card = fopen(argv[1], "r");
    // Verify that the file was properly opened
    if (card == NULL)
    {
        printf ("Error opening file\n");
        return 2;
    }

    // While there's still data left in the file
    uint8_t buffer[IMAGE_SIZE];
    FILE *jpeg = NULL;
    int count = 0;
    bool inJpeg = false;

    while (fread(&buffer, 1, IMAGE_SIZE, card) == IMAGE_SIZE)
    {
        // Verify if it's a JPEG
        bool isValidJpeg = buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;
        if (isValidJpeg)
        {
            // If a JPEG is already open, close it before creating a new one
            if (jpeg != NULL) {
                fclose(jpeg);
            }

            //Create a new JPEG file
            char jpegname[9];
            sprintf(jpegname, "%03i.jpg", count++);
            jpeg = fopen(jpegname, "w");

            // If unable to create jpeg
            if (jpeg == NULL)
            {
                printf("Unable to create jpeg\n");
                fclose(card);
                return 3;
            }

            // Write first block of data to the jpeg file
            fwrite(buffer, 1, IMAGE_SIZE, jpeg);
            inJpeg = true;
        }

        // If the 512 bytes is not a new jpeg and there is already an open jpeg, keep writing to it.
        else if (inJpeg)
        {
            fwrite(buffer, 1, IMAGE_SIZE, jpeg);
        }
    }

    // Close the last JPEG file if open
    if (jpeg != NULL) {
        fclose(jpeg);
    }

    fclose(card);
    return 0;
}
