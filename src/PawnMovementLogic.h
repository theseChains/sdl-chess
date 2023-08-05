#ifndef PAWN_MOVEMENT_LOGIC_H
#define PAWN_MOVEMENT_LOGIC_H

#include <array>

#include "Aliases.h"
#include "Colors.h"
#include "Move.h"
#include "Tile.h"

bool whitePawnMoveIsValid(const TileBoard& board, int pawnRow, int pawnColumn,
                          int newRow, int newColumn);
bool blackPawnMoveIsValid(const TileBoard& board, int pawnRow, int pawnColumn,
                          int newRow, int newColumn);
bool canTakeEnPassant(TileBoard& board, const Piece& piece, int newRow,
                      int newColumn, const Move& lastMove,
                      bool shouldTakePiece);

#endif
