#include "MoveValidator.h"

#include <stdexcept>
#include <iostream>

MoveValidator::MoveValidator(const std::array<std::array<Tile, 8>, 8>& board) : m_board{ board }
{
}

bool MoveValidator::moveIsValid(const Piece& piece, std::pair<int, int> newPosition)
{
    auto piecePosition{ piece.getPosition() };
    PieceType type{ piece.getType() };
    switch (type)
    {
        case PieceType::wPawn:
            return whitePawnMoveIsValid(piecePosition, newPosition);
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

bool MoveValidator::whitePawnMoveIsValid(std::pair<int, int> piecePosition,
        std::pair<int, int> newPosition)
{
    auto [pieceColumn, pieceRow]{ std::make_pair(piecePosition.first / 100,
            piecePosition.second / 100) };
    auto [newColumn, newRow]{ std::make_pair(newPosition.first / 100, newPosition.second / 100) };

    // wip
    if (m_board[newRow][newColumn].getPiece())
    {
        return false;
    }

    return true;
}
