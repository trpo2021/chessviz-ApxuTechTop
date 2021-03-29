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

static int
isAttacked(Field field, const Chessboard* chessboard, FigureSide side)
{
    if (side == FigureSideNone) {
        return 0;
    }

    FieldNumber n = field.number;
    FieldLetter l = field.letter;
    int d;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            d = 1;

            while ((int)n + i * d >= 0 && (int)l + j * d >= 0
                   && (int)n + i * d < CHESSBOARD_SIZE
                   && (int)l + j * d < CHESSBOARD_SIZE) {
                if (d == 1) {
                    Figure f = chessboard->cells[n + i][l + j];
                    if (f.side != side && f.type == FigureTypeKing) {
                        return 1;
                    }
                }
                Figure f = chessboard->cells[n + i * d][l + j * d];
                if (f.side == side) {
                    break;
                }
                if (f.type == FigureTypeQueen) {
                    return 1;
                }
                if (i * j == 0) {
                    if (f.type == FigureTypeRook) {
                        return 1;
                    }
                } else if (f.type == FigureTypeBishop) {
                    return 1;
                }

                d++;
            }
        }
    }
    for (int k = 0; k <= 1; k++) {
        for (int i = -1; i <= 1; i += 2) {
            for (int j = -1; j <= 1; j += 2) {
                int kn, kl;
                kn = (int)n + i * (1 + k);
                kl = (int)l + j * (2 - k);
                if (kn >= 0 && kl >= 0 && kn < CHESSBOARD_SIZE
                    && kl < CHESSBOARD_SIZE) {
                    Figure f = chessboard->cells[kn][kl];
                    if (f.side != side && f.type == FigureTypeKnight) {
                        return 1;
                    }
                }
            }
        }
    }
    int i = side == FigureSideWhite ? 1 : -1;
    for (int j = -1; j <= 1; j += 2) {
        int kn, kl;
        kn = (int)n + i;
        kl = (int)l + j;
        if (kn >= 0 && kl >= 0 && kn < CHESSBOARD_SIZE
            && kl < CHESSBOARD_SIZE) {
            Figure f = chessboard->cells[kn][kl];
            if (f.side != side && f.type == FigureTypePawn) {
                return 1;
            }
        }
    }

    return 0;
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

    if (fromType == FigureTypeNone) {
        moveError->errtype = MoveErrorTypeAnotherFigure;
        sprintf(errptr, "No figure to move");
        return 1;
    }
    if (fromSide != (unsigned int)index % 2) {
        moveError->errtype = MoveErrorTypeAnotherSide;
        sprintf(errptr, "Cant move other side figures");
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
        if (toType == FigureTypeNone && move.extra != MoveExtraEnPassant) {
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
    if (move.extra == MoveExtraEnPassant || move.extra == MoveExtraBishop
        || move.extra == MoveExtraKnight || move.extra == MoveExtraRook
        || move.extra == MoveExtraQueen) {
        if (move.who != FigureTypePawn) {
            moveError->errtype = MoveErrorTypeAnotherFigure;
            sprintf(errptr, "expected Pawn, got %s", fttostr(move.who));
            return 1;
        }
    }
    switch (fromType) {
    case FigureTypePawn:
        if (move.type == MoveTypeQuiet) {
            if (move.extra == MoveExtraEnPassant) {
                moveError->errtype = MoveErrorTypeMoveType;
                sprintf(errptr, "Expected capture move");
                return 1;
            }
            if (fl != tl) {
                moveError->errtype = MoveErrorTypeMove;
                sprintf(errptr, "Pawn can move only forward");
                return 1;
            }
        } else if (move.type == MoveTypeCapture) {
            if (fl == tl || abs((int)fl - (int)tl) > 1) {
                moveError->errtype = MoveErrorTypeAttack;
                sprintf(errptr, "Pawn can capture only diagonally");
                return 1;
            }
            if (move.extra == MoveExtraEnPassant) {
                Move prevMove = moves.array[index - 1];
                if ((index - 1) < 0 || prevMove.who != FigureTypePawn) {
                    moveError->errtype = MoveErrorTypeAnotherFigure;
                    sprintf(errptr,
                            "Do en passant after long Pawn's move "
                            "immediately");
                    return 1;
                }
                if (fn
                    != (fromSide == FigureSideWhite ? FieldNumber5
                                                    : FieldNumber4)) {
                    moveError->errtype = MoveErrorTypeAttack;
                    sprintf(errptr, "Pawn cant do en passant");
                    return 1;
                }
                if (prevMove.from.number
                    != (fromSide == FigureSideWhite ? FieldNumber7
                                                    : FieldNumber2)) {
                    moveError->errtype = MoveErrorTypeAttack;
                    sprintf(errptr, "No Pawn for en passant");
                    return 1;
                }
                if (prevMove.to.number
                    != (fromSide == FigureSideWhite ? FieldNumber5
                                                    : FieldNumber4)) {
                    moveError->errtype = MoveErrorTypeAttack;
                    sprintf(errptr,
                            "Can do en passant only after long Pawn's "
                            "move");
                    return 1;
                }
                if (prevMove.from.letter != move.to.letter) {
                    moveError->errtype = MoveErrorTypeAttack;
                    sprintf(errptr, "Wrong Pawn for en passant");
                    return 1;
                }
            }
        }
        int md = (int)(tn - fn) * (fromSide == FigureSideWhite ? 1 : -1);
        switch (md) {
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
            if (md < 0) {
                moveError->errtype = MoveErrorTypeMove;
                sprintf(errptr, "Pawn cant move backward");
            } else {
                moveError->errtype = MoveErrorTypeMove;
                sprintf(errptr, "Pawn can move forward a maximum of two cells");
            }
            return 1;
        }
        if (move.extra == MoveExtraBishop || move.extra == MoveExtraKnight
            || move.extra == MoveExtraRook || move.extra == MoveExtraQueen) {
            if (fn
                != (fromSide == FigureSideWhite ? FieldNumber7
                                                : FieldNumber2)) {
                moveError->errtype = MoveErrorTypeMove;
                sprintf(errptr, "Wrong move for evolve");
                return 1;
            }
            chessboard->cells[fn][fl].side = FigureSideNone;
            chessboard->cells[fn][fl].type = FigureTypeNone;
            chessboard->cells[tn][tl].side = fromSide;
            switch (move.extra) {
            case MoveExtraBishop:
                chessboard->cells[tn][tl].type = FigureTypeBishop;
                break;
            case MoveExtraKnight:
                chessboard->cells[tn][tl].type = FigureTypeKnight;
                break;
            case MoveExtraRook:
                chessboard->cells[tn][tl].type = FigureTypeRook;
                break;
            case MoveExtraQueen:
                chessboard->cells[tn][tl].type = FigureTypeQueen;
                break;
            default:
                break;
            }
            return 0;
        } else if (
                tn
                == (fromSide == FigureSideWhite ? FieldNumber8
                                                : FieldNumber1)) {
            moveError->errtype = MoveErrorTypeMove;
            sprintf(errptr, "Pawn must to evolve");
            return 1;
        }
        break;
    case FigureTypeBishop: {
        if (abs((int)fn - (int)tn) != abs((int)fl - (int)tl)) {
            moveError->errtype = MoveErrorTypeMove;
            sprintf(errptr, "Bishop can move only diagonally");
            return 1;
        }
        FieldNumber n = fn;
        FieldLetter l = fl;
        n = n + ((fn < tn) ? 1 : -1);
        l = l + ((fl < tl) ? 1 : -1);
        while ((n != tn) && (l != tl)) {
            if (chessboard->cells[n][l].type != FigureTypeNone) {
                moveError->errtype = MoveErrorTypeMove;
                sprintf(errptr, "Bishop cant move through figures");
                return 1;
            }
            n = n + ((fn < tn) ? 1 : -1);
            l = l + ((fl < tl) ? 1 : -1);
        }
        break;
    }
    case FigureTypeKnight: {
        int num = abs((int)fn - (int)tn);
        int let = abs((int)fl - (int)tl);
        if (!((num == 1 && let == 2) || (num == 2 && let == 1))) {
            moveError->errtype = MoveErrorTypeMove;
            sprintf(errptr, "Knight can move like 'L'");
            return 1;
        }
        break;
    }
    case FigureTypeRook: {
        if (fn != tn && fl != tl) {
            moveError->errtype = MoveErrorTypeMove;
            sprintf(errptr, "Rook can move only vertically or horizontally");
            return 1;
        }
        FieldNumber n = fn;
        FieldLetter l = fl;
        n = n + ((fn < tn) ? 1 : -1) * ((fn == tn) ? 0 : 1);
        l = l + ((fl < tl) ? 1 : -1) * ((fl == tl) ? 0 : 1);
        while (n != tn || l != tl) {
            if (chessboard->cells[n][l].type != FigureTypeNone) {
                moveError->errtype = MoveErrorTypeMove;
                sprintf(errptr, "Rook cant move through figures");
                return 1;
            }
            n = n + ((fn < tn) ? 1 : -1) * ((fn == tn) ? 0 : 1);
            l = l + ((fl < tl) ? 1 : -1) * ((fl == tl) ? 0 : 1);
        }
        break;
    }

    case FigureTypeQueen: {
        if ((abs((int)fn - (int)tn) != abs((int)fl - (int)tl))
            && (fn != tn && fl != tl)) {
            moveError->errtype = MoveErrorTypeMove;
            sprintf(errptr,
                    "Queen can move diagonally or vertically or "
                    "horizontally");
            return 1;
        }
        FieldNumber n = fn;
        FieldLetter l = fl;
        n = n + ((fn < tn) ? 1 : -1) * ((fn == tn) ? 0 : 1);
        l = l + ((fl < tl) ? 1 : -1) * ((fl == tl) ? 0 : 1);
        while (n != tn || l != tl) {
            if (chessboard->cells[n][l].type != FigureTypeNone) {
                moveError->errtype = MoveErrorTypeMove;
                sprintf(errptr, "Queen cant move through figures");
                return 1;
            }
            n = n + ((fn < tn) ? 1 : -1) * ((fn == tn) ? 0 : 1);
            l = l + ((fl < tl) ? 1 : -1) * ((fl == tl) ? 0 : 1);
        }
        break;
    }
    case FigureTypeKing: {
        if (move.extra != MoveExtraShortCastling
            && move.extra != MoveExtraLongCastling) {
            int n = abs((int)fn - (int)tn);
            int l = abs((int)fl - (int)tl);
            if (n > 1 || l > 1) {
                moveError->errtype = MoveErrorTypeMove;
                sprintf(errptr, "King can only move one cell");
                return 1;
            }
            if (isAttacked(move.to, chessboard, fromSide)) {
                moveError->errtype = MoveErrorTypeMove;
                sprintf(errptr, "King cant move to attacked field");
                return 1;
            }
        } else {
            FieldNumber n;
            FieldLetter l;
            n = fromSide == FigureSideWhite ? FieldNumber1 : FieldNumber8;
            l = move.extra == MoveExtraLongCastling ? FieldLetterA
                                                    : FieldLetterH;
            Figure kf = chessboard->cells[n][FieldLetterE];
            if (!(kf.type == FigureTypeKing && kf.side == fromSide)) {
                moveError->errtype = MoveErrorTypeMove;
                sprintf(errptr, "King cant be castled");
                return 1;
            }
            Figure rf = chessboard->cells[n][l];
            if (rf.type != FigureTypeRook || rf.side != fromSide) {
                moveError->errtype = MoveErrorTypeMove;
                sprintf(errptr, "No Rook for castling");
                return 1;
            }
            Field f = {FieldLetterE, n};
            if (isAttacked(f, chessboard, fromSide)) {
                moveError->errtype = MoveErrorTypeMove;
                sprintf(errptr,
                        "King cant be castled through the attacked fields");
                return 1;
            }
            int dir = move.extra == MoveExtraShortCastling ? 1 : -1;
            for (int i = 0; i <= 2; i++) {
                Field f = {.number = n, .letter = FieldLetterE + dir * i};
                if (isAttacked(f, chessboard, fromSide)) {
                    moveError->errtype = MoveErrorTypeMove;
                    sprintf(errptr,
                            "King cant be castled through the attacked "
                            "fields");
                    return 1;
                }
            }
            for (int i = FieldLetterE + dir; i != (int)l; i += dir) {
                Figure fg = chessboard->cells[n][i];
                if (fg.type != FigureTypeNone) {
                    moveError->errtype = MoveErrorTypeMove;
                    sprintf(errptr,
                            "King cant be castled through the figures ");
                    return 1;
                }
            }

            for (int i = fromSide == FigureSideBlack; i < index; i += 2) {
                Move m = moves.array[i];
                Field f = m.from;
                if (m.who == FigureTypeKing) {
                    moveError->errtype = MoveErrorTypeMove;
                    sprintf(errptr, "King cant be castled when he moved once");
                    return 1;
                }
                if (m.who == FigureTypeRook && f.letter == l && f.number == n) {
                    moveError->errtype = MoveErrorTypeMove;
                    sprintf(errptr, "King cant be castled with moved rook");
                    return 1;
                }
            }
        }
        break;
    }

    default:
        sprintf(errptr, "Unexpected error");
        return 1;
    }

    chessboard->cells[fn][fl].side = FigureSideNone;
    chessboard->cells[fn][fl].type = FigureTypeNone;
    chessboard->cells[tn][tl].side = fromSide;
    chessboard->cells[tn][tl].type = fromType;

    for (int i = 0; i < CHESSBOARD_SIZE; i++) {
        for (int j = 0; j < CHESSBOARD_SIZE; j++) {
            if (chessboard->cells[i][j].type == FigureTypeKing
                && chessboard->cells[i][j].side == fromSide) {
                Field f = {j, i};
                if (isAttacked(f, chessboard, fromSide)) {
                    moveError->errtype = MoveErrorTypeAnotherFigure;
                    sprintf(errptr, "Dont set up the King");
                    return 1;
                }
            }
        }
    }

    return 0;
}
