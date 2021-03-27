#include "chess_read.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define ERRFRMT(x, y) "Error at column " x ": expected "y

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
    *endptr = string;
    switch (*((*endptr)++)) {
    case 'R':
        return MoveExtraRook;
    case 'N':
        return MoveExtraKnight;
    case 'B':
        return MoveExtraBishop;
    case 'Q':
        return MoveExtraQueen;
    case '+':
        return MoveExtraCheck;
    case '#':
        return MoveExtraCheckmate;
    case 'e':
        if (strncmp(string, "e.p.", 4) == 0) {
            *endptr += 3;
            return MoveExtraEnPassant;
        }
        *endptr = string;
        return MoveExtraNone;
    }
    (*endptr)--;
    return MoveExtraNone;
}

int parseMove(
        const char* string,
        const char** endstr,
        Move* move,
        ParseError* parseError)
{
    const char* sptr = *endstr;
    const char* cptr = string;
    const char* endptr;
    if (*cptr == '0') {
        if (strncmp(cptr, "0-0-0", 5) == 0) {
            Field from;
            from.letter = FieldLetterE;
            from.number = FieldNumber1;
            Field to;
            to.letter = FieldLetterC;
            to.number = FieldNumber1;
            move->extra = MoveExtraLongCastling;
            move->type = MoveTypeQuiet;
            move->who = FigureTypeKing;
            move->from = from;
            move->to = to;
            *endstr = cptr + 5;
            return 0;
        }
        if (strncmp(cptr, "0-0", 3) == 0) {
            Field from;
            from.letter = FieldLetterE;
            from.number = FieldNumber1;
            Field to;
            to.letter = FieldLetterG;
            to.number = FieldNumber1;
            move->extra = MoveExtraShortCastling;
            move->type = MoveTypeQuiet;
            move->who = FigureTypeKing;
            move->from = from;
            move->to = to;
            *endstr = cptr + 3;
            return 0;
        }
        *endstr = cptr;
        parseError->errtype = ParseErrorTypeSyntax;
        parseError->column = endptr - sptr;
        sprintf(parseError->errstr,
                ERRFRMT("%td", "0-0 or 0-0-0"),
                endptr - sptr);
        return 1;
    }

    move->who = parseFigure(cptr, &endptr);
    if (move->who == FigureTypeNone) {
        parseError->errtype = ParseErrorTypeFigure;
        parseError->column = endptr - sptr;
        sprintf(parseError->errstr,
                ERRFRMT("%td", "<Figure char>, got %c"),
                endptr - sptr,
                *endptr);
        return 1;
    }
    cptr = endptr;

    move->from = parseField(cptr, &endptr);
    if (cptr == endptr) {
        parseError->errtype = ParseErrorTypeField;
        parseError->column = cptr - sptr;
        sprintf(parseError->errstr, ERRFRMT("%td", "<Field>"), cptr - sptr);
        return 1;
    }
    cptr = endptr;

    if (*cptr == '-') {
        move->type = MoveTypeQuiet;
    } else if (*cptr == 'x') {
        move->type = MoveTypeCapture;
    } else {
        parseError->errtype = ParseErrorTypeMove;
        parseError->column = cptr - sptr;
        sprintf(parseError->errstr,
                ERRFRMT("%td", "'-' or 'x', got %c"),
                cptr - sptr,
                *cptr);
        return 1;
    }
    cptr++;

    move->to = parseField(cptr, &endptr);
    if (cptr == endptr) {
        parseError->errtype = ParseErrorTypeField;
        parseError->column = cptr - sptr;
        sprintf(parseError->errstr, ERRFRMT("%td", "<Field>"), cptr - sptr);
        return 1;
    }
    cptr = endptr;

    move->extra = parseExtra(cptr, &endptr);
    *endstr = endptr;

    return 0;
}

int parseStep(const char* string, Moves* moves, ParseError* parseError)
{
    int errnum = 0;
    int num = 0;
    const char* cptr = string;
    const char* endptr;

    num = parseNumber(cptr, &endptr);
    if (num == 0) {
        parseError->errtype = ParseErrorTypeNumber;
        parseError->column = cptr - string;
        sprintf(parseError->errstr, ERRFRMT("0", "number"));
        return 1;
    }
    cptr = endptr;
    if (moves->count / 2 + 1 != num) {
        parseError->errtype = ParseErrorTypeNumber;
        parseError->column = cptr - string;
        sprintf(parseError->errstr, ERRFRMT("0", "%d"), moves->count / 2 + 1);
        return 1;
    }
    if (*cptr++ != '.') {
        parseError->errtype = ParseErrorTypeSyntax;
        parseError->column = cptr - string;
        sprintf(parseError->errstr, ERRFRMT("%td", "'.'"), cptr - string);
        return 1;
    }
    if (*cptr++ != ' ') {
        parseError->errtype = ParseErrorTypeSyntax;
        parseError->column = cptr - string;
        sprintf(parseError->errstr, ERRFRMT("%td", "' '"), cptr - string);
        return 1;
    }
    endptr = string;
    errnum = parseMove(cptr, &endptr, &moves->array[moves->count], parseError);
    if (errnum) {
        return errnum;
    }
    moves->count++;
    cptr = endptr;
    if (*cptr == '\0') {
        return 0;
    }
    if (*cptr++ != ' ') {
        parseError->errtype = ParseErrorTypeSyntax;
        parseError->column = cptr - string;
        sprintf(parseError->errstr,
                ERRFRMT("%td", "' ', got %c"),
                cptr - string,
                *cptr);
        return 1;
    }

    if (*cptr != ' ' && *cptr != '\0') {
        endptr = string;
        errnum = parseMove(
                cptr, &endptr, &moves->array[moves->count], parseError);
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
            parseError->errtype = ParseErrorTypeSyntax;
            parseError->column = cptr - string;
            sprintf(parseError->errstr,
                    ERRFRMT("%td", "end"),
                    cptr - string,
                    *cptr);
            return 1;
        }
        cptr = cptr + 1;
    }
}
