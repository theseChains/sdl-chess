#ifndef KING_CHECK_LOGIC_H
#define KING_CHECK_LOGIC_H

#include "Board.h"
#include "Tile.h"

#include <array>

std::optional<std::pair<int, int>> findKingPosition(const std::array<std::array<Tile, 8>, 8>& board,
        PieceColor kingColor);

bool rookOrQueenAttacksKing(const std::array<std::array<Tile, 8>, 8>& board, int kingRow,
        int kingColumn, PieceColor kingColor);
bool isKingInCheck(const std::array<std::array<Tile, 8>, 8>& board, PieceColor kingColor);
// pass a copy of the board to see if the king will be in check after moving a piece to a new spot
bool kingWillBeInCheck(std::array<std::array<Tile, 8>, 8> board, const Piece& piece,
        int newRow, int newColumn);

#endif
