#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Piece variable declaration
#define WHITE 1
#define BLACK -1
#define EMPTY 0
#define PAWN 1
#define KNIGHT 2
#define BISHOP 3
#define ROOK 4
#define QUEEN 5
#define KING 6
#define BOARD_LENGTH 8
#define COMMAND_NUMBER 3
#define COMMAND_LENGTH 10
#define INPUT_LENGTH 30

// board location arrays
const char *X_LOCATION [8] = {"a", "b", "c", "d", "e", "f", "g", "h"};
const char *Y_LOCATION [8] = {"8", "7", "6", "5", "4", "3", "2", "1"};

/*----------------------------------------------------------------
- Missing board cleanup function
- Work on isLegalCapture
----------------------------------------------------------------*/

// Global variables
int **board;

// Function create and setup the chessboard
void setup()
{
    int piece;
    board = calloc(BOARD_LENGTH, sizeof(int *));
    
    // allocate space and initialize to 0
    for (int i=0; i<BOARD_LENGTH; i++)
    {
        board[i] = (int *)calloc(BOARD_LENGTH, sizeof(int));
    }

    // initializing the board with pieces
    for(int i=0; i<BOARD_LENGTH; i++)
    {
        switch (i)
        {
        case 0:
        case 7:
            piece = ROOK;
            break;
        case 1:
        case 6:
            piece = KNIGHT;
            break;
        case 2:
        case 5:
            piece = BISHOP;
            break;
        case 3:
            piece = QUEEN;
            break;
        case 4:
            piece = KING;
            break;
        }
        board[7][i] = piece * WHITE;
        board[6][i] = PAWN * WHITE;
        board[0][i] = piece * BLACK;
        board[1][i] = PAWN * BLACK;
    }

}

// Function to print the board
void printBoard()
{
    // print header coordinates
    printf("board: |%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", X_LOCATION[0], X_LOCATION[1], X_LOCATION[2], X_LOCATION[3], X_LOCATION[4], X_LOCATION[5], X_LOCATION[6], X_LOCATION[7]);
    printf("___________________________________________________________________\n");

    for(int i=0; i<BOARD_LENGTH; i++)
    {
        printf("%s      |", Y_LOCATION[i]); // print y cordinate
        for(int j=0; j<BOARD_LENGTH; j++)
        {
            printf("%d\t",board[i][j]);            
        }
        printf("\n");
    }
    printf("\n");
}

// check if the move is legal 

static int isLegalMove(int xSrc, int ySrc, int xDst, int yDst)
{
    int piece = board[xSrc][ySrc];
    int pieceType = abs(piece);

    // if the piecetype is queen
    if(pieceType == QUEEN)
    {
        if(xSrc == xDst || ySrc == yDst) // moves like a rook
        {
            pieceType = ROOK;
        }
        else
        {
            pieceType = BISHOP; // moves like a bishop
        }
    }

    switch(pieceType)
    {
        case PAWN:
            if(xSrc == xDst) //canbt change x-coordinate
            {    
                if(piece < 0) // if black piece
                {
                    if(ySrc == 6) // pawn initial position
                    {
                        if(ySrc < yDst && abs(ySrc - yDst) <= 2) // can move 2 spots downward
                        {
                            if(board[xDst][yDst] != EMPTY || board[xDst][yDst+1] != EMPTY) // check if path is not empty
                            {
                                printf("invalid move: path is not empty\n");
                                return 0;
                            }
                            else
                            {
                                return 1;
                            }
                        }
                    }
                    else // otherwise
                    {
                        if(ySrc < yDst && abs(ySrc - yDst) == 1) // can move only one spot downward
                        {
                            if(board[xDst][yDst] != EMPTY) //check if path is empty
                            {
                                printf("invalid move: path is not empty\n");
                                return 0;
                            }
                            else
                            {
                                return 1;
                            }
                        }
                    }
                }
                else // White piece
                {
                    if(ySrc == 1) // pawn initial position
                    {
                        if(board[xDst][yDst] != EMPTY || board[xDst][yDst-1] != EMPTY) //check if path is not empty
                            {
                                printf("invalid move: path is not empty\n");
                                return 0;
                            }
                            else
                            {
                                return 1;
                            }
                    }
                    else // otherwise
                    {
                        if(ySrc > yDst && abs(ySrc - yDst) == 1) // can move only one spot upward
                        {
                            if(board[xDst][yDst] != EMPTY) // check if path is not empty
                            {
                                printf("invalid move: path is not empty\n");
                                return 0;
                            }
                            else
                            {
                                return 1;
                            }
                        }
                    }
                }
            }
            printf("invalid move: That is not how pawns move\n");
            return 0;
            break;

        case ROOK:
            if(xSrc == xDst) // Moves vertically
            {
                if(ySrc < yDst) // rook moving upwards
                {
                    for(int i=1; i<(yDst - ySrc); i++) 
                    {
                        if(board[xDst][yDst-i] != EMPTY) // check if path is not empty
                        {
                            printf("invalid move: path is not empty\n");
                            return 0;
                        }
                        else
                        {
                            return 1;
                        }
                    }
                }
                else // rook moving downwards
                {
                    for(int i=1; i<(ySrc - yDst); i++)
                    {
                        if (board[xDst][yDst+i] != EMPTY) //check if path is not empty 
                        {
                            printf("invalid move: path is not empty\n");
                            return 0;
                        }
                        else
                        {
                            return 1; 
                        } 
                    }
                }
            }
            else if(ySrc == yDst) // moves horizontally
            {
                if(xSrc < yDst) // moves to the right
                {
                    for(int i=1; i<(xSrc - xDst); i++)
                    {
                        if(board[xDst-i][yDst] != EMPTY) // check if path is not empty
                        {
                            printf("invalid move: path is not empty\n");
                            return 0; 
                        }
                        else
                        {
                            return 1;
                        }
                    }
                }
                else // moves to the left
                {
                    for(int i=1; i<(xDst - xSrc); i++)
                    {
                        if(board[xDst+i][yDst] != EMPTY) // check if path is not empty
                        {
                            printf("invalid move: path is not empty\n");
                            return 0; 
                        }
                        else
                        {
                            return 1;
                        }
                    }
                }
            }
            break;

        case KNIGHT:
            if(abs(xSrc - xDst) * (ySrc - yDst) == 2)
            {
                return 1;
            }
            else
            {
                printf("invalid move: That is not how knights move\n");
                return 0;
            }
            break;

        case BISHOP:
            if(abs(xSrc - xDst) != abs(ySrc - yDst)) // check if it has been moved diagonally
            {
                printf("invalid move: It is not moving diagonally\n");
                return 0;
            }
            
            if(xSrc < xDst && ySrc < yDst) // moves down and right
            {
                for(int i=1; i<(xSrc - xDst); i++)
                {
                    if(board[xDst+i][yDst+i] != EMPTY) // check if path is not empty
                    {
                        printf("invalid move: path is not empty\n");
                        return 0;
                    }
                }
            }
            else if(xSrc < xDst && ySrc > yDst) // moves down and left
            {
                for(int i=1; i<(xSrc - xDst); i++)
                {
                    if(board[xDst+i][yDst-i] != EMPTY) // check if path is not empty
                    {
                        printf("invalid move: path is not empty\n");
                        return 0;
                    }
                }
            }
            else if(xSrc > xDst && ySrc < yDst) // moves up and right
            {
                for(int i=1; i<(xSrc - xDst); i++)
                {
                    if(board[xDst-i][yDst+i] != EMPTY) // check if path is not empty
                    {
                        printf("invalid move: path is not empty\n");
                        return 0;
                    }
                }
            }
            else // moves up and left
            {
                for(int i=1; i<(xSrc - xDst); i++)
                {
                    if(board[xDst-i][yDst-i] != EMPTY) // check if path is not empty
                    {
                        printf("invalid move: path is not empty\n");
                        return 0;
                    }
                }
            }
            return 1; // if it has not returned 0 to this point, then the move is valid

            break;

        case KING:
            if(abs(xSrc - xDst) + abs(ySrc - yDst) != 1) // king can only move one spot
            {
                printf("invalid move: The king can only move one spot\n");
                return 0;
            }
            return 1; // if the program has not returned 0 then the king is free to move
            break;
    }

    printf("ERROR: No correct piecetype detected\n");
    return 0; 
}

static int isLegalCapture(int xSrc, int ySrc, int xDst, int yDst)
{
    int piece = board[xSrc][ySrc];
    
    //check for move legality
    if(isLegalMove(xSrc, ySrc, xDst, yDst)) 
    {
        if(piece < 0) // if black piece
        {
            if(board[xDst][yDst] > 0)  // destination tile has a white piece
            {
                return 1;
            }
            else
            {
                printf("invalid capture: target tile needs to contain a white piece\n");
                return 0;
            }
        }
        else // else white piece
        {
            if(board[xDst][yDst] < 0)  // destination tile has a black piece
            {
                return 1;
            }
            else
            {
                printf("invalid capture: target tile needs to contain a black piece\n");
                return 0;
            }
        }
    }
    else
    {
        printf("invalid capture: Move is not legal\n");
        return 0;
    }
}

// function checks if move is legal and performs the changes to the board
void move(int xSrc, int ySrc, int xDst, int yDst)
{
    
    if(isLegalMove(xSrc, ySrc, xDst, yDst))
    {
        int piece = board[xSrc][ySrc];
        board[xSrc][ySrc] = 0;
        board[xDst][yDst] = piece;
    }
}

// function checks if capture is legal and performs the changes to the board
void capture(int xSrc, int ySrc, int xDst, int yDst)
{
    if(isLegalCapture(xSrc, ySrc, xDst, yDst))
    {
        int piece = board[xSrc][ySrc];
        board[xSrc][ySrc] = 0;
        board[xDst][yDst] = piece;
    }
}

/*-----------------------------------------------------------------------------------------------
function separates the input into parts
command[] is will store:
command[0] = command 
command[1-4] = source and targets x and y values in order (xSrc, ySrc, xDst, yDst)
-----------------------------------------------------------------------------------------------*/
void splitstr(char str[INPUT_LENGTH], char commands[COMMAND_NUMBER][COMMAND_LENGTH])
{
    int word = 0;
    int ch_num = 0;
    for(int i=0; i<strlen(str); i++)
    {
        if(str[i]== ' ' || str[i]=='\0' || str[i]== '\n')
        {
            commands[word][ch_num] = '\0';
            word++; //change to next word
            ch_num=0; //resetting for next word
        }
        else
        {
            commands[word][ch_num] = str[i];
            ch_num++;
        }
    }
}

// // Set the contents of command to null
// void setCommandsToNull(char commands[COMMAND_NUMBER][COMMAND_LENGTH])
// {
//     int word = 0;
//     int ch_num = 0;
//     for(int i=0; i<INPUT_LENGTH; i++)
//     {
//         commands[word][ch_num] = '\0';
//         if(ch_num == COMMAND_LENGTH - 1)
//         {
//             ch_num = 0;
//             word++;
//         }
//     }
// }

int main(int argc, char const *argv[])
{    
    while(1)
    {
        char input [INPUT_LENGTH];
        char commands[COMMAND_NUMBER][COMMAND_LENGTH];
        int xSrc_num, ySrc_num, xDst_num, yDst_num;
        char xSrc_ch, ySrc_ch, xDst_ch, yDst_ch;
        setup();

        // ask for input and tokenize it
        printf("Enter a command\n");
        fgets(input, INPUT_LENGTH, stdin);
        splitstr(input, commands);
        char *command = commands[0];
        
        if(strcasecmp(commands[0], "mv") == 0) // move command
        {
            printf("inmove");
            if(commands[1][0] != '\0' && commands[2][0] != '\0')
            {
                xSrc_ch = commands[1][0];
                ySrc_ch = commands[1][1];
                xDst_ch = commands[2][0];
                yDst_ch = commands[2][1];
                int index = strcspn(X_LOCATION, xSrc_ch);
                printf("index: %d\n", index);
            }
            else
            {
                printf("Incorrect input format, please use the following...\n");
                printf("mv x0 y0 x1 y1\n");
            }
        }
        else if(strcasecmp(commands[0], "cp") == 0) //capture command
        {

        }
        else if(strcasecmp(commands[0], "show") == 0) // show command
        {
            printBoard();
        }
        else // incorrect command
        {
            printf("Incorrect command format detected, please use one of the following...\n");
            printf("mv x0 y0 x1 y1\n");
            printf("cp x0 y0 x1 y1\n");
            printf("show\n");
            printf("Command:%s", command);
        }

    }
}