#ifndef BOARD_DRAWER_H
#define BOARD_DRAWER_H

#include "Aliases.h"
#include "Renderer.h"
#include "TextureTable.h"

class BoardDrawer
{
public:
    BoardDrawer(TextureTable& textureTable, Renderer& renderer,
                TileBoard& board);

    void draw();

private:
    TextureTable& m_textureTable;
    Renderer& m_renderer;
    TileBoard& m_tileBoard;

    void drawBoardRectangles();
    void drawPieces();
};

#endif
