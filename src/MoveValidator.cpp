#include "MoveValidator.h"

#include "Constants.h"

#include <stdexcept>
#include <iostream>

bool MoveValidator::moveIsValid(std::array<std::array<Tile, 8>, 8>& board, const Piece& piece,
        std::pair<int, int> newPosition)
{
    auto piecePosition{ piece.getPosition() };
    auto [pieceColumn, pieceRow]{ std::make_pair(piecePosition.first / 100,
            piecePosition.second / 100) };
    auto [newColumn, newRow]{ std::make_pair(newPosition.first / 100, newPosition.second / 100) };

    PieceType type{ piece.getType() };
    switch (type)
    {
        case PieceType::wPawn:
            return whitePawnMoveIsValid(board, pieceRow, pieceColumn, newRow, newColumn);
        case PieceType::bPawn:
            return blackPawnMoveIsValid(board, pieceRow, pieceColumn, newRow, newColumn);
        case PieceType::bKnight:
        case PieceType::wKnight:
            return knightMoveIsValis(board, pieceRow, pieceColumn, newRow, newColumn);
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
        int pawnRow, int pawnColumn, int newRow, int newColumn)
{
    if (board[newRow][newColumn].getPiece())
    {
        // can't attack forward
        if (pawnColumn == newColumn)
            return false;
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

bool MoveValidator::blackPawnMoveIsValid(std::array<std::array<Tile, 8>, 8>& board,
        int pawnRow, int pawnColumn, int newRow, int newColumn)
{
    if (board[newRow][newColumn].getPiece())
    {
        // can't attack forward
        if (pawnColumn == newColumn)
            return false;
        // a capture
        if (newRow - pawnRow == 1 && (pawnColumn - newColumn == 1 || pawnColumn - newColumn == -1))
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

        if (pawnRow == constants::blackPawnStartRow && newRow - pawnRow <= 2)
            return true;
        if (pawnRow == constants::blackPawnStartRow && newRow - pawnRow > 2)
            return false;
        if (pawnRow != constants::blackPawnStartRow && newRow - pawnRow == 1)
            return true;

        return false;
    }
}

bool MoveValidator::knightMoveIsValis(std::array<std::array<Tile, 8>, 8>& board,
            int knightRow, int knightColumn, int newRow, int newColumn)
{
    if (!((std::abs(newRow - knightRow) == 2 && std::abs(newColumn - knightColumn) == 1) ||
        (std::abs(newRow - knightRow) == 1 && std::abs(newColumn - knightColumn) == 2)))
        return false;

    // todo: check if king will be in check after knight move

    if (board[newRow][newColumn].getPiece())
        board[newRow][newColumn].removePiece();

    return true;
}
