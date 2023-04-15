#include "KingCheckLogic.h"

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
                kingPosition = { position.second / 100, position.first / 100 };
                break;
            }
        }
    }

    return kingPosition;
}

bool rookOrQueenAttacksKing(const std::array<std::array<Tile, 8>, 8>& board, int kingRow,
        int kingColumn, PieceColor kingColor)
{
    return false;
}

bool isKingInCheck(const std::array<std::array<Tile, 8>, 8>& board, PieceColor kingColor)
{
    auto [kingRow, kingColumn]{ findKingPosition(board, kingColor) };
    return rookOrQueenAttacksKing(board, kingRow, kingColumn, kingColor);
}

bool willKingBeInCheck(std::array<std::array<Tile, 8>, 8> board, int pieceRow, int pieceColumn,
        int newRow, int newColumn)
{
    // place the piece at the new spot and check if the king is in check
    Piece piece{ board[pieceRow][pieceColumn].getPiece().value() };
    board[pieceRow][pieceColumn].removePiece();
    // i think i should also remove a piece from newRow newColumn if there is a piece there
    board[newRow][newColumn].placePiece(piece);

    PieceColor color{ piece.getColor() };
    return isKingInCheck(board, color);
}
