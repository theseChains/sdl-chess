#include "BoardDrawer.h"

#include "Constants.h"

BoardDrawer::BoardDrawer(TextureTable& textureTable, Renderer& renderer,
                         TileBoard& tileBoard)
    : m_textureTable{ textureTable },
      m_renderer{ renderer },
      m_tileBoard{ tileBoard }
{
}

void BoardDrawer::draw()
{
    drawBoardRectangles();
    drawPieces();
}

void BoardDrawer::drawBoardRectangles()
{
    for (int i{ 0 }; i < constants::boardSize; ++i)
    {
        for (int j{ 0 }; j < constants::boardSize; ++j)
        {
            m_renderer.setDrawColor(m_tileBoard[i][j].getConvertedColor());
            m_renderer.fillAndDrawRect(m_tileBoard[i][j].getRectangle());
        }
    }
}

void BoardDrawer::drawPieces()
{
    for (int i{ 0 }; i < constants::boardSize; ++i)
    {
        for (int j{ 0 }; j < constants::boardSize; ++j)
        {
            auto piece{ m_tileBoard[i][j].getPiece() };
            if (piece)
                piece.value().draw(m_renderer);
        }
    }
}
