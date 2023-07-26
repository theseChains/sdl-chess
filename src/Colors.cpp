#include "Colors.h"

TileColor getTileColor(int x, int y)
{
    if ((x + y) % 2 == 1)
        return TileColor::dark;

    return TileColor::light;
}

void changeCurrentMoveColor(PieceColor& color)
{
    if (color == PieceColor::white)
        color = PieceColor::black;
    else
        color = PieceColor::white;
}
