#define CHESSBOARD_SIZE 8

#include "chessboard.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    Chessboard chessboard;
    char string[CHESSBOARD_SIZE * CHESSBOARD_SIZE + 1];
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "        "
            "PPPPPPPP"
            "RNBQKBNR");
    chessboardToString(chessboard, string);
    printf("%s", string);
    return 0;
}
