/*********************************************************************************
 * Implements Game of Fifteen (generalized to d x d)
 *
 * Programmeren 1
 *
 * Rivka Vollebregt
 * 12164968
 *
 * The game of fifteen is played by sorting a grid of numbers in order
 * from small to large.
 * The user enters a tile that has to be next to the blank tile,
 * then that tile will be swapped with the blank tile.
 * This continues until numbers are all sorted
 *
 * Input is the dimension of the board
*********************************************************************************/
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Constants
#define DIM_MIN 3
#define DIM_MAX 9
#define COLOR "\033[32m"

// Board
int board[DIM_MAX][DIM_MAX];

// Dimensions
int d;

// Prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // Ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
               DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // Open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // Greet user with instructions
    greet();

    // Initialize the board
    init();

    // Accept moves until game is won
    while (true)
    {
        // Clear the screen
        clear();

        // Draw the current state of the board
        draw();

        // Log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // Check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // Prompt for move
        int tile = get_int("Tile to move: ");

        // Quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // Log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // Move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // Sleep thread for animation's sake
        usleep(50000);
    }

    // Close log
    fclose(file);

    // Success
    return 0;
}

// Clears screen using ANSI escape sequences
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

// Greets player
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

// Initializes the game's board with tiles numbered 1 through d*d - 1
// (i.e., fills 2D array with values but does not actually print them)
void init(void)
{
    // numbers is here assigned the value for the highest tile
    int number = ((d * d) - 1);

    // Iterate over the grid
    for (int row = 0; row < d; row++)
    {
        for (int column = 0; column < d; column++)
        {
            // set tile's value
            // tile's value is (d^2 -1) descending 1 for every following tile
            board [row] [column] = number;
            number--;
        }
    }

    // if d is even, swap the 1 and 2 tile
    if ((d * d % 2) == 0)
    {
        board [d - 1] [d - 2] = 2;
        board [d - 1] [d - 3] = 1;
    }
}

// Prints the board in its current state
void draw(void)
{
    // Iterate over the grid
    for (int row = 0; row < d; row++)
    {
        for (int column = 0; column < d; column++)
        {
            // print last tile as underscore instead of zero
            if (board [row] [column] == 0)
            {
                printf("%3c", '_');
            }

            // print tile number for every tile other than last tile
            else
            {
                // print tile
                printf("%3i", board [row] [column]);
            }
        }

        // print new line for a new row
        printf("\n\n");
    }
}

// If tile borders empty space, moves tile and returns true, else returns false
bool move(int tile)
{
    // iterate over the grid to find the tile typed in by user
    for (int row = 0; row < d; row++)
    {
        for (int column = 0; column < d; column++)
        {
            // if tile is found, check if it borders the '0' / 'empty tile'
            if (board [row] [column] == tile)
            {
                // if blank tile is above, switch with above
                if (row - 1 >= 0 && board [row - 1] [column] == 0)
                {
                    board [row - 1] [column] = tile;
                    board [row] [column] = 0;
                    return true;
                }

                // if blank tile is below, switch with below
                else if (row + 1 < d && board [row + 1] [column] == 0)
                {
                    board [row + 1] [column] = tile;
                    board [row] [column] = 0;
                    return true;
                }

                // if blank tile is left, switch with left
                else if (column - 1 >= 0 && board [row] [column - 1] == 0)
                {
                    board [row] [column - 1] = tile;
                    board [row] [column] = 0;
                    return true;
                }

                // if blank tile is right, switch with right
                else if (column + 1 < d && board [row] [column + 1] == 0)
                {
                    board [row] [column + 1] = tile;
                    board [row] [column] = 0;
                    return true;
                }

                // if tile does not border empty tile, return false
                return false;
            }
        }
    }

    return false;
}

// Returns true if game is won (i.e., board is in winning configuration), else false
bool won(void)
{
    int wintile = 1;

    // check if value of every tile is equal to winning tile value
    for (int row = 0; row < d; row++)
    {
        for (int column = 0; column < d; column++)
        {
            if (board [row] [column] == wintile)
            {
                wintile++;
            }

            // if last tile is blank tile, last tile is in winning configuration
            else if (wintile == d * d && board [row] [column] == 0)
            {
                return true;
            }

            // if current tile does not equal winning tile, return false: game not solved
            else
            {
                return false;
            }
        }
    }

    return true;
}
