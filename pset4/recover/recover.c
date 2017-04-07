#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Could not open file\n");
        return 1;
    }

    // open input file
    FILE* file = fopen(argv[1], "r");

    if (file == NULL)
    {
        fprintf(stderr, "Could not open file\n");
        return 1;
    }

    // allocate memory for buffer of 512 bytes
    uint8_t buffer[512]; //512 * 8 bits //use uint8_t instead of char for unsigned to store 1 byte

    // counter for the sequence of jpg
    int njpg = 0;

    // file opened indicator
    int fileOpen = 0;
    FILE* jpg;

    //jpg signature stored in char, 1 byte each, total 3 bytes
    //char jpgSig[3] = {0xff, 0xd8, 0xff};

    //detect eof by 512 bytes, if 0 is returned, reach eof
    while(fread(buffer, 512, 1, file) > 0)
    {
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff) //only compare unsigned values
        {
            // file name for jpg
            char* name = malloc(7 * sizeof(char));
            sprintf(name, "%03i.jpg", njpg); // %0 for leading zeros

            // create new file if no file opened
            if(fileOpen==0)
            {
                jpg = fopen(name, "a");
                fileOpen = 1;
            }

            // close old file, create new file
            if(fileOpen==1)
            {
                fclose(jpg);
                jpg = fopen(name, "a");
                njpg++;
            }

            free(name);

            // write 512 bytes to jpg file
            fwrite(buffer, sizeof(buffer), 1, jpg);
        }
        else
        {
            if (fileOpen == 1)
            {
                fwrite(buffer, sizeof(buffer), 1, jpg);   
            }
        }
    }

    // close files
    fclose(file);
    fclose(jpg);
    return 0;
}