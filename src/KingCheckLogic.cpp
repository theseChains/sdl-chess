#include "KingCheckLogic.h"

#include "MoveValidator.h"

std::pair<int, int> findKingPosition(const std::array<std::array<Tile, 8>, 8>& board,
        PieceColor kingColor)
{
    std::pair<int, int> kingPosition{};
    for (const auto& row : board)
    {
        for (const auto& tile : row)
        {
            auto piece{ tile.getPiece() };
            if (piece && piece->getType() == PieceType::king && piece->getColor() == kingColor)
            {
                auto position{ piece->getPosition() };
                // positions are still kinda messed up i guess
                kingPosition = { position.second / 100, position.first / 100 };
                break;
            }
        }
    }

    return kingPosition;
}

bool isKingInCheck(const std::array<std::array<Tile, 8>, 8>& board, PieceColor kingColor)
{
    auto [kingRow, kingColumn]{ findKingPosition(board, kingColor) };
    for (const auto& row : board)
    {
        for (const auto& tile : row)
        {
            auto piece{ tile.getPiece() };
            // piece of different color can capture king
            if (piece && piece->getColor() != kingColor &&
                    MoveValidator::moveIsValid(board, piece.value(), kingRow, kingColumn))
                return true;
        }
    }

    return false;
}

bool kingWillBeInCheck(std::array<std::array<Tile, 8>, 8> board, const Piece& piece,
        int newRow, int newColumn)
{
    auto piecePosition{ piece.getPosition() };
    auto [pieceColumn, pieceRow]{ std::make_pair(piecePosition.first / 100,
            piecePosition.second / 100) };
    // place the piece at the new spot and check if the king is in check
    board[pieceRow][pieceColumn].removePiece();
    // i think i should also remove a piece from newRow newColumn if there is a piece there
    board[newRow][newColumn].placePiece(piece);

    PieceColor color{ piece.getColor() };
    return isKingInCheck(board, color);
}
