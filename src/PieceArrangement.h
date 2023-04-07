#ifndef PIECE_ARRANGEMENT_H
#define PIECE_ARRANGEMENT_H

#include "PieceType.h"

#include <array>

namespace config
{
    using enum PieceType;
    inline constexpr std::array<std::array<PieceType, 8>, 8> arrangement{ {
        { { rook, knight, bishop, queen, king, bishop, knight, rook } },
        { { pawn, pawn, pawn, pawn, pawn, pawn, pawn, pawn } },
        { { none, none, none, none, none, none, none, none } },
        { { none, none, none, none, none, none, none, none } },
        { { none, none, none, none, none, none, none, none } },
        { { none, none, none, none, none, none, none, none } },
        { { pawn, pawn, pawn, pawn, pawn, pawn, pawn, pawn } },
        { { rook, knight, bishop, queen, king, bishop, knight, rook } }
    } };
}

#endif
