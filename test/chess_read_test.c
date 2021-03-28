#include <ctest.h>
#include <libchessviz/chess_read.h>

CTEST(chessParseError, WrongNum)
{
    Moves moves = {.count = 0};
    ParseError parseError;
    int result = parseStep("2. e2-e4 e7-e5", &moves, &parseError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(ParseErrorTypeNumber, parseError.errtype);
}

CTEST(chessParseError, BadSyntax1)
{
    Moves moves = {.count = 0};
    ParseError parseError;
    int result = parseStep("1 . e2-e4 e7-e5", &moves, &parseError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(ParseErrorTypeSyntax, parseError.errtype);
}

CTEST(chessParseError, BadSyntax2)
{
    Moves moves = {.count = 0};
    ParseError parseError;
    int result = parseStep("1.e2-e4 e7-e5", &moves, &parseError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(ParseErrorTypeSyntax, parseError.errtype);
}

CTEST(chessParseError, BadSyntax3)
{
    Moves moves = {.count = 0};
    ParseError parseError;
    int result = parseStep("1. e2-e4  e7-e5", &moves, &parseError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(ParseErrorTypeSyntax, parseError.errtype);
}

CTEST(chessParseError, BadSyntax4)
{
    Moves moves = {.count = 0};
    ParseError parseError;
    int result = parseStep("1. e2-e4 e7-e5    c", &moves, &parseError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(ParseErrorTypeSyntax, parseError.errtype);
}

CTEST(chessParseError, BadSyntax5)
{
    Moves moves = {.count = 0};
    ParseError parseError;
    int result = parseStep("1. 0-0-O e7-e5", &moves, &parseError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(ParseErrorTypeSyntax, parseError.errtype);
}

CTEST(chessParseError, BadSyntax6)
{
    Moves moves = {.count = 0};
    ParseError parseError;
    int result = parseStep("1. 0-O e7-e5", &moves, &parseError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(ParseErrorTypeSyntax, parseError.errtype);
}

CTEST(chessParseError, WrongField1)
{
    Moves moves = {.count = 0};
    ParseError parseError;
    int result = parseStep("1. q2-e4 e7-e5", &moves, &parseError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(ParseErrorTypeField, parseError.errtype);
}

CTEST(chessParseError, WrongField2)
{
    Moves moves = {.count = 0};
    ParseError parseError;
    int result = parseStep("1. e0-e4 e7-e5", &moves, &parseError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(ParseErrorTypeField, parseError.errtype);
}

CTEST(chessParseError, WrongMoveType)
{
    Moves moves = {.count = 0};
    ParseError parseError;
    int result = parseStep("1. e2_e4 e7-e5", &moves, &parseError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(ParseErrorTypeMove, parseError.errtype);
}

CTEST(chessParseError, WrongFigure1)
{
    Moves moves = {.count = 0};
    ParseError parseError;
    int result = parseStep("1. Ce2-e4 e7-e5", &moves, &parseError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(ParseErrorTypeFigure, parseError.errtype);
}

CTEST(chessParseError, WrongFigure2)
{
    Moves moves = {.count = 0};
    ParseError parseError;
    int result = parseStep("1.  e2-e4 e7-e5", &moves, &parseError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(ParseErrorTypeFigure, parseError.errtype);
}
