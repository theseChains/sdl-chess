#include "KingCheckLogic.h"

#include <iostream>
#include <optional>
#include <stdexcept>

#include "MoveValidator.h"

std::pair<int, int> findKingPosition(const TileBoard& board,
                                     PieceColor kingColor)
{
    for (const auto& row : board)
    {
        for (const auto& tile : row)
        {
            auto piece{ tile.getPiece() };
            if (piece && piece->getType() == PieceType::king &&
                piece->getColor() == kingColor)
                return { piece->getBoardPosition() };
        }
    }

    throw std::runtime_error{ "no kign found on board" };
}

bool isKingInCheck(const TileBoard& board, PieceColor kingColor)
{
    auto [kingRow, kingColumn]{ findKingPosition(board, kingColor) };
    for (const auto& row : board)
    {
        for (const auto& tile : row)
        {
            auto piece{ tile.getPiece() };
            if (piece && piece->getColor() != kingColor &&
                MoveValidator::moveIsValid(board, piece.value(), kingRow,
                                           kingColumn))
                return true;
        }
    }

    return false;
}

bool kingWillBeInCheck(TileBoard board, const Piece& piece, int newRow,
                       int newColumn)
{
    auto [pieceRow, pieceColumn]{ piece.getBoardPosition() };

    board[pieceRow][pieceColumn].removePiece();
    board[newRow][newColumn].removePiece();
    board[newRow][newColumn].placePiece(piece);
    board[newRow][newColumn].getPiece()->setPositionFromBoardPosition(
        { newRow, newColumn });

    PieceColor color{ piece.getColor() };
    return isKingInCheck(board, color);
}
