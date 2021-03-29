#include <ctest.h>
#include <libchessviz/chessboard_create.h>
#include <libchessviz/figures_move.h>

CTEST(pawnMoveError, PawnDiagonalMove)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterE, FieldNumber2},
               {FieldLetterD, FieldNumber3},
               FigureTypePawn,
               MoveTypeQuiet,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "        "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(pawnMoveError, PawnThreeFieldsMove)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterE, FieldNumber2},
               {FieldLetterE, FieldNumber5},
               FigureTypePawn,
               MoveTypeQuiet,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "        "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(pawnMoveError, PawnDirectAttack)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterE, FieldNumber2},
               {FieldLetterE, FieldNumber3},
               FigureTypePawn,
               MoveTypeCapture,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "    p   "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeAttack, moveError.errtype);
}

CTEST(pawnMoveError, PawnHorizontalMove)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterE, FieldNumber3},
               {FieldLetterD, FieldNumber3},
               FigureTypePawn,
               MoveTypeQuiet,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "    P   "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(pawnMoveError, PawnBackwardMove)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterE, FieldNumber4},
               {FieldLetterE, FieldNumber3},
               FigureTypePawn,
               MoveTypeQuiet,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "    P   "
            "        "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(pawnMoveError, PawnWrongEnPassant)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterE, FieldNumber5},
               {FieldLetterD, FieldNumber6},
               FigureTypePawn,
               MoveTypeCapture,
               MoveExtraEnPassant};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "   pP   "
            "        "
            "        "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeAnotherFigure, moveError.errtype);
}

CTEST(pawnMoveError, PawnWrongAttack)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterE, FieldNumber5},
               {FieldLetterD, FieldNumber5},
               FigureTypePawn,
               MoveTypeCapture,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "   pP   "
            "        "
            "        "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(knightMoveError, knightWrongMove1)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterB, FieldNumber1},
               {FieldLetterB, FieldNumber3},
               FigureTypeKnight,
               MoveTypeQuiet,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "   pP   "
            "        "
            "        "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(knightMoveError, knightWrongAttack)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterA, FieldNumber3},
               {FieldLetterC, FieldNumber5},
               FigureTypeKnight,
               MoveTypeCapture,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "  p     "
            "        "
            "N       "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(bishopMoveError, BishopWrongMove1)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterA, FieldNumber3},
               {FieldLetterC, FieldNumber3},
               FigureTypeBishop,
               MoveTypeQuiet,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "B       "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(bishopMoveError, BishopWrongMove2)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterA, FieldNumber3},
               {FieldLetterC, FieldNumber5},
               FigureTypeBishop,
               MoveTypeQuiet,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            " P      "
            "B       "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(bishopMoveError, BishopWrongAttack)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterA, FieldNumber3},
               {FieldLetterC, FieldNumber5},
               FigureTypeBishop,
               MoveTypeCapture,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "  p     "
            " P      "
            "B       "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(rookMoveError, RookWrongMove1)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterA, FieldNumber3},
               {FieldLetterC, FieldNumber5},
               FigureTypeRook,
               MoveTypeQuiet,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            " P      "
            "R       "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(rookMoveError, RookWrongMove2)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterA, FieldNumber3},
               {FieldLetterC, FieldNumber3},
               FigureTypeRook,
               MoveTypeQuiet,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            " P      "
            "RP      "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(rookMoveError, RookWrongAttack)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterA, FieldNumber3},
               {FieldLetterC, FieldNumber3},
               FigureTypeRook,
               MoveTypeCapture,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            " P      "
            "RPp     "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(queenMoveError, QueenWrongMove1)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterA, FieldNumber3},
               {FieldLetterB, FieldNumber5},
               FigureTypeQueen,
               MoveTypeQuiet,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            " P      "
            "QPp     "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(queenMoveError, QueenWrongMove2)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterA, FieldNumber3},
               {FieldLetterD, FieldNumber3},
               FigureTypeQueen,
               MoveTypeQuiet,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            " P      "
            "QPp     "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(queenMoveError, QueenWrongMove3)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterA, FieldNumber3},
               {FieldLetterC, FieldNumber5},
               FigureTypeQueen,
               MoveTypeQuiet,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            " P      "
            "QPp     "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(queenMoveError, QueenWrongAttack1)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterA, FieldNumber3},
               {FieldLetterC, FieldNumber5},
               FigureTypeQueen,
               MoveTypeCapture,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "  p     "
            " P      "
            "QPp     "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(queenMoveError, QueenWrongAttack2)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterA, FieldNumber3},
               {FieldLetterC, FieldNumber3},
               FigureTypeQueen,
               MoveTypeCapture,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "  p     "
            " P      "
            "QPp     "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(kingMoveError, KingWrongMove1)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterA, FieldNumber3},
               {FieldLetterA, FieldNumber5},
               FigureTypeKing,
               MoveTypeQuiet,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "K       "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(kingMoveError, KingWrongMove2)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterA, FieldNumber3},
               {FieldLetterA, FieldNumber4},
               FigureTypeKing,
               MoveTypeQuiet,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "       r"
            "K       "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(kingMoveError, KingWrongAttack)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterA, FieldNumber3},
               {FieldLetterA, FieldNumber4},
               FigureTypeKing,
               MoveTypeCapture,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            " p      "
            "p       "
            "K       "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(kingMoveError, KingWrongCastling1)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterE, FieldNumber1},
               {FieldLetterG, FieldNumber1},
               FigureTypeKing,
               MoveTypeQuiet,
               MoveExtraShortCastling};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "        "
            "PPPPPPPP"
            "RNBQKB R");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(kingMoveError, KingWrongCastling2)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterE, FieldNumber1},
               {FieldLetterC, FieldNumber1},
               FigureTypeKing,
               MoveTypeQuiet,
               MoveExtraLongCastling};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "        "
            "PPPPPPPP"
            "RN  KBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(kingMoveError, KingWrongCastling3)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterE, FieldNumber1},
               {FieldLetterC, FieldNumber1},
               FigureTypeKing,
               MoveTypeQuiet,
               MoveExtraLongCastling};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "   r    "
            "PPP PPPP"
            "R   KBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(kingMoveError, KingWrongCastling4)
{
    Moves moves = {.count = 3};
    Move move1
            = {{FieldLetterD, FieldNumber1},
               {FieldLetterE, FieldNumber1},
               FigureTypeKing,
               MoveTypeQuiet,
               MoveExtraNone};
    Move move3
            = {{FieldLetterE, FieldNumber1},
               {FieldLetterC, FieldNumber1},
               FigureTypeKing,
               MoveTypeQuiet,
               MoveExtraLongCastling};
    moves.array[0] = move1;
    moves.array[2] = move3;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "        "
            "PPP PPPP"
            "R  K BNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(0, result);
    result = doMove(moves, 2, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(kingMoveError, KingWrongCastling5)
{
    Moves moves = {.count = 5};
    Move move1
            = {{FieldLetterA, FieldNumber1},
               {FieldLetterA, FieldNumber2},
               FigureTypeRook,
               MoveTypeQuiet,
               MoveExtraNone};
    Move move3
            = {{FieldLetterA, FieldNumber2},
               {FieldLetterA, FieldNumber1},
               FigureTypeRook,
               MoveTypeQuiet,
               MoveExtraNone};
    Move move5
            = {{FieldLetterE, FieldNumber1},
               {FieldLetterC, FieldNumber1},
               FigureTypeKing,
               MoveTypeQuiet,
               MoveExtraLongCastling};
    moves.array[0] = move1;
    moves.array[2] = move3;
    moves.array[4] = move5;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "        "
            " PP PPPP"
            "R   KBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(0, result);
    result = doMove(moves, 2, &chessboard, &moveError);
    ASSERT_EQUAL(0, result);
    result = doMove(moves, 4, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(kingMoveError, KingWrongCastling6)
{
    Moves moves = {.count = 5};
    Move move1
            = {{FieldLetterH, FieldNumber1},
               {FieldLetterH, FieldNumber2},
               FigureTypeRook,
               MoveTypeQuiet,
               MoveExtraNone};
    Move move3
            = {{FieldLetterH, FieldNumber2},
               {FieldLetterH, FieldNumber1},
               FigureTypeRook,
               MoveTypeQuiet,
               MoveExtraNone};
    Move move5
            = {{FieldLetterE, FieldNumber1},
               {FieldLetterG, FieldNumber1},
               FigureTypeKing,
               MoveTypeQuiet,
               MoveExtraShortCastling};
    moves.array[0] = move1;
    moves.array[2] = move3;
    moves.array[4] = move5;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "        "
            "RPP PPP "
            "    K  R");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(0, result);
    result = doMove(moves, 2, &chessboard, &moveError);
    ASSERT_EQUAL(0, result);
    result = doMove(moves, 4, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(kingMoveError, KingBadSave)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterF, FieldNumber2},
               {FieldLetterE, FieldNumber3},
               FigureTypePawn,
               MoveTypeCapture,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "    r b "
            "PPPP PPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeAnotherFigure, moveError.errtype);
}

CTEST(kingMoveError, KingNotSafeMove)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterE, FieldNumber1},
               {FieldLetterE, FieldNumber2},
               FigureTypeKing,
               MoveTypeQuiet,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "      b "
            "        "
            "PPPP PPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeMove, moveError.errtype);
}

CTEST(otherMoveError, SelfAttack)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterH, FieldNumber1},
               {FieldLetterG, FieldNumber1},
               FigureTypeRook,
               MoveTypeCapture,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "        "
            "RPP PPP "
            "    K NR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeSelfAttack, moveError.errtype);
}

CTEST(otherMoveError, AnotherSide)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterE, FieldNumber7},
               {FieldLetterE, FieldNumber5},
               FigureTypePawn,
               MoveTypeQuiet,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "        "
            "RPP PPP "
            "    K NR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeAnotherSide, moveError.errtype);
}

CTEST(otherMoveError, AnotherFigure)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterA, FieldNumber2},
               {FieldLetterA, FieldNumber4},
               FigureTypePawn,
               MoveTypeQuiet,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "        "
            "RPP PPP "
            "    K NR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(MoveErrorTypeAnotherFigure, moveError.errtype);
}

CTEST(pawnMoveGood, PawnMoveForward)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterE, FieldNumber2},
               {FieldLetterE, FieldNumber3},
               FigureTypePawn,
               MoveTypeQuiet,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "        "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(MoveErrorTypeNone, moveError.errtype);
}

CTEST(pawnMoveGood, PawnMoveForwardDouble)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterE, FieldNumber2},
               {FieldLetterE, FieldNumber4},
               FigureTypePawn,
               MoveTypeQuiet,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "        "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(MoveErrorTypeNone, moveError.errtype);
}

CTEST(pawnMoveGood, PawnAttack)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterA, FieldNumber2},
               {FieldLetterB, FieldNumber3},
               FigureTypePawn,
               MoveTypeCapture,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            " p     "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(MoveErrorTypeNone, moveError.errtype);
}

CTEST(knightMoveGood, KnightMove1)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterB, FieldNumber1},
               {FieldLetterC, FieldNumber3},
               FigureTypeKnight,
               MoveTypeQuiet,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "        "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(MoveErrorTypeNone, moveError.errtype);
}

CTEST(knightMoveGood, KnightMove2)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterA, FieldNumber3},
               {FieldLetterC, FieldNumber4},
               FigureTypeKnight,
               MoveTypeQuiet,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "N       "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(MoveErrorTypeNone, moveError.errtype);
}

CTEST(knightMoveGood, KnightAttack1)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterA, FieldNumber3},
               {FieldLetterC, FieldNumber4},
               FigureTypeKnight,
               MoveTypeCapture,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "  p     "
            "N       "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(MoveErrorTypeNone, moveError.errtype);
}

CTEST(knightMoveGood, KnightAttack2)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterA, FieldNumber3},
               {FieldLetterB, FieldNumber5},
               FigureTypeKnight,
               MoveTypeCapture,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            " p      "
            "  p     "
            "N       "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(MoveErrorTypeNone, moveError.errtype);
}

CTEST(bishopMoveGood, BishopMove)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterC, FieldNumber4},
               {FieldLetterE, FieldNumber6},
               FigureTypeBishop,
               MoveTypeQuiet,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "  B     "
            "        "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(MoveErrorTypeNone, moveError.errtype);
}

CTEST(bishopMoveGood, BishopAttack)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterC, FieldNumber4},
               {FieldLetterF, FieldNumber7},
               FigureTypeBishop,
               MoveTypeCapture,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "  B     "
            "        "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(MoveErrorTypeNone, moveError.errtype);
}

CTEST(rookMoveGood, RookMove)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterH, FieldNumber1},
               {FieldLetterH, FieldNumber5},
               FigureTypeRook,
               MoveTypeQuiet,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "  B     "
            "        "
            "PPPPPPP "
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(MoveErrorTypeNone, moveError.errtype);
}

CTEST(rookMoveGood, RookAttack)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterH, FieldNumber4},
               {FieldLetterH, FieldNumber7},
               FigureTypeRook,
               MoveTypeCapture,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "  B    R"
            "        "
            "PPPPPPP "
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(MoveErrorTypeNone, moveError.errtype);
}

CTEST(queenMoveGood, QueenMove1)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterH, FieldNumber4},
               {FieldLetterH, FieldNumber6},
               FigureTypeQueen,
               MoveTypeQuiet,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "  B    Q"
            "        "
            "PPPPPPP "
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(MoveErrorTypeNone, moveError.errtype);
}

CTEST(queenMoveGood, QueenMove2)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterH, FieldNumber4},
               {FieldLetterF, FieldNumber6},
               FigureTypeQueen,
               MoveTypeQuiet,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "  B    Q"
            "        "
            "PPPPPPP "
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(MoveErrorTypeNone, moveError.errtype);
}

CTEST(queenMoveGood, QueenAttack1)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterH, FieldNumber4},
               {FieldLetterE, FieldNumber7},
               FigureTypeQueen,
               MoveTypeCapture,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "  B    Q"
            "        "
            "PPPPPPP "
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(MoveErrorTypeNone, moveError.errtype);
}

CTEST(queenMoveGood, QueenAttack2)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterH, FieldNumber4},
               {FieldLetterH, FieldNumber7},
               FigureTypeQueen,
               MoveTypeCapture,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "  B    Q"
            "        "
            "PPPPPPP "
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(MoveErrorTypeNone, moveError.errtype);
}

CTEST(kingMoveGood, KingMove)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterE, FieldNumber3},
               {FieldLetterE, FieldNumber4},
               FigureTypeKing,
               MoveTypeQuiet,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "    K   "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(MoveErrorTypeNone, moveError.errtype);
}

CTEST(kingMoveGood, KingAttack)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterE, FieldNumber3},
               {FieldLetterE, FieldNumber4},
               FigureTypeKing,
               MoveTypeCapture,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "    p   "
            "    K   "
            "PPPPPPPP"
            "RNBQKBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(MoveErrorTypeNone, moveError.errtype);
}

CTEST(kingMoveGood, KingShortCastling)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterE, FieldNumber1},
               {FieldLetterG, FieldNumber1},
               FigureTypeKing,
               MoveTypeQuiet,
               MoveExtraShortCastling};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "        "
            "PPPPPPPP"
            "RNBQK  R");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(MoveErrorTypeNone, moveError.errtype);
}

CTEST(kingMoveGood, KingLongCastling)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterE, FieldNumber1},
               {FieldLetterC, FieldNumber1},
               FigureTypeKing,
               MoveTypeQuiet,
               MoveExtraLongCastling};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "        "
            "PPPPPPPP"
            "R   KBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(MoveErrorTypeNone, moveError.errtype);
}

CTEST(kingMoveGood, KingGoodSave1)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterE, FieldNumber1},
               {FieldLetterD, FieldNumber1},
               FigureTypeKing,
               MoveTypeQuiet,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "    r   "
            "PPPP PPP"
            "R   KBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(MoveErrorTypeNone, moveError.errtype);
}

CTEST(kingMoveGood, KingGoodSave2)
{
    Moves moves = {.count = 1};
    Move move1
            = {{FieldLetterD, FieldNumber2},
               {FieldLetterE, FieldNumber3},
               FigureTypePawn,
               MoveTypeCapture,
               MoveExtraNone};
    moves.array[0] = move1;
    MoveError moveError = {.errtype = MoveErrorTypeNone};
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "    r   "
            "PPPP PPP"
            "R   KBNR");
    int result = doMove(moves, 0, &chessboard, &moveError);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(MoveErrorTypeNone, moveError.errtype);
}
