CC = gcc
CFLAGS = -g -Wall -c
LFLAGS = -g -Wall 

calendarFunctions : main.c
	$(CC) $(LFLAGS) main.c -o chessGame

clean :
	\rm chessGame.zip chessGame

zip : 
	zip chessGame.zip *