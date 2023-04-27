#include "KingMateLogic.h"
#include "MoveValidator.h"

#include <iostream>

bool doesKingHaveValidMoves(const std::array<std::array<Tile, 8>, 8>& board, PieceColor kingColor)
{
    auto [kingRow, kingColumn]{ findKingPosition(board, kingColor).value() };
    Piece king{ board[kingRow][kingColumn].getPiece().value() };
    // this doesn't print anything at all.. nonsense

    for (int rowOffset{ -1 }; rowOffset < 2; ++rowOffset)
    {
        for (int columnOffset{ -1 }; columnOffset < 2; ++columnOffset)
        {
            if (rowOffset == 0 && columnOffset == 0)
                continue;

            int newRow{ kingRow + rowOffset };
            int newColumn{ kingColumn + columnOffset };

            if (newRow > 7 || newRow < 0 || newColumn > 7 || newColumn < 0)
                continue;

            if (MoveValidator::moveIsValid(board, king, newRow, newColumn) &&
                    !kingWillBeInCheck(board, king, newRow, newColumn))
            {
                std::cout << "king has valid move at " << newRow << ' ' << newColumn << '\n';
                return true;
            }
        }
    }

    std::cout << "king has no valid moves\n";

    return false;
}

bool isKingCheckmated(const std::array<std::array<Tile, 8>, 8>& board, PieceColor kingColor)
{
    // so we need to check if any pieces can block the attacker, capture the attacker,
    // or whether king has legal moves
    bool isCheckmated{ isKingInCheck(board, kingColor) && !doesKingHaveValidMoves(board, kingColor) };

    return isCheckmated;
}
