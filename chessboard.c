#include "chessboard.h"
#include <ctype.h>
#include <stdio.h>

int createFigure(Figure* figure, char what)
{
    if (islower(what)) {
        figure->side = FigureSideBlack;
    } else {
        figure->side = FigureSideWhite;
    }
    switch (tolower(what)) {
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
    case ' ':
        figure->side = FigureSideNone;
        figure->type = FigureTypeNone;
        break;
    default:
        printf("Cant transform [%c] to figure\n", what);
        return 1;
    }

    return 0;
}

void printFigure(Figure figure)
{
    int color = figure.side == FigureSideBlack;
    switch (figure.type) {
    case FigureTypeRook:
        printf("%c", ('R' + color * 32));
        break;
    case FigureTypeKnight:
        printf("%c", ('N' + color * 32));
        break;
    case FigureTypeBishop:
        printf("%c", ('B' + color * 32));
        break;
    case FigureTypeQueen:
        printf("%c", ('Q' + color * 32));
        break;
    case FigureTypeKing:
        printf("%c", ('K' + color * 32));
        break;
    case FigureTypePawn:
        printf("%c", ('P' + color * 32));
        break;
    case FigureTypeNone:
        printf(" ");
        break;
    }
}

void createChessboard(Figure chessboard[8][8], char str[65])
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int index = (7 - i) * 8 + j;
            createFigure(&chessboard[i][j], str[index]);
        }
    }
}

void printChessboard(Figure chessboard[8][8])
{
    for (int i = 7; i >= 0; i--) {
        printf("%d", (i + 1));
        for (int j = 0; j < 8; j++) {
            printf(" ");
            printFigure(chessboard[i][j]);
        }
        printf("\n");
    }
    printf("  a b c d e f g h\n");
}