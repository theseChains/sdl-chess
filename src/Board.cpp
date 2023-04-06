#include "Board.h"

Board::Board(Renderer& renderer)
{
    SDL_Texture* texture{ renderer.loadTexture("../res/pawn.png") };
    for (int i{ 0 }; i < 8; ++i)
    {
        for (int j{ 0 }; j < 8; ++j)
        {
            Piece piece{ PieceType::pawn, texture, { i * 100, j * 100 } };
            m_board[i][j] = { getTileColor(i, j), piece, { i * 100, j * 100 } };
        }
    }
}

void Board::draw(Renderer& renderer)
{
    for (int i{ 0 }; i < 8; ++i)
    {
        for (int j{ 0 }; j < 8; ++j)
        {
            renderer.setDrawColor(m_board[i][j].getConvertedColor());
            renderer.fillAndDrawRect(m_board[i][j].getRectangle());
            m_board[i][j].getPiece().value().draw(renderer);
        }
    }
}
