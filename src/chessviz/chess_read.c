#include "chess_read.h"
#include <ctype.h>
#include <stdio.h>

static int parseNumber(const char* string, const char** endptr)
{
    int num = 0;
    const char* cptr = string;
    while (1) {
        if (!isdigit(*cptr)) {
            *endptr = cptr;
            return num;
        }
        if (num == 0 && *cptr == '0') {
            *endptr = cptr;
            return 0;
        }
        num = num * 10 + *cptr - '0';
        cptr++;
    }
}

static FigureType parseFigure(const char* string, const char** endptr)
{
    *endptr = string;
    if (islower(*string)) {
        return FigureTypePawn;
    }
    switch (*(*endptr)++) {
    case 'R':
        return FigureTypeRook;
    case 'N':
        return FigureTypeKnight;
    case 'B':
        return FigureTypeBishop;
    case 'Q':
        return FigureTypeQueen;
    case 'K':
        return FigureTypeKing;
    }

    *endptr = string;
    return FigureTypeNone;
}

static Field parseField(const char* cptr, const char** endptr)
{
    Field field = {FieldLetterA, FieldNumber1};
    *endptr = cptr;
    if (*cptr < 'a' || *cptr > 'h') {
        return field;
    }
    field.letter = *cptr - 'a';
    cptr++;
    if (*cptr < '1' || *cptr > '8') {
        return field;
    }
    field.number = *cptr - '1';
    *endptr = *endptr + 2;
    return field;
}

static MoveExtra parseExtra(const char* string, const char** endptr)
{
    const char* cptr = string;
    switch (*cptr) {
    case 'R':
        return MoveExtraRook;
    case 'N':
        return MoveExtraKnight;
    case 'B':
        return MoveExtraBishop;
    case 'Q':
        return MoveExtraQueen;
    }
    *endptr = cptr;
    // e.p.

    //+

    //#
    return MoveExtraNone;
}

int parseMove(const char* string, const char** endstr, Move* move, char* errstr)
{
    const char* sptr = *endstr;
    const char* cptr = string;
    const char* endptr;
    // 0-0-0

    move->who = parseFigure(cptr, &endptr);
    if (move->who == FigureTypeNone) {
        sprintf(errstr,
                "Error at column %d: expected <Figure char>, got %c",
                endptr - sptr,
                *endptr);
        return 1;
    }
    cptr = endptr;

    move->from = parseField(cptr, &endptr);
    if (cptr == endptr) {
        sprintf(errstr, "Error at column %d: expected <Field>", cptr - sptr);
        return 1;
    }
    cptr = endptr;

    if (*cptr == '-') {
        move->type = MoveTypeQuiet;
    } else if (*cptr == 'x') {
        move->type = MoveTypeCapture;
    } else {
        sprintf(errstr,
                "Error at column %d: expected '-' or 'x', got %c",
                cptr - sptr,
                *cptr);
        return 1;
    }
    cptr++;

    move->to = parseField(cptr, &endptr);
    if (cptr == endptr) {
        sprintf(errstr, "Error at column %d: expected <Field>", cptr - sptr);
        return 1;
    }
    cptr = endptr;

    move->extra = parseExtra(cptr, &endptr);
    *endstr = cptr;

    return 0;
}

int parseStep(const char* string, Moves* moves, char* errstr)
{
    int errnum = 0;
    int num = 0;
    const char* cptr = string;
    const char* endptr;

    num = parseNumber(cptr, &endptr);
    if (num == 0) {
        sprintf(errstr, "Error at column 0: expected number");
        return 1;
    }
    cptr = endptr;
    if (moves->count / 2 + 1 != num) {
        sprintf(errstr, "Error at column 0: expected %d", moves->count / 2 + 1);
        return 1;
    }
    if (*cptr++ != '.') {
        sprintf(errstr, "Error at column %d: expected '.'", cptr - string);
        return 1;
    }
    if (*cptr++ != ' ') {
        sprintf(errstr, "Error at column %d: expected ' '", cptr - string);
        return 1;
    }
    endptr = string;
    errnum = parseMove(cptr, &endptr, &moves->array[moves->count], errstr);
    if (errnum) {
        return errnum;
    }
    moves->count++;
    cptr = endptr;
    if (*cptr++ != ' ' && *cptr != '\0' && *cptr != '\n') {
        sprintf(errstr, "Error at column %d: expected ' '", cptr - string);
        return 1;
    }
    if (*cptr != ' ' && *cptr != '\0') {
        endptr = string;
        errnum = parseMove(cptr, &endptr, &moves->array[moves->count], errstr);
        if (errnum) {
            return errnum;
        }
        moves->count++;
        cptr = endptr;
    }

    while (1) {
        if (*cptr == '\0') {
            return 0;
        }
        if (!isspace(*cptr)) {
            sprintf(errstr,
                    "Error at column %d: not expected <%c>",
                    cptr - string,
                    *cptr);
            return 1;
        }
        cptr = cptr + 1;
    }
}
