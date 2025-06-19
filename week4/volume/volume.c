// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

typedef uint8_t BYTE;
typedef int16_t SAMPLE;

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

    // My code ↓
    /*
    Get the header :
     - Loop over the size of the header (HEADER_SIZE) here its 44 bytes for .wav files
     - for each byte, read it and copy it into output.wav

     understanding fread and fwrite :
        - give the adress of the array named "header" with & and asking for the sizeof a header
    chunk -> here 1 byte.
        - Than ordering to loop read one by one with third argument
        - All that from the input pointer (file)

        So basically, fread and fwrite knows at which position of the array im in, bc no [] in
    &header ??? tried to put it but crashed so....
    */
    BYTE header[HEADER_SIZE];

    fread(&header, sizeof(header), 1, input);
    fwrite(&header, sizeof(header), 1, output);

    /*
    Loop as long as i read sum.
        - Once ive read sum, multiply it
        - Than write it SAMPLE by SAMPLE (int16_t) i output file.
    */

    SAMPLE buffer;

    while (fread(&buffer, sizeof(SAMPLE), 1, input) != 0)
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(SAMPLE), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
