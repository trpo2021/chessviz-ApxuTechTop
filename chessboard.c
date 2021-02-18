#define CHESSBOARD_SIZE 8

#include "chessboard.h"
#include <ctype.h>
#include <stdio.h>

static int createFigure(Figure* figure, char fromChar)
{
    if (fromChar == ' ') {
        figure->side = FigureSideNone;
        figure->type = FigureTypeNone;
    } else {
        figure->side = (islower(fromChar)) ? FigureSideBlack : FigureSideWhite;
        switch (tolower(fromChar)) {
        case 'r':
            figure->type = FigureTypeRook;
            break;
        case 'n':
            figure->type = FigureTypeKnight;
            break;
        case 'b':
            figure->type = FigureTypeBishop;
            break;
        case 'q':
            figure->type = FigureTypeQueen;
            break;
        case 'k':
            figure->type = FigureTypeKing;
            break;
        case 'p':
            figure->type = FigureTypePawn;
            break;
        default:
            return 1;
        }
    }

    return 0;
}

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

void createChessboard(Chessboard* chessboard, const char* fromString)
{
    for (int i = 0; i < CHESSBOARD_SIZE; i++) {
        for (int j = 0; j < CHESSBOARD_SIZE; j++) {
            int index = (CHESSBOARD_SIZE - 1 - i) * CHESSBOARD_SIZE + j;
            createFigure(&chessboard->cells[i][j], fromString[index]);
        }
    }
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
