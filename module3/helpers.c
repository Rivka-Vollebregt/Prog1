/*********************************************************************************
 * Helper functions
 *
 * Programmeren 1
 *
 * Rivka Vollebregt
 * 12164968
 *
 * helpers.c functions are used by find.c to search for specific value in list of
 * numbers, and returns 'found' is value present or 'not found' if not present
 *
 * Input is a list of numbers, sorts numbers from small-large with sort function
 * Then search functions uses selection sort to check for presence of value
*********************************************************************************/

#include <cs50.h>

#include "helpers.h"

// binary search (log(n))
// Returns true if value is in array of n values, else false
bool search(int value, int values[], int n)
{
    // if value is negative, return false
    if (value < 0)
    {
        return false;
    }

    // assign 'first' as start of list, 'last' as end of list (length of n)
    int first = 0, last = n - 1;

    // check if value is in the list
    while (n > 0)
    {
        // assign middle value
        int middle = (last - first) / 2 + first;

        if (values[middle] == value)
        {
            return true;
        }

        // if middle is larger than value, search left half of list
        else if (values[middle] > value)
        {
            // new list is left half of previous list
            last = middle - 1;
        }

        // if middle is smaller than value, search right half of list
        else if (values[middle] < value)
        {
            // new list is right half of previous list
            first = middle + 1;
        }

        // new list length n
        n = last - first + 1;
    }

    return false;
}

// Sorts array of n values using selection sort (O(n^2))
void sort(int values[], int n)
{
    // scan every value in the array values[]
    for (int minvalue = 0; minvalue < n - 1; minvalue++)
    {
        for (int current = minvalue + 1; current < n; current++)
        {
            // check if current value is smaller than minvalue
            if (values[current] < values[minvalue])
            {
                // exchange the values of minvalue and current
                int exchange = values[minvalue];
                values[minvalue] = values[current];
                values[current] = exchange;
            }
        }
    }

    return;
}