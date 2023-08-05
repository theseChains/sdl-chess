#include "GameLogic.h"

#include <algorithm>
#include <iostream>
#include <ranges>

#include "KingCheckLogic.h"
#include "KingMateLogic.h"
#include "MoveValidator.h"
#include "PawnMovementLogic.h"

GameLogic::GameLogic(TileBoard& tileBoard, Move& lastMove)
    : m_tileBoard{ tileBoard }, m_lastMove{ lastMove }
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
            !m_tileBoard[newColumn][newRow].getPiece());
}

bool GameLogic::playerCastled(const Piece& piece, int newColumn,
                              int oldColumn) const
{
    return (piece.getType() == PieceType::king &&
            std::abs(oldColumn - newColumn) == 2);
}

bool GameLogic::playerPromotingPawn(const Piece& piece, int newRow,
                                    int newColumn) const
{
    return (piece.getType() == PieceType::pawn &&
            pawnIsPromoting(m_tileBoard, newRow, newColumn));
}

void GameLogic::updatePieceProperties(int newRow, int newColumn)
{
    Piece& pieceReference{
        m_tileBoard[newRow][newColumn].getPiece().value()
    };
    pieceReference.setHasMoved();
}

PieceColor GameLogic::checkForGameEnd(const std::vector<TileBoard>& positions,
                                      PieceColor currentColorToMove) const
{
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

    if (std::ranges::count(positions, m_tileBoard) >= 3)
    {
        std::cout << "draw by three-fold repetition\n";
        currentColorToMove = PieceColor::noColor;
    }

    return currentColorToMove;
}
