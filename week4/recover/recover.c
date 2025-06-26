#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "rb");

    if (f == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    BYTE buffer[512];
    FILE *output;
    int count = 0;
    bool isOpen = false;

    while (fread(&buffer, sizeof(buffer), 1, f) != 0)
    {
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF &&
            (buffer[3] & 0xF0) == 0xE0)
        {

            if (isOpen)
            {
                fclose(output);
                isOpen = false;
            }

            char filename[8];
            snprintf(filename, sizeof filename, "%03i.jpg", count);
            output = fopen(filename, "wb");

            if (output == NULL)
            {
                printf("Could not open file.\n");
                return 1;
            }

            isOpen = true;
            count++;
        }

        if (isOpen)
        {
            fwrite(&buffer, sizeof(buffer), 1, output);
        }
    }

    if (isOpen)
    {
        fclose(output);
    }
    fclose(f);
    return 0;
}
