# COP 4338           
Assignment 3         
Cristian Bencomo                       
## Description 
This program allows the user to play chess and by issuing commands.            
Available commands:
> mv xy XY: Moves the piece located at xy to XY           
> cp xy XY: Captures the piece ad XY with the piece at xy 

The Program in this version does not support the promotion of pawns, 
the en passant move and it does not display a check message. However, everytime a move is performed, 
the program will check for the move's validity and display an error message depending on why the move 
is not possible.    

At the beginning of the program the board is generated dynamically by using the calloc function, and after calling the function "cleanup" all the memory used by the board is freed. 

## Contents
* main.c file containing all the source code 
* Makefile used to compile the program for testing and debugging
* chessGame object ready to be run (compiled on a linux system)

## How to use 
simply run the chessGame executable, or compile the program with the included makefile again