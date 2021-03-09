#include "figures_move.h"
#include <stdio.h>
#include <stdlib.h>

int doMove(const Move move, Chessboard* chessboard)
{
    FieldNumber fn = move.from.number;
    FieldLetter fl = move.from.letter;
    FieldNumber tn = move.to.number;
    FieldLetter tl = move.to.letter;
    FigureSide fromSide = chessboard->cells[fn][fl].side;
    FigureType fromType = chessboard->cells[fn][fl].type;
    FigureSide toSide = chessboard->cells[tn][tl].side;
    FigureType toType = chessboard->cells[tn][tl].type;
    if (fromType == FigureTypeNone) {
        return 1;
    }
    if (fromType != move.who) {
        printf("(%d %d, %d %d)", fromType, move.who, fn, fl);
        return 2;
    }
    if (move.type == MoveTypeCapture) {
        if (fromSide == toSide) {
            return 3;
        }
    } else {
        if (toType != FigureTypeNone) {
            return 4;
        }
    }
    if (fromType == FigureTypePawn) {
        if (move.type == MoveTypeQuiet && fl != tl) {
            return 5;
        }
        switch ((tn - fn) * (fromSide == FigureSideWhite ? 1 : -1)) {
        case 1:
            break;
        case 2:
            if (fn != FieldNumber2 && fn != FieldNumber7) {
                return 6;
            }
            break;
        default:
            return 7;
        }
    }

    chessboard->cells[fn][fl].side = FigureSideNone;
    chessboard->cells[fn][fl].type = FigureTypeNone;
    chessboard->cells[tn][tl].side = fromSide;
    chessboard->cells[tn][tl].type = fromType;

    return 0;
}
