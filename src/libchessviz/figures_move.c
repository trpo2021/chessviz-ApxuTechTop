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
        char* errstr)
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
    if (fromSide != (unsigned int)index % 2) {
        sprintf(errstr,
                "Error at move %d: Cant move other side figures",
                index + 1);
        return 1;
    }
    if (fromType == FigureTypeNone) {
        sprintf(errstr, "Error at move %d: No figure to move", index + 1);
        return 1;
    }
    if (fromType != move.who) {
        sprintf(errstr,
                "Error at move %d: expected %s, got %s",
                index + 1,
                fttostr(fromType),
                fttostr(move.who));
        return 1;
    }
    if (move.type == MoveTypeCapture) {
        if (fromSide == toSide) {
            sprintf(errstr,
                    "Error at move %d: Cant capture yourself",
                    index + 1);
            return 1;
        }
        if (toType == FigureTypeNone) {
            sprintf(errstr,
                    "Error at move %d: No figure for capture",
                    index + 1);
            return 1;
        }
    } else {
        if (toType != FigureTypeNone) {
            sprintf(errstr,
                    "Error at move %d: Didnt expect figure for quiet move",
                    index + 1);
            return 1;
        }
    }
    if (fromType == FigureTypePawn) {
        if (move.type == MoveTypeQuiet) {
            if (fl != tl) {
                sprintf(errstr,
                        "Error at move %d: Pawn can move only forward",
                        index + 1);
                return 1;
            }
        } else {
            if (fl == tl || abs(fl - tl) > 1) {
                sprintf(errstr,
                        "Error at move %d: Pawn can capture only diagonally",
                        index + 1);
                return 1;
            }
        }
        switch ((tn - fn) * (fromSide == FigureSideWhite ? 1 : -1)) {
        case 1:
            break;
        case 2:
            if (fn != FieldNumber2 && fn != FieldNumber7) {
                sprintf(errstr,
                        "Error at move %d: Pawn can double move forward only "
                        "at first step",
                        index + 1);
                return 1;
            }
            break;
        default:
            if (((int)(tn - fn) * (fromSide == FigureSideWhite ? 1 : -1)) < 0) {
                sprintf(errstr,
                        "Error at move %d: Pawn cant move backward",
                        index + 1);
            } else {
                sprintf(errstr,
                        "Error at move %d: Pawn can move forward a maximum of "
                        "two cells",
                        index + 1);
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
