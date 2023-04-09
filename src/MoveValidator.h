#ifndef MOVE_VALIDATOR_H
#define MOVE_VALIDATOR_H

#include "Colors.h"
#include "Tile.h"

#include <array>

class MoveValidator
{
public:
    static bool moveIsValid(std::array<std::array<Tile, 8>, 8>& board, const Piece& piece,
            std::pair<int, int> newPosition);

private:
    static bool whitePawnMoveIsValid(std::array<std::array<Tile, 8>, 8>& board,
            int pawnRow, int pawnColumn, int newRow, int newColumn);
    static bool blackPawnMoveIsValid(std::array<std::array<Tile, 8>, 8>& board,
            int pawnRow, int pawnColumn, int newRow, int newColumn);
    static bool knightMoveIsValid(std::array<std::array<Tile, 8>, 8>& board,
            int knightRow, int knightColumn, int newRow, int newColumn, PieceColor knightColor);
    static bool bishopMoveIsValid(std::array<std::array<Tile, 8>, 8>& board,
            int bishopRow, int bishopColumn, int newRow, int newColumn, PieceColor bishopColor);
    static bool rookMoveIsValid(std::array<std::array<Tile, 8>, 8>& board,
            int rookRow, int rookColumn, int newRow, int newColumn, PieceColor rookColor);
    static bool kingMoveIsValid(std::array<std::array<Tile, 8>, 8>& board,
            int kingRow, int kingColumn, int newRow, int newColumn, PieceColor kingColor);
};

#endif
