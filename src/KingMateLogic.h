#ifndef KING_MATE_LOGIC_H
#define KING_MATE_LOGIC_H

#include "KingCheckLogic.h"

bool kingHasLegalMoves(const TileBoard& board, const Piece& king,
                       int currentRow, int currentColumn);
bool playerHasLegalMoves(const TileBoard& board, PieceColor color);
bool isKingCheckmated(const TileBoard& board, PieceColor kingColor);

#endif
