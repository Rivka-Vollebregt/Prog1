// greedy asks the user for the amount of change due and calculates the minimal number of coins necessary
// coins available: quarters: 25, dimes: 10, nickels: 5, pennies: 1
// count = number of coins returned (0 at the start)
// amount = change still due (lessens after every coin given)

#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    int amount = 0;
    int count = 0;
    float dollars = 0;

    // prompt user for amount of change due
    do
    {
        dollars = get_float("Change owed: $ ");
    }
    while (dollars < 0);

    // convert input into cents
    dollars *= 100.0;
    amount = (int) round(dollars);

    // while amount is larger than coin (quarter = 25, dime = 10, nickel = 5, penny = 1),
    // give that coin as change
    while (amount >= 25)
    {
        count++;
        amount = amount - 25;
    }

    while (amount >= 10)
    {
        count++;
        amount = amount - 10;
    }

    while (amount >= 5)
    {
        count++;
        amount = amount - 5;
    }

    while (amount >= 1)
    {
        count++;
        amount = amount - 1;
    }

    //print minimum number of coins for change
    printf("%i \n", count);
}