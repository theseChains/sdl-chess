#include "Board.h"
#include "PieceArrangement.h"

Board::Board(TextureTable& table)
{
    for (int i{ 0 }; i < 8; ++i)
    {
        for (int j{ 0 }; j < 8; ++j)
        {
            PieceType type{ config::arrangement[j][i] };
            Piece piece{ type, table[type], { i * 100, j * 100 } };
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

            auto piece{ m_board[i][j].getPiece() };
            if (piece)
                piece.value().draw(renderer);
        }
    }
}
