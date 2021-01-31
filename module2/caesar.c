// caesar encripts a line of text
// it accepts a single command line argument which allows the user to specify the type of encription and uses that to encript the plain input text

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // if the command line argument is missing or two command line arguments have
    // been entered, the argc will not be 2, printing an error message to the user
    if (argc != 2)
    {
        printf("missing command-line argument\n");

        return 1;
    }

    // convert the command line argument from a string to an integer
    int num = atoi(argv[1]);

    // prompt the user for the plaintext
    string plaintext = get_string("plaintext: ");

    // print the word ciphertext: , after this all the ciphertext characters will be printed in a loop
    printf("ciphertext: ");

    // enciphering all individual characters of the string with the num specified by user in command line argument
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // check if character is a letter, if not, print character without encripting
        if (isalpha(plaintext[i]))
        {
            // check if character is uppercase, if so, encripted character will also be printed as uppercase
            if (isupper(plaintext[i]))
            {
                // convert character with encription key 'num'
                printf("%c", (((plaintext[i] - 65) + num) % 26) + 65);
            }

            // check if character is lowercase, if so, encripted character will also be printed as lowercase
            if (islower(plaintext[i]))
            {
                // convert character with encription key 'num'
                printf("%c", (((plaintext[i] - 97) + num) % 26) + 97);
            }
        }

        // print character if character is not letter
        else
        {
            printf("%c", plaintext[i]);
        }
    }

    // print newline for prompt
    printf("\n");

    return 0;
}