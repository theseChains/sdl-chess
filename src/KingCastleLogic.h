#ifndef KING_CASTLE_LOGIC_H
#define KING_CASTLE_LOGIC_H

#include <array>

#include "Tile.h"
#include "Colors.h"

bool kingCanCastle(const std::array<std::array<Tile, 8>, 8>& board,
        int kingRow, int kingColumn, int newRow, int newColumn, PieceColor kingColor);

void moveRookForCastling(std::array<std::array<Tile, 8>, 8>& board, int kingRow,
        int newKingColumn);

#endif
