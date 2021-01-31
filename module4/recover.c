/*********************************************************************************
 * recover.c
 *
 * recovers jpeg images
 *
 * Programmeren 1
 *
 * Rivka Vollebregt
 * 12164968
 *
 * recover.c recovers jpeg files from a memory card that have been 'deleted'
 * the input is the data from the memory card and the output is the jpeg images
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // error if the command line argument is missing or >1
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // open card file with fopen
    FILE *input = fopen(argv[1], "r");

    if (input == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    unsigned char buffer[512];

    // create space for jpeg image filename
    char photo[8];

    // counter for number of jpeg's processed
    int counter = 0;

    // create pointer to output file
    FILE *output = NULL;

    // repeat until end of card
    while (fread(buffer, 512, 1, input))
    {
        // check if start of a jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // if already found jpeg, close old jpeg and start new jpeg
            if (counter > 0)
            {
                fclose(output);
            }

            // if not found, close previous file, open new
            sprintf(photo, "%03i.jpg", counter);

            // open image file and check if succesfull
            output = fopen(photo, "w");

            if (output == NULL)
            {
                fprintf(stderr, "Could not create %s.\n", photo);
                return 3;
            }

            // up 1 the number of jpeg's created
            counter++;
        }

        // if photo exists, write the block to it
        if (output != NULL)
        {
            // write to image file
            fwrite(buffer, 512, 1, output);
        }
    }

    // close any remaining files (end of card)
    fclose(output);
    fclose(input);

    return 0;
}
