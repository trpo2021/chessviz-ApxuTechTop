#include "figures_move.h"

int doMove(const Move move, Chessboard* chessboard)
{
    chessboard->cells[move.to.letter - 'a'][move.to.number - '1']
            = chessboard->cells[move.from.letter - 'a'][move.from.number - '1'];
    chessboard->cells[move.to.letter - 'a'][move.to.number - '1'].side
            = FigureSideNone;
    chessboard->cells[move.to.letter - 'a'][move.to.number - '1'].type
            = FigureTypeNone;
}