#pragma once

#include <libchessviz/figures_move.h>

#define ERROR_STR_LEN 128

typedef enum {
    ParseErrorTypeNone,
    ParseErrorTypeFigure,
    ParseErrorTypeField,
    ParseErrorTypeMove,
    ParseErrorTypeNumber,
    ParseErrorTypeSyntax,
} ParseErrorType;

typedef struct {
    ParseErrorType errtype;
    int column;
    char errstr[ERROR_STR_LEN];
} ParseError;

int parseMove(
        const char* string,
        const char** endstr,
        Move* move,
        ParseError* parseError);

int parseStep(const char* string, Moves* moves, ParseError* parseError);
