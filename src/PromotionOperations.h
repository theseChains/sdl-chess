#ifndef PROMOTION_OPERATIONS_H
#define PROMOTION_OPERATIONS_H

#include <array>

#include "Aliases.h"
#include "Move.h"
#include "TextureTable.h"
#include "Tile.h"

struct PromotionPieces
{
    Piece queen;
    Piece rook;
    Piece bishop;
    Piece knight;
};

PromotionPieces initializePromotionPieces(TextureTable& textureTable,
                                          TileBoard& tileBoard,
                                          const Move& lastMove);
int getPromotionPieceScreenRow(int tileRow, PieceType type, PieceColor color);

bool pawnIsPromoting(TileBoard& board, int row, int column);
void handlePromotedPieceSelection(Tile& pawnTile, TextureTable& textureTable,
                                  int boardRow, int pawnRow, int pawnColumn);

#endif
