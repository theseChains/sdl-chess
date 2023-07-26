#ifndef PROMOTION_OPERATIONS_H
#define PROMOTION_OPERATIONS_H

#include <array>

#include "Aliases.h"
#include "Move.h"
#include "Renderer.h"
#include "TextureTable.h"
#include "Tile.h"

bool pawnIsPromoting(TileBoard& board, int row, int column);

void drawPromotionPieces(const TileBoard& board, TextureTable& table,
                         Renderer& renderer, const Move& lastMove);
void handlePromotedPieceSelection(Tile& pawnTile, TextureTable& textureTable,
                                  int boardRow, int pawnRow, int pawnColumn);

#endif
