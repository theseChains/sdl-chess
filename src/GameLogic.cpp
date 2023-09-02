#include "GameLogic.h"

#include <algorithm>
#include <iostream>
#include <ranges>

#include "KingCastleLogic.h"
#include "KingCheckLogic.h"
#include "KingMateLogic.h"
#include "MoveValidator.h"
#include "PawnMovementLogic.h"
#include "PieceType.h"

GameLogic::GameLogic(TileBoard& tileBoard)
    : m_tileBoard{ tileBoard },
      m_lastMove{ { 0, 0 }, { 0, 0 }, PieceType::none },
      m_fiftyMoveCounter{ 0 },
      m_positions{},
      m_promotingPawn{ false }
{
}

bool GameLogic::playerMoveIsValid(const Piece& piece, int newRow,
                                  int newColumn) const
{
    return (
        (MoveValidator::moveIsValid(m_tileBoard, piece, newRow, newColumn) ||
         canTakeEnPassant(m_tileBoard, piece, newRow, newColumn, m_lastMove)) &&
        !kingWillBeInCheck(m_tileBoard, piece, newRow, newColumn));
}

bool GameLogic::playerTookEnPassant(const Piece& piece, int newRow,
                                    int newColumn, int oldRow,
                                    int oldColumn) const
{
    return (piece.getType() == PieceType::pawn && newColumn != oldColumn &&
            m_tileBoard[oldRow][newColumn].getPiece() &&
            m_tileBoard[oldRow][newColumn].getPiece()->getType() ==
                PieceType::pawn &&
            !m_tileBoard[newRow][newColumn].getPiece());
}

void GameLogic::checkForEnPassantCapture(const Piece& piece, int newRow,
                                         int newColumn, int oldRow,
                                         int oldColumn)
{
    if (playerTookEnPassant(piece, newRow, newColumn, oldRow, oldColumn))
        m_tileBoard[oldRow][newColumn].removePiece();
}

void GameLogic::updateFiftyMoveCounter(const Piece& piece, int newRow,
                                       int newColumn, int oldRow, int oldColumn)
{
    if (playerTookEnPassant(piece, newRow, newColumn, oldRow, oldColumn))
        resetFiftyMoveCounter();
    else if (m_lastMove.pieceType != PieceType::pawn &&
             !m_tileBoard[newRow][newColumn].getPiece())
    {
        incrementFiftyMoveCounter();
    }
    else
        resetFiftyMoveCounter();
}

bool GameLogic::playerCastled(const Piece& piece, int newColumn,
                              int oldColumn) const
{
    return (piece.getType() == PieceType::king &&
            std::abs(oldColumn - newColumn) == 2);
}

void GameLogic::checkForCastling(const Piece& piece, int newRow, int newColumn,
                                 int oldColumn)
{
    if (playerCastled(piece, newColumn, oldColumn))
        moveRookForCastling(m_tileBoard, newRow, newColumn);
}

bool GameLogic::playerPromotingPawn(const Piece& piece, int newRow,
                                    int newColumn) const
{
    return (piece.getType() == PieceType::pawn &&
            pawnIsPromoting(m_tileBoard, newRow, newColumn));
}

void GameLogic::checkForPawnPromotion(const Piece& piece, int newRow,
                                      int newColumn)
{
    if (playerPromotingPawn(piece, newRow, newColumn))
        m_promotingPawn = true;
}

void GameLogic::updatePieceProperties(int newRow, int newColumn)
{
    Piece& pieceReference{ m_tileBoard[newRow][newColumn].getPiece().value() };
    pieceReference.setHasMoved();
}

void GameLogic::resetFiftyMoveCounter()
{
    m_fiftyMoveCounter = 0;
}

void GameLogic::incrementFiftyMoveCounter()
{
    ++m_fiftyMoveCounter;
}

bool GameLogic::promotingPawn() const
{
    return m_promotingPawn;
}

void GameLogic::setPawnPromotion(bool value)
{
    m_promotingPawn = value;
}

const Move& GameLogic::getLastMove() const
{
    return m_lastMove;
}

void GameLogic::setLastMove(const Move& lastMove)
{
    m_lastMove = lastMove;
}

void GameLogic::addPosition(const TileBoard& tileBoard)
{
    m_positions.push_back(tileBoard);
}

PieceColor GameLogic::checkForGameEnd(PieceColor currentColorToMove) const
{
    if (isKingCheckmated(m_tileBoard, currentColorToMove))
    {
        if (currentColorToMove == PieceColor::white)
            std::cout << "white king is checkmated, black wins!\n";
        else
            std::cout << "black king is checkmated, white wins!\n";

        currentColorToMove = PieceColor::noColor;

        return currentColorToMove;
    }

    if (!isKingInCheck(m_tileBoard, currentColorToMove) &&
        !playerHasLegalMoves(m_tileBoard, currentColorToMove))
    {
        std::cout << "draw by stalemate\n";
        currentColorToMove = PieceColor::noColor;
    }

    if (std::ranges::count(m_positions, m_tileBoard) >= 3)
    {
        std::cout << "draw by three-fold repetition\n";
        currentColorToMove = PieceColor::noColor;
    }

    if (m_fiftyMoveCounter == 50)
    {
        std::cout << "draw by the fifty-rule move\n";
        currentColorToMove = PieceColor::noColor;
    }

    return currentColorToMove;
}
