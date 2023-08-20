#ifndef KING_CHECK_LOGIC_H
#define KING_CHECK_LOGIC_H

#include <array>

#include "Aliases.h"
#include "Board.h"
#include "Tile.h"

std::pair<int, int> findKingPosition(const TileBoard& board,
                                     PieceColor kingColor);

bool isKingInCheck(const TileBoard& board, PieceColor kingColor);
// pass a copy of the board to see if the king will be in check after moving a
// piece to a new spot
bool kingWillBeInCheck(TileBoard board, const Piece& piece, int newRow,
                       int newColumn);

#endif
