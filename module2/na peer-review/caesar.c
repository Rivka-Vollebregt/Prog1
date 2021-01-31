/*********************************************************************************
 * caesar.c
 *
 * Programmeren 1
 *
 * Rivka Vollebregt
 * 12164968
 *
 * caesar encripts a line of text
 * it accepts a single command line argument which is the encription key
 * The user enters plaintext, which is shifted by the value of the encription key
*********************************************************************************/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // error if the command line argument is missing or >1
    if (argc != 2)
    {
        printf("missing command-line argument\n");

        return 1;
    }

    // convert the command line argument from a string to an integer
    int num = atoi(argv[1]);

    // prompt the user for the plaintext
    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    // enciphering all elements of plaintext with the num of command line argument
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // check if character is a letter, if not, print character without encripting
        if (isalpha(plaintext[i]))
        {
            // check case of letter, keep case in encripted letter
            if (isupper(plaintext[i]))
            {
                // convert character with encription key 'num'
                printf("%c", (((plaintext[i] - 65) + num) % 26) + 65);
            }

            else
            {
                printf("%c", (((plaintext[i] - 97) + num) % 26) + 97);
            }
        }

        // print character if character is not a letter
        else
        {
            printf("%c", plaintext[i]);
        }
    }

    // print newline for prompt
    printf("\n");

    return 0;
}