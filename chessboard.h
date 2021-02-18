#pragma once

#define CHESSBOARD_SIZE 8

typedef enum {
    FigureTypeKing,
    FigureTypeQueen,
    FigureTypeRook,
    FigureTypeKnight,
    FigureTypeBishop,
    FigureTypePawn,
    FigureTypeNone
} FigureType;
typedef enum { FigureSideWhite, FigureSideBlack, FigureSideNone } FigureSide;

typedef struct {
    char letter;
    char number;
} Field;

typedef struct {
    Field from;
    Field to;
    char who;
    char type;
    char extra;
} Move;

typedef struct {
    FigureType type;
    FigureSide side;
} Figure;

typedef struct {
    Figure cells[CHESSBOARD_SIZE][CHESSBOARD_SIZE];
} Chessboard;

void createChessboard(Chessboard* chessboard, char* fromString);

void chessboardToString(Chessboard chessboard, char* string);
