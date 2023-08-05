#include "Board.h"

#include <algorithm>
#include <iostream>

#include "Colors.h"
#include "Constants.h"
#include "KingCastleLogic.h"
#include "KingCheckLogic.h"
#include "KingMateLogic.h"
#include "MoveValidator.h"
#include "PawnMovementLogic.h"
#include "PieceArrangement.h"
#include "PositionConversions.h"
#include "PromotionOperations.h"

Board::Board(TextureTable& table, Renderer& renderer)
    : m_lastMove{ { 0, 0 }, { 0, 0 }, PieceType::none },
      m_textureTable{ table },
      m_renderer{ renderer },
      m_positions{},
      m_boardDrawer{ table, renderer, m_tileBoard }
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
    {
        for (int j{ 0 }; j < constants::boardSize; ++j)
        {
            if ((MoveValidator::moveIsValid(m_tileBoard, piece, i, j) ||
                 canTakeEnPassant(m_tileBoard, piece, i, j, m_lastMove,
                                  false)) &&
                !kingWillBeInCheck(m_tileBoard, piece, i, j))
            {
                m_tileBoard[i][j].highlight();
            }
        }
    }
}

void Board::resetMoveHighlight()
{
    for (auto& row : m_tileBoard)
        for (auto& tile : row)
            tile.dehighlight();
}

void Board::checkBoardTile(Tile& tile, bool& keepGoing, int newRow,
                           int newColumn, bool& pieceSelected,
                           PieceColor& currentColorToMove)
{
    auto piece{ tile.getPiece() };
    if (!piece || !piece->isSelected())
        return;

    // could add something like if (!piece || !pieceIsSelected) return;

    if ((MoveValidator::moveIsValid(m_tileBoard, piece.value(), newRow,
                                    newColumn) ||
         canTakeEnPassant(m_tileBoard, piece.value(), newRow, newColumn,
                          m_lastMove, true)) &&
        !kingWillBeInCheck(m_tileBoard, piece.value(), newRow, newColumn))
    {
        auto [oldRow, oldColumn]{ piece->getBoardPosition() };
        m_lastMove = { { oldRow, oldColumn },
                       { newRow, newColumn },
                       piece->getType() };

        tile.removePiece();
        m_tileBoard[newRow][newColumn].removePiece();
        placePieceAtChosenTile(newRow, newColumn, piece);
        if (piece->getType() == PieceType::king &&
            std::abs(oldColumn - newColumn) == 2)
            moveRookForCastling(m_tileBoard, newRow, newColumn);

        if (piece->getType() == PieceType::pawn &&
            pawnIsPromoting(m_tileBoard, newRow, newColumn))
            m_promotingPawn = true;

        pieceSelected = false;

        Piece& pieceReference{
            m_tileBoard[newRow][newColumn].getPiece().value()
        };
        pieceReference.setHasMoved();

        changeCurrentMoveColor(currentColorToMove);
        // change this stuff to checkForGameEnd() or something
        if (isKingCheckmated(m_tileBoard, currentColorToMove))
        {
            if (currentColorToMove == PieceColor::white)
                std::cout << "white king is checkmated, black wins!\n";
            else
                std::cout << "black king is checkmated, white wins!\n";

            currentColorToMove = PieceColor::noColor;
        }

        if (!isKingInCheck(m_tileBoard, currentColorToMove) &&
            !playerHasLegalMoves(m_tileBoard, currentColorToMove))
        {
            std::cout << "draw by stalemate\n";
            currentColorToMove = PieceColor::noColor;
        }

        m_positions.push_back(m_tileBoard);
        if (std::count(m_positions.begin(), m_positions.end(), m_tileBoard) >=
            3)
        {
            std::cout << "draw by three-fold repetition\n";
            currentColorToMove = PieceColor::noColor;
        }
        keepGoing = false;
    }
    else
    {
        tile.getPiece()->deselect();
        pieceSelected = false;
        keepGoing = false;
    }
    resetMoveHighlight();
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
            // bit of a hack i guess..
            bool keepGoing = true;
            checkBoardTile(tile, keepGoing, newRow, newColumn, pieceSelected,
                           currentColorToMove);
            if (!keepGoing)
                return;
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
