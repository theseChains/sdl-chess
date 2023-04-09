#include "Board.h"

#include "Colors.h"
#include "PieceArrangement.h"

#include <stdexcept>
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

void Board::checkForPieceSelection(SDL_Point mousePosition, bool& pieceSelected)
{
    for (auto& row : m_board)
    {
        for (auto& tile : row)
        {
            auto piece{ tile.getPiece() };
            if (piece && SDL_PointInRect(&mousePosition, &piece->getRectangle()))
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

bool whitePawnMoveIsValid(std::pair<int, int> piecePos, SDL_Point mousePosition)
{
    auto [mouseRow, mouseColumn]{ std::make_pair(mousePosition.x, mousePosition.y) };
    auto [pieceRow, pieceColumn]{ std::make_pair(piecePos.first / 100, piecePos.second / 100) };

    // wip
    return true;
}

bool moveIsValid(const Piece& piece, SDL_Point mousePosition)
{
    auto piecePosition{ piece.getPosition() };
    PieceType type{ piece.getType() };
    switch (type)
    {
        case PieceType::wPawn:
            return whitePawnMoveIsValid(piecePosition, mousePosition);
        case PieceType::bPawn:
        case PieceType::bKnight:
        case PieceType::wKnight:
        case PieceType::bBishop:
        case PieceType::wBishop:
        case PieceType::bRook:
        case PieceType::wRook:
        case PieceType::bQueen:
        case PieceType::wQueen:
        case PieceType::bKing:
        case PieceType::wKing:
            return true;
        case PieceType::none:
            throw std::runtime_error{ "moveIsValid(): piece type none should not be checked" };
    }

    return true;
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

void Board::checkForPieceMovement(SDL_Point mousePosition, bool& pieceSelected)
{
    for (auto& row : m_board)
    {
        for (auto& tile : row)
        {
            auto piece{ tile.getPiece() };
            if (piece && piece->isSelected() && moveIsValid(piece.value(), mousePosition))
            {
                auto newPosition{ getSnappedBoardPosition(mousePosition) };
                // remove piece from old tile
                tile.removePiece();
                // place piece at a chosen tile
                auto chosenTile{ findTile(newPosition) };
                chosenTile->get().placePiece(piece.value());
                chosenTile->get().getPiece()->setPosition(newPosition);
                chosenTile->get().getPiece()->deselect();
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
