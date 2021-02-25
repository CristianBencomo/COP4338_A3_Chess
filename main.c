#include <stdlib.h>
#include <stdio.h>

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
            else // Not moving in a straight line
            {
                printf("invalid move: It is not moving in a stright line\n");
                return 0;
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

void move()
{

}

void capture()
{

}

int main(int argc, char const *argv[])
{
    setup();
    printBoard();

    return 0;
}
