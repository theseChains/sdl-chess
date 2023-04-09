#include "MoveValidator.h"

#include "Constants.h"

#include <stdexcept>
#include <iostream>

bool MoveValidator::moveIsValid(std::array<std::array<Tile, 8>, 8>& board, const Piece& piece,
        std::pair<int, int> newPosition)
{
    auto piecePosition{ piece.getPosition() };
    PieceType type{ piece.getType() };
    switch (type)
    {
        case PieceType::wPawn:
            return whitePawnMoveIsValid(board, piecePosition, newPosition);
        case PieceType::bPawn:
        case PieceType::bKnight:
        case PieceType::wKnight:
        case PieceType::bBishop:
        case PieceType::wBishop:
        case PieceType::bRook:
        case PieceType::wRook:
        case PieceType::bQueen:
        case PieceType::wQueen:
        case PieceType::bKing:
        case PieceType::wKing:
            return true;
        case PieceType::none:
            throw std::runtime_error{ "moveIsValid(): piece type none should not be checked" };
    }

    return true;
}

bool MoveValidator::whitePawnMoveIsValid(std::array<std::array<Tile, 8>, 8>& board,
        std::pair<int, int> piecePosition, std::pair<int, int> newPosition)
{
    // we don't update the board!!! that's the problem man..........
    auto [pawnColumn, pawnRow]{ std::make_pair(piecePosition.first / 100,
            piecePosition.second / 100) };
    auto [newColumn, newRow]{ std::make_pair(newPosition.first / 100, newPosition.second / 100) };
    std::cout << "new row and col: " << newRow << ' ' << newColumn << '\n';

    if (board[newRow][newColumn].getPiece())
    {
        // can't attack forward
        if (pawnColumn == newColumn)
            return false;
        std::cout << "capturing or not\n";
        // a capture
        if (pawnRow - newRow == 1 && (pawnColumn - newColumn == 1 || pawnColumn - newColumn == -1))
        {
            board[newRow][newColumn].removePiece();
            return true;
        }

        return false;
    }
    // new tile doesn't have a piece
    else
    {
        if (pawnColumn != newColumn)
            return false;

        if (pawnRow == constants::whitePawnStartRow && pawnRow - newRow <= 2)
            return true;
        if (pawnRow == constants::whitePawnStartRow && pawnRow - newRow > 2)
            return false;
        if (pawnRow != constants::whitePawnStartRow && pawnRow - newRow == 1)
            return true;

        return false;
    }
}
