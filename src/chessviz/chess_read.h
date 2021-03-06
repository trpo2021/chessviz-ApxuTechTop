#pragma once

#include <figures_move.h>

int parseMove(
        const char* string, const char** endstr, Move* move, char* errstr);

int parseStep(const char* string, Moves* moves, char* errstr);
