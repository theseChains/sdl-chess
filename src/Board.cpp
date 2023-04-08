#include "Board.h"

#include "Colors.h"
#include "PieceArrangement.h"

#include <iostream>

Board::Board(TextureTable& table)
{
    for (int i{ 0 }; i < 8; ++i)
    {
        for (int j{ 0 }; j < 8; ++j)
        {
            initializeTile(table, i, j);
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
        }
    }

    // render pieces on top of the board
    for (int i{ 0 }; i < 8; ++i)
    {
        for (int j{ 0 }; j < 8; ++j)
        {
            auto piece{ m_board[i][j].getPiece() };
            if (piece)
                piece.value().draw(renderer);
        }
    }
}

void Board::checkForPieceSelection(SDL_Point mousePosition, bool& pieceSelected)
{
    for (auto& row : m_board)
    {
        for (auto& tile : row)
        {
            auto piece{ tile.getPiece() };
            if (piece && SDL_PointInRect(&mousePosition, &tile.getPiece()->getRectangle()))
            {
                std::cout << "selected a piece\n";
                tile.getPiece()->select();
                pieceSelected = true;
            }
        }
    }
}

void Board::checkForPieceMovement(SDL_Point mousePosition, bool& pieceSelected)
{
    for (auto& row : m_board)
    {
        for (auto& tile : row)
        {
            auto piece{ tile.getPiece() };
            if (piece && piece->isSelected())
            {
                std::cout << "changing position\n";
                tile.getPiece()->setPosition({ mousePosition.x, mousePosition.y });
                tile.getPiece()->deselect();
            }
        }
    }

    pieceSelected = false;
}

std::array<std::array<Tile, 8>, 8>& Board::getTiles()
{
    return m_board;
}

void Board::initializeTile(TextureTable& table, int i, int j)
{
    PieceType type{ config::arrangement[j][i] };
    if (type == PieceType::none)
        m_board[i][j] = { getTileColor(i, j), std::nullopt, { i * 100, j * 100 } };
    else
    {
        PieceColor color{ getPieceColor(type) };
        Piece piece{ type, color, table[{ color, type }], { i * 100, j * 100 } };
        m_board[i][j] = { getTileColor(i, j), piece, { i * 100, j * 100 } };
    }
}
