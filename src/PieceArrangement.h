#ifndef PIECE_ARRANGEMENT_H
#define PIECE_ARRANGEMENT_H

#include "Colors.h"
#include "PieceType.h"

#include <array>

namespace config
{
    using enum PieceType;
    using enum PieceColor;

    static constexpr std::pair<PieceColor, PieceType> bRook{ black, rook };
    static constexpr std::pair<PieceColor, PieceType> bKnight{ black, knight };
    static constexpr std::pair<PieceColor, PieceType> bBishop{ black, bishop };
    static constexpr std::pair<PieceColor, PieceType> bQueen{ black, queen };
    static constexpr std::pair<PieceColor, PieceType> bKing{ black, king };
    static constexpr std::pair<PieceColor, PieceType> bPawn{ black, pawn };
    static constexpr std::pair<PieceColor, PieceType> wRook{ white, rook };
    static constexpr std::pair<PieceColor, PieceType> wKnight{ white, knight };
    static constexpr std::pair<PieceColor, PieceType> wBishop{ white, bishop };
    static constexpr std::pair<PieceColor, PieceType> wQueen{ white, queen };
    static constexpr std::pair<PieceColor, PieceType> wKing{ white, king };
    static constexpr std::pair<PieceColor, PieceType> wPawn{ white, pawn };
    static constexpr std::pair<PieceColor, PieceType> noPiece{ noColor, none };

    inline constexpr std::array<std::array<std::pair<PieceColor, PieceType>, 8>, 8> arrangement{ {
        { { bRook, bKnight, bBishop, bQueen, bKing, bBishop, bKnight, bRook } },
        { { bPawn, bPawn, bPawn, bPawn, bPawn, bPawn, bPawn, bPawn} },
        { { noPiece, noPiece, noPiece, noPiece, noPiece, noPiece, noPiece, noPiece} },
        { { noPiece, noPiece, noPiece, noPiece, noPiece, noPiece, noPiece, noPiece} },
        { { noPiece, noPiece, noPiece, noPiece, noPiece, noPiece, noPiece, noPiece} },
        { { noPiece, noPiece, noPiece, noPiece, noPiece, noPiece, noPiece, noPiece} },
        { { wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn} },
        { { wRook, wKnight, wBishop, wQueen, wKing, wBishop, wKnight, wRook } }
    } };
}

#endif
