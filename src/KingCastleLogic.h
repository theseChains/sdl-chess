#ifndef KING_CASTLE_LOGIC_H
#define KING_CASTLE_LOGIC_H

#include <array>

#include "Aliases.h"
#include "Colors.h"
#include "Tile.h"

bool kingCanCastle(const TileBoard& board, int kingRow, int kingColumn,
                   int newRow, int newColumn, PieceColor kingColor);

void moveRookForCastling(TileBoard& board, int kingRow, int newKingColumn);

#endif
