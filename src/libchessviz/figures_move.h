#pragma once

#include "chess.h"

typedef enum {
    FieldLetterA,
    FieldLetterB,
    FieldLetterC,
    FieldLetterD,
    FieldLetterE,
    FieldLetterF,
    FieldLetterG,
    FieldLetterH,
} FieldLetter;
typedef enum {
    FieldNumber1,
    FieldNumber2,
    FieldNumber3,
    FieldNumber4,
    FieldNumber5,
    FieldNumber6,
    FieldNumber7,
    FieldNumber8
} FieldNumber;

typedef enum { MoveTypeQuiet, MoveTypeCapture } MoveType;

typedef enum {
    MoveExtraQueen,
    MoveExtraRook,
    MoveExtraKnight,
    MoveExtraBishop,
    MoveExtraEnPassant,
    MoveExtraCheck,
    MoveExtraCheckmate,
    MoveExtraShortCastling,
    MoveExtraLongCastling,
    MoveExtraNone
} MoveExtra;

typedef enum {
    MoveCastlingShort,
    MoveCastlingLong,
    MoveCastlingNone
} MoveCastling;

typedef struct {
    FieldLetter letter;
    FieldNumber number;
} Field;

typedef struct {
    Field from;
    Field to;
    FigureType who;
    MoveType type;
    MoveExtra extra;
} Move;

typedef struct {
    int count;
    Move array[100];
} Moves;

int doMove(
        const Moves moves,
        const int index,
        Chessboard* chessboard,
        char* errstr);
