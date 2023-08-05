#ifndef BOARD_DRAWER_H
#define BOARD_DRAWER_H

#include <array>

#include "Aliases.h"
#include "Constants.h"
#include "Move.h"
#include "PieceType.h"
#include "PromotionOperations.h"
#include "Renderer.h"
#include "TextureTable.h"

class BoardDrawer
{
public:
    BoardDrawer(TextureTable& textureTable, Renderer& renderer,
                TileBoard& board);

    void draw();
    void drawPromotion(const Move& lastMove);

private:
    TextureTable& m_textureTable;
    Renderer& m_renderer;
    TileBoard& m_tileBoard;

    void drawBoardRectangles();
    void drawPieces();

    void drawPromotionPiecesRectangles(PromotionPieces& pieces);
    void drawPromotionPieces(PromotionPieces& pieces);
};

#endif
