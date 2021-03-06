#include "chessboard_create.h"
#include <ctype.h>

static int createFigure(Figure* figure, char fromChar)
{
    if (fromChar == ' ') {
        figure->side = FigureSideNone;
        figure->type = FigureTypeNone;
        return 0;
    }
    figure->side = islower(fromChar) ? FigureSideBlack : FigureSideWhite;
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

    return 0;
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