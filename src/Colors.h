#ifndef COLORS_H
#define COLORS_H

#include "PieceType.h"

enum class TileColor
{
    light,
    dark
};

enum class PieceColor
{
    white,
    black,
    noColor
};

TileColor getTileColor(int x, int y);
void changeCurrentMoveColor(PieceColor& color);

#endif
