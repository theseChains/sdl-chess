#ifndef ALIASES_H
#define ALIASES_H

#include <array>
#include <tuple>

#include "Colors.h"
#include "Constants.h"
#include "PieceType.h"
#include "Tile.h"

using TileBoard =
    std::array<std::array<Tile, constants::boardSize>, constants::boardSize>;

using ColorAndType = std::pair<PieceColor, PieceType>;
using PieceArrangement =
    std::array<std::array<ColorAndType, constants::boardSize>,
               constants::boardSize>;

#endif
