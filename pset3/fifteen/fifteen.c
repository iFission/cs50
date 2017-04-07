/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
bool isodd(int n);
void swap(int*, int*);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                if (board[i][j] == d * d) // required as program uses d * d as blank, however check50 expects blank to be 0
                {
                    board[i][j] = 0;
                }
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
                if (board[i][j] == 0) // reverts the blank to d * d
                {
                    board[i][j] = d * d;
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000); // pause for .5 seconds
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000); // pause for 2 seconds
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    int k = (d * d) - 1;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
                board[i][j] = k;
                k = k - 1;
        }
    }
    if (isodd((d * d) - 1)) // swap the positions of 1 and 2 if odd
    {
        swap(&board[d - 1][d - 2], &board[d - 1][d - 3]);
    }
    board[d - 1][d - 1] = d * d; // make last element the max number of the array, use as blank
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == d * d) // print the largest element as _ (blank) for user to move
            {
                printf(" _");
            }
            else
            {
                printf("%2i", board[i][j]);
            }
            if (j < d - 1) // prints space between columns, don't print at the last column
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
                if (board[i][j] == tile) // get the position of the tile to be moved in the array
                {
                    // check if the tile is near the blank
                    if (board[i - 1][j] == d * d) // check above tile
                    {
                        swap(&board[i][j], &board[i - 1][j]);
                        return true;
                    }
                    if (board[i][j - 1] == d * d) // check left tile
                    {
                        swap(&board[i][j], &board[i][j - 1]);
                        return true;
                    }
                    if (board[i][j + 1] == d * d) // check right tile
                    {
                        swap(&board[i][j], &board[i][j + 1]);
                        return true;
                    }
                    if (board[i + 1][j] == d * d) // check below tile
                    {
                        swap(&board[i][j], &board[i + 1][j]);
                        return true;
                    }
                }
        }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // compares the first element and the element after itself, if the first element is bigger, return false
    // wins if all elements are in ascending order
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d - 1; j++) // stops at board[][d-1] as the second last element will be compared against the last element, hence not requring the last element to be compared against other elements
        {
            if (board[i][j] + 1 != board[i][j + 1]) // checks the board using + 1, does not have to compare board[0][2] with board[1][0]
            {
                return false;
            }
        }
    }
    return true;
}

bool isodd(int n)
{
    if (n < 0)
    {
        n = abs(n);
    }
    n = n % 2;
    if (n == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}


void swap(int *i, int *j)
{
    int temp = *i;
    *i = *j;
    *j = temp;
}
