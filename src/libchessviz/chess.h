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
    FigureType type;
    FigureSide side;
} Figure;

typedef struct {
    Figure cells[CHESSBOARD_SIZE][CHESSBOARD_SIZE];
} Chessboard;
