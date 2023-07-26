#ifndef MOVE_VALIDATOR_H
#define MOVE_VALIDATOR_H

#include <array>

#include "Aliases.h"
#include "Colors.h"
#include "Tile.h"

class MoveValidator
{
public:
    static bool moveIsValid(const TileBoard& board, const Piece& piece,
                            int newRow, int newColumn);

private:
    static bool pawnMoveIsValid(const TileBoard& board, int pawnRow,
                                int pawnColumn, int newRow, int newColumn,
                                PieceColor color);
    static bool knightMoveIsValid(const TileBoard& board, int knightRow,
                                  int knightColumn, int newRow, int newColumn,
                                  PieceColor knightColor);
    static bool bishopMoveIsValid(const TileBoard& board, int bishopRow,
                                  int bishopColumn, int newRow, int newColumn,
                                  PieceColor bishopColor);
    static bool rookMoveIsValid(const TileBoard& board, int rookRow,
                                int rookColumn, int newRow, int newColumn,
                                PieceColor rookColor);
    static bool kingMoveIsValid(const TileBoard& board, int kingRow,
                                int kingColumn, int newRow, int newColumn,
                                PieceColor kingColor);
};

#endif
