#include "Board.h"

#include <algorithm>
#include <iostream>

#include "Colors.h"
#include "Constants.h"
#include "PieceArrangement.h"
#include "PositionConversions.h"

Board::Board(TextureTable& table, Renderer& renderer)
    : m_lastMove{ { 0, 0 }, { 0, 0 }, PieceType::none },
      m_textureTable{ table },
      m_renderer{ renderer },
      m_positions{},
      m_boardDrawer{ table, renderer, m_tileBoard },
      m_gameLogic{ m_tileBoard, m_lastMove }
{
    for (int i{ 0 }; i < constants::boardSize; ++i)
        for (int j{ 0 }; j < constants::boardSize; ++j)
            initializeTile(m_textureTable, i, j);
}

void Board::draw()
{
    m_boardDrawer.draw();

    if (m_promotingPawn)
        m_boardDrawer.drawPromotion(m_lastMove);
}

void Board::checkForPieceSelection(SDL_Point mousePosition, bool& pieceSelected,
                                   PieceColor currentColorToMove)
{
    auto [boardRow, boardColumn]{ getBoardPositionFromMouse(mousePosition) };
    std::pair<int, int> tilePosition{ convertToScreenPosition(
        { boardRow, boardColumn }) };
    Tile& tile{ getTileReferenceByPosition(tilePosition) };
    auto piece{ tile.getPiece() };
    if (piece && piece->getColor() == currentColorToMove)
    {
        tile.getPiece()->select();
        pieceSelected = true;
        highlightValidMoves(piece.value());
    }
}

void Board::checkForPromotionPieceSelection(SDL_Point mousePosition)
{
    auto [boardRow, boardColumn]{ getBoardPositionFromMouse(mousePosition) };
    auto [pawnRow, pawnColumn]{ m_lastMove.to };
    if (boardColumn != pawnColumn || std::abs(boardRow - pawnRow) > 3)
        return;

    std::pair<int, int> pawnTilePosition{ convertToScreenPosition(
        { pawnRow, pawnColumn }) };
    Tile& pawnTile{ getTileReferenceByPosition(pawnTilePosition) };
    handlePromotedPieceSelection(pawnTile, m_textureTable, boardRow, pawnRow,
                                 pawnColumn);

    m_promotingPawn = false;
}

Tile& Board::getTileReferenceByPosition(std::pair<int, int> position)
{
    for (auto& row : m_tileBoard)
    {
        for (auto& tile : row)
        {
            if (tile.getPosition() == position)
                return tile;
        }
    }

    throw std::runtime_error{ "incorrect position for tile" };
}

void Board::placePieceAtChosenTile(int newRow, int newColumn,
                                   const std::optional<Piece>& piece)
{
    std::pair<int, int> chosenTilePosition{ convertToScreenPosition(
        { newRow, newColumn }) };
    Tile& chosenTile{ getTileReferenceByPosition(chosenTilePosition) };
    chosenTile.placePiece(piece.value());
    chosenTile.getPiece()->setPositionFromBoardPosition({ newRow, newColumn });
    chosenTile.getPiece()->deselect();
}

void Board::highlightValidMoves(const Piece& piece)
{
    for (int i{ 0 }; i < constants::boardSize; ++i)
        for (int j{ 0 }; j < constants::boardSize; ++j)
            if (m_gameLogic.playerMoveIsValid(piece, i, j))
                m_tileBoard[i][j].highlight();
}

void Board::resetMoveHighlight()
{
    for (auto& row : m_tileBoard)
        for (auto& tile : row)
            tile.dehighlight();
}

bool Board::checkBoardTile(Tile& tile, int newRow, int newColumn,
                           bool& pieceSelected, PieceColor& currentColorToMove)
{
    auto piece{ tile.getPiece() };
    if (!piece || !piece->isSelected())
        return true;

    if (m_gameLogic.playerMoveIsValid(piece.value(), newRow, newColumn))
    {
        auto [oldRow, oldColumn]{ piece->getBoardPosition() };
        m_lastMove = { { oldRow, oldColumn },
                       { newRow, newColumn },
                       piece->getType() };

        m_gameLogic.checkForEnPassantCapture(piece.value(), newRow, newColumn,
                                             oldRow, oldColumn);
        m_gameLogic.updateFiftyMoveCounter(piece.value(), newRow, newColumn,
                                           oldRow, oldColumn);

        tile.removePiece();
        m_tileBoard[newRow][newColumn].removePiece();
        placePieceAtChosenTile(newRow, newColumn, piece);

        m_gameLogic.checkForCastling(piece.value(), newRow, newColumn,
                                     oldColumn);
        if (m_gameLogic.playerPromotingPawn(piece.value(), newRow, newColumn))
            m_promotingPawn = true;

        pieceSelected = false;
        changeCurrentMoveColor(currentColorToMove);
        m_positions.push_back(m_tileBoard);
        m_gameLogic.updatePieceProperties(newRow, newColumn);
        currentColorToMove =
            m_gameLogic.checkForGameEnd(m_positions, currentColorToMove);
    }
    else
    {
        tile.getPiece()->deselect();
        pieceSelected = false;
    }

    resetMoveHighlight();

    return false;
}

void Board::checkForPieceMovement(SDL_Point mousePosition, bool& pieceSelected,
                                  PieceColor& currentColorToMove)
{
    if (currentColorToMove == PieceColor::noColor)
        return;

    auto [newRow, newColumn]{ getBoardPositionFromMouse(mousePosition) };

    for (auto& row : m_tileBoard)
    {
        for (auto& tile : row)
        {
            if (!checkBoardTile(tile, newRow, newColumn, pieceSelected,
                                currentColorToMove))
            {
                return;
            }
        }
    }
}

TileBoard& Board::getTiles()
{
    return m_tileBoard;
}

bool Board::promotingPawn() const
{
    return m_promotingPawn;
}

void Board::initializeTile(TextureTable& table, int i, int j)
{
    auto [color, type]{ config::arrangement[i][j] };
    TileColor tileColor{ getTileColor(i, j) };
    auto [tileRow, tileColumn]{ convertToScreenPosition({ i, j }) };

    if (type == PieceType::none)
        m_tileBoard[i][j] = { tileColor,
                              std::nullopt,
                              { tileRow, tileColumn } };
    else
    {
        Piece piece{
            type, color, table[{ color, type }], { tileRow, tileColumn }
        };
        m_tileBoard[i][j] = { tileColor, piece, { tileRow, tileColumn } };
    }
}
