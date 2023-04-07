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
    none
};

TileColor getTileColor(int x, int y);
PieceColor getPieceColor(PieceType type);

#endif
