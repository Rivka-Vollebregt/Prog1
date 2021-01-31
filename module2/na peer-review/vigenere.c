/*********************************************************************************
 * viginere.c
 *
 * Programmeren 1
 *
 * Rivka Vollebregt
 * 12164968
 *
 * viginere encripton function encrypts plaintext given as input by the user
 * the encription key is the command line argument.
 * plaintext entered by user is shifted using the value of encription key
*********************************************************************************/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // check if command line argument is present and < 2, if not -> error
    if (argc != 2)
    {
        printf("missing command-line argument\n");

        return 1;
    }

    // Store command line argument in cla, and its length in length_cla
    int length_cla = strlen(argv[1]);
    string cla = argv[1];

    // check if command line argument is all letters
    for (int i = 0, n = length_cla; i < n; i++)
    {
        if (!isalpha(cla[i]))
        {
            printf("invalid command-line argument, enter letters\n");

            return 1;
        }
    }

    // prompt the user for the plaintext
    string plaintext = get_string("plaintext: ");

    // print the word ciphertext: , after this all the ciphertext characters will be printed in a loop
    printf("ciphertext: ");

    // convert plaintext to ciphertext
    for (int j = 0, i = 0, n = strlen(plaintext); j < n; j++)
    {
        // get encription key for current letter (plaintext(j))
        int k = tolower(cla[i % length_cla]) - 97;

        // check if character is a letter, if not, print character without encripting
        if (isalpha(plaintext[j]))
        {
            // check case of letter, keep case in encripted letter
            if (isupper(plaintext[j]))
            {
                // convert character with encription key k
                printf("%c", (((plaintext[j] - 65) + k) % 26) + 65);
                i++;
            }

            else
            {
                printf("%c", (((plaintext[j] - 97) + k) % 26) + 97);
                i++;
            }
        }

        // print character if character is not letter
        else
        {
            printf("%c", plaintext[j]);
        }
    }

    // print newline for prompt
    printf("\n");

    return 0;
}