CC = gcc
CFLAGS = -c -Wall -Werror

all: chess

chess: main.o chessboard.o
	$(CC) main.o chessboard.o -o chess

main.o: main.c
	$(CC) $(CFLAGS) main.c

chessboard.o: chessboard.c
	$(CC) $(CFLAGS) chessboard.c

clean:
	rm -rf *.o chess