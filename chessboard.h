#pragma once

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
    Figure cells[8][8];
} Chessboard;

void createChessboard(Chessboard* chessboard, char* fromString);

void chessboardToString(Chessboard chessboard, char* string);
