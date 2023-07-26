#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "DrawColor.h"

namespace constants
{
    inline constexpr int windowWidth{ 800 };
    inline constexpr int windowHeight{ 800 };
    inline constexpr int boardSize{ 8 };
    inline constexpr int screenPositionMultiplier{ 100 };

    inline constexpr int tileWidth{ windowWidth / boardSize };
    inline constexpr int tileHeight{ windowHeight / boardSize };

    inline constexpr int whitePawnStartRow{ 6 };
    inline constexpr int blackPawnStartRow{ 1 };
    inline constexpr int topRow{ 0 };
    inline constexpr int bottomRow{ 7 };
}

namespace colors
{
    inline constexpr DrawColor white{ 255, 255, 255, 255 };
    inline constexpr DrawColor lightTile{ 230, 230, 230, 255 };
    inline constexpr DrawColor darkTile{ 150, 75, 0, 255 };
}

#endif
