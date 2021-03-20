#include "chess_read.h"
#include <libchessviz/chess.h>
#include <libchessviz/chessboard_create.h>
#include <libchessviz/chessboard_print_plain.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    FILE* f;
    char* filename;

    Moves moves;
    moves.count = 0;
    Chessboard chessboard;
    char string[(CHESSBOARD_SIZE + 1) * (CHESSBOARD_SIZE + 1) * 2 + 1];
    char inputString[64];

    ParseError parseError = {.errtype = ParseErrorTypeNone};

    char errstr[64];

    if (argc == 1) {
        printf("Usage: chessviz <filename>");
        return 0;
    }

    filename = argv[1];
    f = fopen(filename, "r");

    while (fgets(inputString, 64, f) != NULL) {
        printf("%s", inputString);
        if (parseStep(inputString, &moves, &parseError)) {
            printf("\n%s", parseError.errstr);
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
    int errnum = 0;
    for (int i = 0; i < moves.count; i++) {
        errnum = doMove(moves, i, &chessboard, errstr);
        if (errnum) {
            printf("\n%s\n", errstr);
            return 1;
        }
        chessboardToString(&chessboard, string);

        printf("\n%s", string);
    }

    chessboardToString(&chessboard, string);

    printf("\n%s", string);

    return 0;
}
