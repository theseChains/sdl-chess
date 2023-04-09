#ifndef MOVE_VALIDATOR_H
#define MOVE_VALIDATOR_H

#include "Tile.h"

#include <array>

class MoveValidator
{
public:
    static bool moveIsValid(std::array<std::array<Tile, 8>, 8>& board, const Piece& piece,
            std::pair<int, int> newPosition);

private:
    static bool whitePawnMoveIsValid(std::array<std::array<Tile, 8>, 8>& board,
            std::pair<int, int> piecePosition, std::pair<int, int> newPosition);
};

#endif
