#ifndef PIECE_ARRANGEMENT_H
#define PIECE_ARRANGEMENT_H

#include "PieceType.h"

#include <array>

namespace config
{
    using enum PieceType;
    inline constexpr std::array<std::array<PieceType, 8>, 8> arrangement{ {
        { { bRook, bKnight, bBishop, bQueen, bKing, bBishop, bKnight, bRook } },
        { { bPawn, bPawn, bPawn, bPawn, bPawn, bPawn, bPawn, bPawn } },
        { { none, none, none, none, none, none, none, none } },
        { { none, none, none, none, none, none, none, none } },
        { { none, none, none, none, none, none, none, none } },
        { { none, none, none, none, none, none, none, none } },
        { { wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn} },
        { { wRook, wKnight, wBishop, wQueen, wKing, wBishop, wKnight, wRook } }
    } };
}

#endif
