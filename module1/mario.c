// Prints an half-pyramid with the height that user gets prompted for

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;

    // prompt user for height, if height not within ranges 0-23, user gets prompted again
    do
    {
        n = get_int("Height: ");
    }
    while (n < 0 || n > 23);

    // creates the number of rows desired i.e. the pyramid height that user entered
    for (int i = 0; i < n; i++)
    {
        // creates the spaces
        for (int j = n - i; j > 1; j--)
        {
            printf(" ");
        }

        //creates the hashmarks
        for (int k = 0; k < i + 2; k++)
        {
            printf("#");
        }

        // goes to new row
        printf("\n");
    }
}
