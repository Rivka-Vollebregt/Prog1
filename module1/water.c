// this function converts minutes showered into bottles of water
// it prompts the user for the minutes showered and converts this in bottles water, the output is a print of the bottles of water

# include <cs50.h>
# include <stdio.h>

int main(void)
{
  // prompt user for minutes showered, convert it into bottles water and print bottles, 1 minute=12 bottles
  int minutes = get_int("Minutes:");

  printf("Bottles: %i\n",minutes*12);
}
