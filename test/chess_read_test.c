#include <ctest.h>
#include <libchessviz/chess_read.h>

#define MOVE_ASSERT_EQUAL(exp, real)                 \
    ASSERT_EQUAL(exp.extra, real.extra);             \
    ASSERT_EQUAL(exp.who, real.who);                 \
    ASSERT_EQUAL(exp.type, real.type);               \
    ASSERT_EQUAL(exp.from.letter, real.from.letter); \
    ASSERT_EQUAL(exp.from.number, real.from.number); \
    ASSERT_EQUAL(exp.to.letter, real.to.letter);     \
    ASSERT_EQUAL(exp.to.number, real.to.number)

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

CTEST(chessParseError, BadSyntax7)
{
    Moves moves = {.count = 0};
    ParseError parseError;
    int result = parseStep("1. e2-e4e.p e7-e5", &moves, &parseError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(ParseErrorTypeSyntax, parseError.errtype);
}

CTEST(chessParseError, BadSyntax8)
{
    Moves moves = {.count = 0};
    ParseError parseError;
    int result = parseStep("1. e2-e4L e7-e5", &moves, &parseError);
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

CTEST(chessParseGood, QuiteMove)
{
    Moves moves = {.count = 0};
    ParseError parseError = {.errtype = ParseErrorTypeNone};
    Move expMove1
            = {.extra = MoveExtraNone,
               .who = FigureTypePawn,
               .type = MoveTypeQuiet,
               .from = {FieldLetterE, FieldNumber2},
               .to = {FieldLetterE, FieldNumber4}};
    Move expMove2
            = {.extra = MoveExtraNone,
               .who = FigureTypePawn,
               .type = MoveTypeQuiet,
               .from = {FieldLetterE, FieldNumber7},
               .to = {FieldLetterE, FieldNumber5}};
    int result = parseStep("1. e2-e4 e7-e5", &moves, &parseError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(2, moves.count);
    Move realMove1 = moves.array[0];
    Move realMove2 = moves.array[1];
    MOVE_ASSERT_EQUAL(expMove1, realMove1);
    MOVE_ASSERT_EQUAL(expMove2, realMove2);
}

CTEST(chessParseGood, CaptureMove)
{
    Moves moves = {.count = 0};
    ParseError parseError = {.errtype = ParseErrorTypeNone};
    Move expMove1
            = {.extra = MoveExtraNone,
               .who = FigureTypePawn,
               .type = MoveTypeCapture,
               .from = {FieldLetterE, FieldNumber2},
               .to = {FieldLetterE, FieldNumber4}};
    int result = parseStep("1. e2xe4 e7-e5", &moves, &parseError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(2, moves.count);
    Move realMove1 = moves.array[0];
    MOVE_ASSERT_EQUAL(expMove1, realMove1);
}

CTEST(chessParseGood, BishopAndKnightMove)
{
    Moves moves = {.count = 0};
    ParseError parseError = {.errtype = ParseErrorTypeNone};
    Move expMove1
            = {.extra = MoveExtraNone,
               .who = FigureTypeBishop,
               .type = MoveTypeQuiet,
               .from = {FieldLetterE, FieldNumber2},
               .to = {FieldLetterE, FieldNumber4}};
    Move expMove2
            = {.extra = MoveExtraNone,
               .who = FigureTypeKnight,
               .type = MoveTypeQuiet,
               .from = {FieldLetterE, FieldNumber7},
               .to = {FieldLetterE, FieldNumber5}};
    int result = parseStep("1. Be2-e4 Ne7-e5", &moves, &parseError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(2, moves.count);
    Move realMove1 = moves.array[0];
    Move realMove2 = moves.array[1];
    MOVE_ASSERT_EQUAL(expMove1, realMove1);
    MOVE_ASSERT_EQUAL(expMove2, realMove2);
}

CTEST(chessParseGood, RookAndQueenMove)
{
    Moves moves = {.count = 0};
    ParseError parseError = {.errtype = ParseErrorTypeNone};
    Move expMove1
            = {.extra = MoveExtraNone,
               .who = FigureTypeRook,
               .type = MoveTypeQuiet,
               .from = {FieldLetterE, FieldNumber2},
               .to = {FieldLetterE, FieldNumber4}};
    Move expMove2
            = {.extra = MoveExtraNone,
               .who = FigureTypeQueen,
               .type = MoveTypeQuiet,
               .from = {FieldLetterE, FieldNumber7},
               .to = {FieldLetterE, FieldNumber5}};
    int result = parseStep("1. Re2-e4 Qe7-e5", &moves, &parseError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(2, moves.count);
    Move realMove1 = moves.array[0];
    Move realMove2 = moves.array[1];
    MOVE_ASSERT_EQUAL(expMove1, realMove1);
    MOVE_ASSERT_EQUAL(expMove2, realMove2);
}

CTEST(chessParseGood, KingMove)
{
    Moves moves = {.count = 0};
    ParseError parseError = {.errtype = ParseErrorTypeNone};
    Move expMove1
            = {.extra = MoveExtraNone,
               .who = FigureTypeKing,
               .type = MoveTypeQuiet,
               .from = {FieldLetterE, FieldNumber2},
               .to = {FieldLetterE, FieldNumber4}};
    int result = parseStep("1. Ke2-e4 e7-e5", &moves, &parseError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(2, moves.count);
    Move realMove1 = moves.array[0];
    MOVE_ASSERT_EQUAL(expMove1, realMove1);
}

CTEST(chessParseGood, ShortAndLongCastling)
{
    Moves moves = {.count = 0};
    ParseError parseError = {.errtype = ParseErrorTypeNone};
    Move expMove1
            = {.extra = MoveExtraShortCastling,
               .who = FigureTypeKing,
               .type = MoveTypeQuiet,
               .from = {FieldLetterE, FieldNumber1},
               .to = {FieldLetterG, FieldNumber1}};
    Move expMove2
            = {.extra = MoveExtraLongCastling,
               .who = FigureTypeKing,
               .type = MoveTypeQuiet,
               .from = {FieldLetterE, FieldNumber1},
               .to = {FieldLetterC, FieldNumber1}};
    int result = parseStep("1. 0-0 0-0-0", &moves, &parseError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(2, moves.count);
    Move realMove1 = moves.array[0];
    Move realMove2 = moves.array[1];
    MOVE_ASSERT_EQUAL(expMove1, realMove1);
    MOVE_ASSERT_EQUAL(expMove2, realMove2);
}

CTEST(chessParseGood, CheckAndCheckmate)
{
    Moves moves = {.count = 0};
    ParseError parseError = {.errtype = ParseErrorTypeNone};
    Move expMove1
            = {.extra = MoveExtraCheck,
               .who = FigureTypeRook,
               .type = MoveTypeQuiet,
               .from = {FieldLetterE, FieldNumber2},
               .to = {FieldLetterE, FieldNumber4}};
    Move expMove2
            = {.extra = MoveExtraCheckmate,
               .who = FigureTypeQueen,
               .type = MoveTypeQuiet,
               .from = {FieldLetterE, FieldNumber7},
               .to = {FieldLetterE, FieldNumber5}};
    int result = parseStep("1. Re2-e4+ Qe7-e5#", &moves, &parseError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(2, moves.count);
    Move realMove1 = moves.array[0];
    Move realMove2 = moves.array[1];
    MOVE_ASSERT_EQUAL(expMove1, realMove1);
    MOVE_ASSERT_EQUAL(expMove2, realMove2);
}

CTEST(chessParseGood, EnPasssant)
{
    Moves moves = {.count = 0};
    ParseError parseError = {.errtype = ParseErrorTypeNone};
    Move expMove1
            = {.extra = MoveExtraEnPassant,
               .who = FigureTypePawn,
               .type = MoveTypeQuiet,
               .from = {FieldLetterE, FieldNumber2},
               .to = {FieldLetterE, FieldNumber4}};

    int result = parseStep("1. e2-e4e.p. Qe7-e5#", &moves, &parseError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(2, moves.count);
    Move realMove1 = moves.array[0];
    MOVE_ASSERT_EQUAL(expMove1, realMove1);
}

CTEST(chessParseGood, FourMoves)
{
    Moves moves = {.count = 0};
    ParseError parseError = {.errtype = ParseErrorTypeNone};
    int result = parseStep("1. Re2-e4 Qe7-e5", &moves, &parseError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(2, moves.count);
    result = parseStep("2. Re2-e4 Qe7-e5", &moves, &parseError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(4, moves.count);
}

CTEST(chessParseGood, ThreeMoves)
{
    Moves moves = {.count = 0};
    ParseError parseError = {.errtype = ParseErrorTypeNone};
    int result = parseStep("1. Re2-e4 Qe7-e5", &moves, &parseError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(2, moves.count);
    result = parseStep("2. Re2-e4", &moves, &parseError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(3, moves.count);
}
