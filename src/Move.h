#ifndef MOVE_H
#define MOVE_H

#include <tuple>

#include "PieceType.h"

struct Move
{
    std::pair<int, int> from{};
    std::pair<int, int> to{};
    PieceType pieceType{};
};

#endif
