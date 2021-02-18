CC = gcc
CFLAGS = -c -Wall -Werror

all: chessviz

chessviz: main.o chessboard.o
	$(CC) main.o chessboard.o -o chessviz

main.o: main.c
	$(CC) $(CFLAGS) main.c

chessboard.o: chessboard.c
	$(CC) $(CFLAGS) chessboard.c

clean:
	rm -rf *.o chessviz
