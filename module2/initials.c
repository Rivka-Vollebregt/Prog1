// initials.c is a program that prints the initials of a name
// it asks the user for his/her name as input and returns the initials in capitals

#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    // prompt user for name
    string fullname = get_string("Name:");

    // print the first initial of the name
    printf("%c", toupper(fullname[0]));

    // loop for the entire length of the name
    for (int i = 0; i <= strlen(fullname); i++)
    {
        // if the current character is a space, print the first character after the space
       if (fullname[i] == ' ' && fullname[i+1] != '\0')
       {
           printf("%c", toupper(fullname[i+1]));
       }
    }

    // prompt to a new line
    printf("\n");
}