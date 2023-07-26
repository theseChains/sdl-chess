#ifndef CONSTANTS_H
#define CONSTANTS_H

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

#endif
