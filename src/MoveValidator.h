#ifndef MOVE_VALIDATOR_H
#define MOVE_VALIDATOR_H

#include "Tile.h"

#include <array>

class MoveValidator
{
public:
    // weird default constructor once again
    MoveValidator() = default;
    MoveValidator(const std::array<std::array<Tile, 8>, 8>& board);

    bool moveIsValid(const Piece& piece, std::pair<int, int> newPosition);

private:
    std::array<std::array<Tile, 8>, 8> m_board;

    bool whitePawnMoveIsValid(std::pair<int, int> piecePosition, std::pair<int, int> newPosition);
};

#endif
