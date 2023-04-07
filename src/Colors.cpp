#include "Colors.h"

TileColor getTileColor(int x, int y)
{
    if ((x + y) % 2 == 1)
        return TileColor::dark;

    return TileColor::light;
}

PieceColor getPieceColor(PieceType type)
{
    PieceColor color{};
    switch (type)
    {
        case PieceType::wPawn:
        case PieceType::wKnight:
        case PieceType::wBishop:
        case PieceType::wRook:
        case PieceType::wQueen:
        case PieceType::wKing:
            color = PieceColor::white;
            break;

        case PieceType::bPawn:
        case PieceType::bKnight:
        case PieceType::bBishop:
        case PieceType::bRook:
        case PieceType::bQueen:
        case PieceType::bKing:
            color = PieceColor::black;
            break;

        // a bit weird i guess
        case PieceType::none:
            color = PieceColor::none;
    }

    return color;
}
