#include "Board.h"

#include "Colors.h"
#include "KingCheckLogic.h"
#include "MoveValidator.h"
#include "PieceArrangement.h"

#include <iostream>

Board::Board(TextureTable& table)
{
    for (int i{ 0 }; i < 8; ++i)
        for (int j{ 0 }; j < 8; ++j)
            initializeTile(table, i, j);
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

void changeCurrentMoveColor(PieceColor& color)
{
    if (color == PieceColor::white)
        color = PieceColor::black;
    else
        color = PieceColor::white;
}

void Board::checkForPieceSelection(SDL_Point mousePosition, bool& pieceSelected,
        PieceColor currentColorToMove)
{
    for (auto& row : m_board)
    {
        for (auto& tile : row)
        {
            auto piece{ tile.getPiece() };
            if (piece && SDL_PointInRect(&mousePosition, &piece->getRectangle()) &&
                    piece->getColor() == currentColorToMove)
            {
                tile.getPiece()->select();
                pieceSelected = true;
                return;
            }
        }
    }
}

std::pair<int, int> getSnappedBoardPosition(SDL_Point mousePosition)
{
    // exception if user clicks on [0, y] or [x, 0] but whatever
    return { mousePosition.x / 100 * 100, mousePosition.y / 100 * 100 };
}

std::optional<std::reference_wrapper<Tile>> Board::findTile(std::pair<int, int> position)
{
    for (auto& row : m_board)
    {
        for (auto& tile : row)
        {
            if (tile.getPosition() == position)
                return tile;
        }
    }

    return std::nullopt;
}

void Board::checkForPieceMovement(SDL_Point mousePosition, bool& pieceSelected,
        PieceColor& currentColorToMove)
{
    for (auto& row : m_board)
    {
        for (auto& tile : row)
        {
            auto piece{ tile.getPiece() };
            auto newPosition{ getSnappedBoardPosition(mousePosition) };
            auto [newColumn, newRow]{ std::make_pair(newPosition.first / 100,
                    newPosition.second / 100) };

            if (piece && piece->isSelected() &&
                    MoveValidator::moveIsValid(m_board, piece.value(), newRow, newColumn) &&
                    !kingWillBeInCheck(m_board, piece.value(), newRow, newColumn))
            {
                // remove piece from old tile
                tile.removePiece();
                // remove piece from new tile (in case of capturing)
                m_board[newRow][newColumn].removePiece();
                // place piece at a chosen tile
                auto chosenTile{ findTile(newPosition) };
                chosenTile->get().placePiece(piece.value());
                chosenTile->get().getPiece()->setPosition(newPosition);
                chosenTile->get().getPiece()->deselect();
                pieceSelected = false;
                changeCurrentMoveColor(currentColorToMove);
                return;
            }
            else if (piece && piece->isSelected())
            {
                tile.getPiece()->deselect();
                pieceSelected = false;
                return;
            }
        }
    }
}

std::array<std::array<Tile, 8>, 8>& Board::getTiles()
{
    return m_board;
}

void Board::initializeTile(TextureTable& table, int i, int j)
{
    auto [color, type]{ config::arrangement[i][j] };
    if (type == PieceType::none)
        m_board[i][j] = { getTileColor(i, j), std::nullopt, { j * 100, i * 100 } };
    else
    {
        Piece piece{ type, color, table[{ color, type }], { j * 100, i * 100 } };
        m_board[i][j] = { getTileColor(i, j), piece, { j * 100, i * 100 } };
    }
}
