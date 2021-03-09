#include "chessboard_print_plain.h"
#include <ctype.h>
#include <stdio.h>

static char figureToChar(Figure figure)
{
    char figureChar = 'c';
    switch (figure.type) {
    case FigureTypeRook:
        figureChar = 'r';
        break;
    case FigureTypeKnight:
        figureChar = 'n';
        break;
    case FigureTypeBishop:
        figureChar = 'b';
        break;
    case FigureTypeQueen:
        figureChar = 'q';
        break;
    case FigureTypeKing:
        figureChar = 'k';
        break;
    case FigureTypePawn:
        figureChar = 'p';
        break;
    case FigureTypeNone:
        figureChar = ' ';
        break;
    }
    figureChar = (figure.side == FigureSideWhite) ? toupper(figureChar)
                                                  : figureChar;

    return figureChar;
}

void chessboardToString(const Chessboard* chessboard, char* string)
{
    int n = 0;
    for (int i = CHESSBOARD_SIZE - 1; i >= 0; i--) {
        n += sprintf(string + n, "%d", (i + 1));
        for (int j = 0; j < CHESSBOARD_SIZE; j++) {
            n += sprintf(string + n, " ");
            char c = figureToChar(chessboard->cells[i][j]);
            n += sprintf(string + n, "%c", c);
        }
        n += sprintf(string + n, "\n");
    }
    sprintf(string + n, "  a b c d e f g h\n");
}