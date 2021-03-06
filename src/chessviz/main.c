#include "chess_read.h"
#include <chess.h>
#include <chessboard_create.h>
#include <chessboard_print_plain.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    Moves moves;
    moves.count = 0;
    Chessboard chessboard;
    char string[(CHESSBOARD_SIZE + 1) * (CHESSBOARD_SIZE + 1) * 2 + 1];
    char inputString[64];
    char errstr[64];

    if (argc == 1) {
        fgets(inputString, 64, stdin);
        if (parseStep(inputString, &moves, errstr)) {
            printf("%s", errstr);
            return 0;
        }
    }
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
    for (int i = 0; i < moves.count; i++) {
        doMove(moves.array[i], &chessboard);
    }
    chessboardToString(&chessboard, string);
    printf("%s", string);
    return 0;
}
