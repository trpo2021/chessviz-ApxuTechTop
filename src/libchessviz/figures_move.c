#include "figures_move.h"
#include <stdio.h>
#include <stdlib.h>

static const char* fttostr(FigureType ft)
{
    switch (ft) {
    case FigureTypeKing:
        return "King";
    case FigureTypeQueen:
        return "Queen";
    case FigureTypeRook:
        return "Rook";
    case FigureTypeKnight:
        return "Knight";
    case FigureTypeBishop:
        return "Bishop";
    case FigureTypePawn:
        return "Pawn";
    case FigureTypeNone:
        return "Nothing";
    }

    return "WTF";
}

int doMove(
        const Moves moves,
        const int index,
        Chessboard* chessboard,
        MoveError* moveError)
{
    Move move = moves.array[index];
    FieldNumber fn = move.from.number;
    FieldLetter fl = move.from.letter;
    FieldNumber tn = move.to.number;
    FieldLetter tl = move.to.letter;
    FigureSide fromSide = chessboard->cells[fn][fl].side;
    FigureType fromType = chessboard->cells[fn][fl].type;
    FigureSide toSide = chessboard->cells[tn][tl].side;
    FigureType toType = chessboard->cells[tn][tl].type;

    moveError->move = index + 1;
    char* errptr = moveError->errstr;
    errptr += sprintf(errptr, "Error at move %d: ", moveError->move);

    if (fromSide != (unsigned int)index % 2) {
        moveError->errtype = MoveErrorTypeAnotherSide;
        sprintf(errptr, "Cant move other side figures");
        return 1;
    }
    if (fromType == FigureTypeNone) {
        moveError->errtype = MoveErrorTypeAnotherFigure;
        sprintf(errptr, "No figure to move");
        return 1;
    }
    if (fromType != move.who) {
        moveError->errtype = MoveErrorTypeAnotherFigure;
        sprintf(errptr,
                "expected %s, got %s",
                fttostr(move.who),
                fttostr(fromType));
        return 1;
    }
    if (move.type == MoveTypeCapture) {
        if (fromSide == toSide) {
            moveError->errtype = MoveErrorTypeSelfAttack;
            sprintf(errptr, "Cant capture yourself");
            return 1;
        }
        if (toType == FigureTypeNone) {
            moveError->errtype = MoveErrorTypeMoveType;
            sprintf(errptr, "No figure for capture");
            return 1;
        }
    } else {
        if (toType != FigureTypeNone) {
            moveError->errtype = MoveErrorTypeMoveType;
            sprintf(errptr, "Didnt expect figure for quiet move");
            return 1;
        }
    }
    if (fromType == FigureTypePawn) {
        if (move.type == MoveTypeQuiet) {
            if (fl != tl) {
                moveError->errtype = MoveErrorTypeMove;
                sprintf(errptr, "Pawn can move only forward");
                return 1;
            }
        } else {
            if (fl == tl || abs((int)fl - (int)tl) > 1) {
                moveError->errtype = MoveErrorTypeAttack;
                sprintf(errptr, "Pawn can capture only diagonally");
                return 1;
            }
        }
        switch ((tn - fn) * (fromSide == FigureSideWhite ? 1 : -1)) {
        case 1:
            break;
        case 2:
            if (fn != FieldNumber2 && fn != FieldNumber7) {
                moveError->errtype = MoveErrorTypeMove;
                sprintf(errptr,
                        "Pawn can double move forward only at first step");
                return 1;
            }
            break;
        default:
            if (((int)(tn - fn) * (fromSide == FigureSideWhite ? 1 : -1)) < 0) {
                moveError->errtype = MoveErrorTypeMove;
                sprintf(errptr, "Pawn cant move backward");
            } else {
                moveError->errtype = MoveErrorTypeMove;
                sprintf(errptr, "Pawn can move forward a maximum of two cells");
            }
            return 1;
        }
    }

    chessboard->cells[fn][fl].side = FigureSideNone;
    chessboard->cells[fn][fl].type = FigureTypeNone;
    chessboard->cells[tn][tl].side = fromSide;
    chessboard->cells[tn][tl].type = fromType;

    return 0;
}
