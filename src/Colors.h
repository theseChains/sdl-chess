#ifndef COLORS_H
#define COLORS_H

#include "DrawColor.h"
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

namespace colors
{
    inline constexpr DrawColor white{ 255, 255, 255, 255 };
    inline constexpr DrawColor green{ 50, 205, 50, 255 };
    inline constexpr DrawColor red{ 220, 20, 60, 255 };

    inline constexpr DrawColor lightTile{ 211, 211, 211, 255 };
    inline constexpr DrawColor darkTile{ 105, 105, 105, 255 };
}

TileColor getTileColor(int x, int y);
void changeCurrentMoveColor(PieceColor& color);

#endif
