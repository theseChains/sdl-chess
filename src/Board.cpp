#include "Board.h"

#include "Colors.h"
#include "KingCastleLogic.h"
#include "KingCheckLogic.h"
#include "KingMateLogic.h"
#include "MoveValidator.h"
#include "PawnMovementLogic.h"
#include "PieceArrangement.h"

#include <iostream>

Board::Board(TextureTable& table)
    : m_lastMove{ { 0, 0 }, { 0, 0 }, PieceType::none }
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

std::pair<int, int> getBoardPositionFromMouse(SDL_Point mousePosition)
{
    // in case user clicks on the edge of the screen
    if (mousePosition.x == 0)
        mousePosition.x = 1;
    if (mousePosition.y == 0)
        mousePosition.y = 1;

    return { mousePosition.y / 100, mousePosition.x / 100 };
}

void Board::checkForPieceSelection(SDL_Point mousePosition, bool& pieceSelected,
        PieceColor currentColorToMove)
{
    auto [boardRow, boardColumn]{ getBoardPositionFromMouse(mousePosition) };
    auto tile{ findTile({ boardRow * 100, boardColumn * 100 }) };
    auto piece{ tile->get().getPiece() };
    if (piece && piece->getColor() == currentColorToMove)
    {
        tile->get().getPiece()->select();
        pieceSelected = true;
    }
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

void Board::placePieceAtChosenTile(int newRow, int newColumn, const std::optional<Piece>& piece)
{
    auto chosenTile{ findTile({ newRow * 100, newColumn * 100 }) };
    chosenTile->get().placePiece(piece.value());
    chosenTile->get().getPiece()->setBoardPosition({ newRow, newColumn });
    chosenTile->get().getPiece()->deselect();
}

void Board::checkBoardTile(Tile& tile, bool& keepGoing, int newRow, int newColumn,
        bool& pieceSelected, PieceColor& currentColorToMove)
{
    auto piece{ tile.getPiece() };

    if (piece && piece->isSelected() &&
        (MoveValidator::moveIsValid(m_board, piece.value(), newRow, newColumn) ||
         canTakeEnPassant(m_board, piece.value(), newRow, newColumn, m_lastMove)) &&
        !kingWillBeInCheck(m_board, piece.value(), newRow, newColumn))
    {
        auto [oldRow, oldColumn]{ piece->getBoardPosition() };
        m_lastMove = { { oldRow, oldColumn }, { newRow, newColumn }, piece->getType() };

        tile.removePiece();
        m_board[newRow][newColumn].removePiece();
        placePieceAtChosenTile(newRow, newColumn, piece);
        if (piece->getType() == PieceType::king && std::abs(oldColumn - newColumn) == 2)
            moveRookForCastling(m_board, newRow, newColumn);

        pieceSelected = false;

        Piece& pieceReference{ m_board[newRow][newColumn].getPiece().value() };
        pieceReference.setHasMoved();

        changeCurrentMoveColor(currentColorToMove);
        if (isKingCheckmated(m_board, currentColorToMove))
        {
            if (currentColorToMove == PieceColor::white)
                std::cout << "white king is checkmated, black wins!\n";
            else
                std::cout << "black king is checkmated, white wins!\n";

            currentColorToMove = PieceColor::noColor;
        }

        keepGoing = false;
    }
    else if (piece && piece->isSelected())
    {
        tile.getPiece()->deselect();
        pieceSelected = false;
        keepGoing = false;
    }
}

void Board::checkForPieceMovement(SDL_Point mousePosition, bool& pieceSelected,
        PieceColor& currentColorToMove)
{
    if (currentColorToMove == PieceColor::noColor)
        return;

    auto [newRow, newColumn]{ getBoardPositionFromMouse(mousePosition) };

    for (auto& row : m_board)
    {
        for (auto& tile : row)
        {
            // bit of a hack i guess..
            bool keepGoing = true;
            checkBoardTile(tile, keepGoing, newRow, newColumn, pieceSelected, currentColorToMove);
            if (!keepGoing)
                return;
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
    TileColor tileColor{ getTileColor(i, j) };
    auto [tileRow, tileColumn]{ std::make_pair(i * 100, j * 100) };

    if (type == PieceType::none)
        m_board[i][j] = { tileColor, std::nullopt, { tileRow, tileColumn } };
    else
    {
        Piece piece{ type, color, table[{ color, type }], { tileRow, tileColumn } };
        m_board[i][j] = { tileColor, piece, { tileRow, tileColumn } };
    }
}
