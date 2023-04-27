#ifndef KING_MATE_LOGIC_H
#define KING_MATE_LOGIC_H

#include "KingCheckLogic.h"

bool isKingCheckmated(const std::array<std::array<Tile, 8>, 8>& board, PieceColor kingColor);

#endif
