#include "KingCheckLogic.h"

#include "MoveValidator.h"

#include <iostream>
#include <optional>

std::optional<std::pair<int, int>> findKingPosition(const std::array<std::array<Tile, 8>, 8>& board,
        PieceColor kingColor)
{
    for (const auto& row : board)
    {
        for (const auto& tile : row)
        {
            auto piece{ tile.getPiece() };
            if (piece && piece->getType() == PieceType::king && piece->getColor() == kingColor)
                return { piece->getBoardPosition() };
        }
    }

    return std::nullopt;
}

bool isKingInCheck(const std::array<std::array<Tile, 8>, 8>& board, PieceColor kingColor)
{
    auto [kingRow, kingColumn]{ findKingPosition(board, kingColor).value() };
    for (const auto& row : board)
    {
        for (const auto& tile : row)
        {
            auto piece{ tile.getPiece() };
            // piece of different color can capture king
            if (piece && piece->getColor() != kingColor &&
                    MoveValidator::moveIsValid(board, piece.value(), kingRow, kingColumn))
            {
                std::cout << "king in check by piece at " << piece->getBoardPosition().first
                    << ' ' << piece->getBoardPosition().second << '\n';
                return true;
            }
        }
    }

    return false;
}

bool kingWillBeInCheck(std::array<std::array<Tile, 8>, 8> board, const Piece& piece,
        int newRow, int newColumn)
{
    auto [pieceRow, pieceColumn]{ piece.getBoardPosition() };

    // place the piece at the new spot and check if the king is in check
    board[pieceRow][pieceColumn].removePiece();
    // remove previous piece in case of capturing
    board[newRow][newColumn].removePiece();
    board[newRow][newColumn].placePiece(piece);
    // set the new position for the piece
    board[newRow][newColumn].getPiece()->setBoardPosition({ newRow, newColumn });

    PieceColor color{ piece.getColor() };
    return isKingInCheck(board, color);
}
