#include "chessboard.h"
#include <stdio.h>
#include <string.h>

int main()
{
    Figure chessboard[8][8] = {};
    // Move Moves[1000];
    char str[64];
    char* name;
    FILE* f;
    // int i = 0;
    createChessboard(
            chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "        "
            "PPPPPPPP"
            "RNBQKBNR");
    fgets(str, 64, stdin);
    if (strncmp(str, "chessviz ", 9) == 0) {
        name = str + 9;
        printf("%s\n", name);
        f = fopen(name, "r");
        if (f == NULL) {
            printf("Can't open file\n");
            getchar();
            return 1;
        }
        printChessboard(chessboard);
    }
    getchar();
    return 0;
}