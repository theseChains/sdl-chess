#include "BoardDrawer.h"

#include <stdexcept>

#include "Colors.h"
#include "Constants.h"
#include "KingCheckLogic.h"
#include "PositionConversions.h"
#include "PromotionOperations.h"

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

void BoardDrawer::drawPromotion(const Move& lastMove)
{
    PromotionPieces pieces{ initializePromotionPieces(m_textureTable,
                                                      m_tileBoard, lastMove) };

    drawPromotionPiecesRectangles(pieces);
    drawPromotionPieces(pieces);
}

void BoardDrawer::highlightKingCheck(const Tile& currentTile)
{
    if (isKingInCheck(m_tileBoard, currentTile.getPiece()->getColor()))
    {
        auto [rectangleX, rectangleY]{ convertToRectanglePosition(
            currentTile.getPosition()) };
        SDL_Rect validMoveRectangle{ rectangleX, rectangleY, 20, 20 };
        m_renderer.setDrawColor(colors::red);
        m_renderer.fillAndDrawRect(validMoveRectangle);
    }
}

void BoardDrawer::drawBoardRectangles()
{
    for (int i{ 0 }; i < constants::boardSize; ++i)
    {
        for (int j{ 0 }; j < constants::boardSize; ++j)
        {
            Tile currentTile{ m_tileBoard[i][j] };
            m_renderer.drawTile(currentTile);
            if (currentTile.isHighlighted())
            {
                auto [rectangleX, rectangleY]{ convertToRectanglePosition(
                    currentTile.getPosition()) };
                SDL_Rect validMoveRectangle{ rectangleX, rectangleY, 20, 20 };
                m_renderer.setDrawColor(colors::green);
                m_renderer.fillAndDrawRect(validMoveRectangle);
            }
            if (currentTile.getPiece() &&
                currentTile.getPiece()->getType() == PieceType::king)
            {
                highlightKingCheck(currentTile);
            }
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
                m_renderer.drawPiece(piece.value());
        }
    }
}

void BoardDrawer::drawPromotionPiecesRectangles(PromotionPieces& pieces)
{
    m_renderer.setDrawColor(colors::white);

    auto [queenRectangleRow, queenRectangleColumn]{ convertToRectanglePosition(
        pieces.queen.getPosition()) };
    auto [rookRectangleRow, rookRectangleColumn]{ convertToRectanglePosition(
        pieces.rook.getPosition()) };
    auto [bishopRectangleRow, bishopRectangleColumn]{
        convertToRectanglePosition(pieces.bishop.getPosition())
    };
    auto [knightRectangleRow, knightRectangleColumn]{
        convertToRectanglePosition(pieces.knight.getPosition())
    };
    int rectangleWidth{ constants::windowWidth / constants::boardSize };
    int rectangleHeight{ constants::windowHeight / constants::boardSize };

    m_renderer.fillAndDrawRect({ queenRectangleRow, queenRectangleColumn,
                                 rectangleWidth, rectangleHeight });
    m_renderer.fillAndDrawRect({ rookRectangleRow, rookRectangleColumn,
                                 rectangleWidth, rectangleHeight });
    m_renderer.fillAndDrawRect({ bishopRectangleRow, bishopRectangleColumn,
                                 rectangleWidth, rectangleHeight });
    m_renderer.fillAndDrawRect({ knightRectangleRow, knightRectangleColumn,
                                 rectangleWidth, rectangleHeight });
}

void BoardDrawer::drawPromotionPieces(PromotionPieces& pieces)
{
    m_renderer.drawPiece(pieces.queen);
    m_renderer.drawPiece(pieces.rook);
    m_renderer.drawPiece(pieces.bishop);
    m_renderer.drawPiece(pieces.knight);
}
