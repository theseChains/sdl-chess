#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace constants
{
    inline constexpr int noEventAvailable{ 0 };
    inline constexpr int renderDriverIndex{ -1 };
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

    inline constexpr int numberOfPromotionPieces{ 4 };
    inline constexpr int promotionQueenPositionDifference{ 0 };
    inline constexpr int promotionRookPositionDifference{ 1 };
    inline constexpr int promotionBishopPositionDifference{ 2 };
    inline constexpr int promotionKnightPositionDifference{ 3 };

    inline constexpr int highlightRectangleSize{ 20 };
}

#endif
