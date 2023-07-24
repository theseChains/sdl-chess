#ifndef KING_MATE_LOGIC_H
#define KING_MATE_LOGIC_H

#include "KingCheckLogic.h"

bool kingHasLegalMoves(const std::array<std::array<Tile, 8>, 8>& board, const Piece& king,
        int currentRow, int currentColumn);
bool playerHasLegalMoves(const std::array<std::array<Tile, 8>, 8>& board, PieceColor color);
bool isKingCheckmated(const std::array<std::array<Tile, 8>, 8>& board, PieceColor kingColor);

#endif
