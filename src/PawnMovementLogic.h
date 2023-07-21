#ifndef PAWN_MOVEMENT_LOGIC_H
#define PAWN_MOVEMENT_LOGIC_H

#include <array>

#include "Colors.h"
#include "Move.h"
#include "Tile.h"

bool whitePawnMoveIsValid(const std::array<std::array<Tile, 8>, 8>& board,
        int pawnRow, int pawnColumn, int newRow, int newColumn);
bool blackPawnMoveIsValid(const std::array<std::array<Tile, 8>, 8>& board,
        int pawnRow, int pawnColumn, int newRow, int newColumn);
bool canTakeEnPassant(std::array<std::array<Tile, 8>, 8>& board,
        const Piece& piece, int newRow, int newColumn, const Move& lastMove);

#endif
