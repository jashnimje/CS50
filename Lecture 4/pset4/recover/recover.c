#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open a file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open.\n");
        return 1;
    }

    // Declare a variable to unsigned char to store 512 chunks array
    unsigned char buffer[512];

    // Initialize output pointer to NULL
    FILE *outfile = NULL;

    // filename
    char filename[8];

    // Initialize image counter
    int count = 0;

    while (fread(buffer, sizeof(char), 512, file) != 0)
    {
        // Check starting bytes if it matches the jpg file headers.
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
        {
            // Create filename
            sprintf(filename, "%03i.jpg", count);

            // Open output new file
            outfile = fopen(filename, "w");

            // Image Count
            count++;
        }

        // Write the buffer to the file if the outfile is not empty
        if (outfile != NULL)
        {
            fwrite(buffer, sizeof(char), 512, outfile);
        }
    }

    fclose(outfile);
    fclose(file);
}