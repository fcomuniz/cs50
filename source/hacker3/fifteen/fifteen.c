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
#include <string.h>
#include <time.h>
#include "saml.h"

// Testing values;
#define LOGGING

#ifdef LOGGING
    FILE * file;
#endif

// constants
#define DIM_MIN 3
#define DIM_MAX 9
#define N_OF_MOVES_RANDOM 100
#define MAX_INPUT_SIZE 1000

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// Solving values
bool solved = false;
int * solution = NULL;
int sizeOfSolution = 0;
int solutionIndex = 0;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
int solve(void);
bool move(int tile);
bool areAdjacent(int tilePos1[2], int tilePos2[2]);
bool won(void);
void randomizeBoard(void);

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
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    
    file = fopen("log.txt", "w");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open log file");
        return 3;
    }

    // greet user with instructions
    greet();
    
    bool inGodMode=false;

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
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            free(solution);
            break;
        }

        // prompt for move
        int tile;
        if(!inGodMode){
            // Ask user for input
            printf("Tile to move: ");
            char input[MAX_INPUT_SIZE];
            scanf("%s", input);
            char * endptr = NULL;
            tile = strtol(input,&endptr, 10);
            if(*endptr != '\0'){
                // If the input is GOD, enter god mode, else, the input is invalid
                if(strcmp(input,"GOD")==0){
                    // Enter god mode
                    inGodMode=true;
                }
            }
            // quit if user inputs 0 (for testing)
            if (tile == 0 && !inGodMode)
            {
                break;
            }
        } else {
            // determine the movement to be made now
            tile = solve();
        }



        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
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
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // We must fill the array with a dependency to the dimenstion
    int numberToPut = d*d - 1;
    for(int i = 0; i < d; i++){
        for(int j = 0; j < d; j++){
            board[i][j] = numberToPut;
            numberToPut --;
        }
    }
    
    // fix if d is pair
    if(d%2 == 0){
        board[d-1][d-2] = 2;
        board[d-1][d-3] = 1;
    }
    
    // Now we randomize the board moving random numbers 
    randomizeBoard();
    
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for(int i = 0; i < d; i++){
        printf("    ");
        for(int j = 0; j < d; j++){
            if(board[i][j] != 0){
                printf("%2i", board[i][j]);
            } else {
                printf("%2c", '_');
            }
            if(j < d-1){
                printf("  ");   
            } else {
                printf("\n");
            }
        }
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    if(tile < 0 || tile >= d*d){
        return false;
    }
    // Define the position variables for both the tile and the zero
    int tilePlace[2] = {-1,-1};
    int zeroPlace[2];
    
    
    // Iterate trough the board to find the tile and the zero
    for(int i = 0; i < d; i++){
        for(int j = 0 ; j < d ; j++){
            if(board[i][j] == tile){
                tilePlace[0] = i;
                tilePlace[1] = j;
            }
            
            if(board[i][j] == 0){
                zeroPlace[0] = i;
                zeroPlace[1] = j;
            }
        }
    }
    // Aux Variable for changing the position of 
    int auxVar;
    // Check if the tile and the zero are adjacent and move if they are
    bool adjacent = areAdjacent(tilePlace, zeroPlace);
    if(adjacent){
        auxVar = board[tilePlace[0]][tilePlace[1]];
        board[tilePlace[0]][tilePlace[1]] = board[zeroPlace[0]][zeroPlace[1]];
        board[zeroPlace[0]][zeroPlace[1]] = auxVar;
        
    } 
    return adjacent;
}

/**
 * Returns true if the two tiles are adjacent
 */
 bool areAdjacent(int tilePos1[2], int tilePos2[2]){
     bool adjacent = false;
    //  Simplest case
    
    if(!(tilePos1[0] == 0)){
        adjacent = adjacent || (tilePos1[0]-1 == tilePos2[0] && tilePos1[1] == tilePos2[1]);
    }
    if(!(tilePos1[0] == d-1)){
        adjacent = adjacent || (tilePos1[0]+1 == tilePos2[0] && tilePos1[1] == tilePos2[1]);
    }
    
    if(!(tilePos1[1] == 0)){
        adjacent = adjacent || (tilePos1[0] == tilePos2[0] && tilePos1[1]-1 == tilePos2[1]);
    }
    if(!(tilePos1[1] == d-1)){
        adjacent = adjacent || (tilePos1[0] == tilePos2[0] && tilePos1[1]+1 == tilePos2[1]);
    }
     return adjacent;
 }

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    bool hasWon = true;
    int correctNumber = 1;
    // Looping trhough the board
    for(int i = 0; i < d ; i++){
        for(int j = 0 ; j < d; j++){
            if(j == d-1 && i == d -1){
                // Should be a zero 
                hasWon = hasWon && board[i][j] == 0;
            } else {
                hasWon = hasWon && board[i][j] == correctNumber;
                correctNumber++;
            }
        }
    }
    
    return hasWon;
}

void randomizeBoard(void){
    srand48((long int) time(NULL));
    // Random number
    
    for(int i = 0 ; i < N_OF_MOVES_RANDOM; i++){
        // fprintf(file,"%i\n",(int) (drand48() *(d*d -1) +1));
        move((int) (drand48() *(d*d -1) +1));    
    }
}

int solve(void){
    // Check if the game has already been solved 
    // if not solved, solve, if solved, read from solution
    if(!solved){
        // Solving the system with the current configuration
        solveSAML(d,board, &solution, &sizeOfSolution);
        solved = true;
    }
    // Solve using some algorithm for solving
    int retValue=solution[solutionIndex];
    solutionIndex++;
    return retValue;
}