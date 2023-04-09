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
    PieceColor color{ piece.getColor() };

    PieceType type{ piece.getType() };
    switch (type)
    {
        case PieceType::wPawn:
            return whitePawnMoveIsValid(board, pieceRow, pieceColumn, newRow, newColumn);

        case PieceType::bPawn:
            return blackPawnMoveIsValid(board, pieceRow, pieceColumn, newRow, newColumn);

        case PieceType::bKnight:
        case PieceType::wKnight:
            return knightMoveIsValid(board, pieceRow, pieceColumn, newRow, newColumn, color);

        case PieceType::bBishop:
        case PieceType::wBishop:
            return bishopMoveIsValid(board, pieceRow, pieceColumn, newRow, newColumn, color);

        case PieceType::bRook:
        case PieceType::wRook:
            return rookMoveIsValid(board, pieceRow, pieceColumn, newRow, newColumn, color);

        case PieceType::bQueen:
        case PieceType::wQueen:
            return bishopMoveIsValid(board, pieceRow, pieceColumn, newRow, newColumn, color) ||
                rookMoveIsValid(board, pieceRow, pieceColumn, newRow, newColumn, color);

        case PieceType::bKing:
        case PieceType::wKing:
            return kingMoveIsValid(board, pieceRow, pieceColumn, newRow, newColumn, color);

        case PieceType::none:
            throw std::runtime_error{ "moveIsValid(): piece type none should not be checked" };
    }

    return true;
}

bool MoveValidator::whitePawnMoveIsValid(std::array<std::array<Tile, 8>, 8>& board,
        int pawnRow, int pawnColumn, int newRow, int newColumn)
{
    auto piece{ board[newRow][newColumn].getPiece() };
    if (piece && piece->getColor() == PieceColor::black)
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
    // new tile doesn't have a piece or the piece is white
    else
    {
        if (pawnColumn != newColumn)
            return false;

        if (pawnRow == constants::whitePawnStartRow && pawnRow - newRow <= 2 &&
                !board[pawnRow - 1][pawnColumn].getPiece())
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
    auto piece{ board[newRow][newColumn].getPiece() };
    if (piece && piece->getColor() == PieceColor::white)
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
    // new tile doesn't have a piece or the piece is black
    else
    {
        if (pawnColumn != newColumn)
            return false;

        if (pawnRow == constants::blackPawnStartRow && newRow - pawnRow <= 2 &&
                !board[pawnRow + 1][pawnColumn].getPiece())
            return true;
        if (pawnRow == constants::blackPawnStartRow && newRow - pawnRow > 2)
            return false;
        if (pawnRow != constants::blackPawnStartRow && newRow - pawnRow == 1)
            return true;

        return false;
    }
}

bool MoveValidator::knightMoveIsValid(std::array<std::array<Tile, 8>, 8>& board,
        int knightRow, int knightColumn, int newRow, int newColumn, PieceColor knightColor)
{
    if (!((std::abs(newRow - knightRow) == 2 && std::abs(newColumn - knightColumn) == 1) ||
        (std::abs(newRow - knightRow) == 1 && std::abs(newColumn - knightColumn) == 2)))
        return false;

    // todo: check if king will be in check after knight move
    // if (kingWillBeInCheck(...))
    //     return false;

    auto piece{ board[newRow][newColumn].getPiece() };
    if (piece && piece->getColor() != knightColor)
        board[newRow][newColumn].removePiece();
    else if (piece && piece->getColor() == knightColor)
        return false;

    return true;
}

std::pair<int, int> getBishopDirection(int bishopRow, int bishopColumn, int newRow, int newColumn)
{
    int rowDirection{ bishopRow < newRow ? 1 : -1 };
    int columnDirection{ bishopColumn < newColumn ? 1 : -1 };
    return { rowDirection, columnDirection };
}

bool bishopJumpsOverPiece(const std::array<std::array<Tile, 8>, 8>& board,
        int bishopRow, int bishopColumn, int newRow, int newColumn)
{
    auto [rowDirection, columnDirection]{
        getBishopDirection(bishopRow, bishopColumn, newRow, newColumn) };

    while (bishopRow + rowDirection != newRow)
    {
        if (board[bishopRow + rowDirection][bishopColumn + columnDirection].getPiece())
            return true;

        bishopRow += rowDirection;
        bishopColumn += columnDirection;
    }

    return false;
}

bool MoveValidator::bishopMoveIsValid(std::array<std::array<Tile, 8>, 8>& board,
        int bishopRow, int bishopColumn, int newRow, int newColumn, PieceColor bishopColor)
{
    if (std::abs(newRow - bishopRow) != std::abs(newColumn - bishopColumn))
        return false;

    // todo: check if king will be in check

    if (bishopJumpsOverPiece(board, bishopRow, bishopColumn, newRow, newColumn))
        return false;

    auto piece{ board[newRow][newColumn].getPiece() };
    if (piece && piece->getColor() != bishopColor)
        board[newRow][newColumn].removePiece();
    else if (piece && piece->getColor() == bishopColor)
        return false;

    return true;
}

std::pair<int, int> getRookDirection(int rookRow, int rookColumn, int newRow, int newColumn)
{
    if (rookRow != newRow)
    {
        int rowDirection{ rookRow < newRow ? 1 : -1 };
        return { rowDirection, 0 };
    }
    else
    {
        int columnDirection{ rookColumn < newColumn ? 1 : -1 };
        return { 0, columnDirection };
    }
}

bool rookJumpsOverPiece(const std::array<std::array<Tile, 8>, 8>& board,
        int rookRow, int rookColumn, int newRow, int newColumn)
{
    auto [rowDirection, columnDirection]{
        getRookDirection(rookRow, rookColumn, newRow, newColumn) };

    if (rowDirection != 0)
    {
        while (rookRow + rowDirection != newRow)
        {
            if (board[rookRow + rowDirection][rookColumn].getPiece())
                return true;

            rookRow += rowDirection;
        }
    }
    else if (columnDirection != 0)
    {
        while (rookColumn + columnDirection != newColumn)
        {
            if (board[rookRow][rookColumn + columnDirection].getPiece())
                return true;

            rookColumn += columnDirection;
        }
    }

    return false;
}

bool MoveValidator::rookMoveIsValid(std::array<std::array<Tile, 8>, 8>& board,
            int rookRow, int rookColumn, int newRow, int newColumn, PieceColor rookColor)
{
    if (newRow - rookRow != 0 && newColumn - rookColumn != 0)
        return false;

    // todo: check if king will be in check
    if (rookJumpsOverPiece(board, rookRow, rookColumn, newRow, newColumn))
        return false;

    auto piece{ board[newRow][newColumn].getPiece() };
    if (piece && piece->getColor() != rookColor)
        board[newRow][newColumn].removePiece();
    else if (piece && piece->getColor() == rookColor)
        return false;

    return true;
}

bool MoveValidator::kingMoveIsValid(std::array<std::array<Tile, 8>, 8>& board,
            int kingRow, int kingColumn, int newRow, int newColumn, PieceColor kingColor)
{
    if (std::abs(newRow - kingRow) > 1 || std::abs(newColumn - kingColumn) > 1)
        return false;

    // todo: check if king will be in check and if the king is capturing a piece of the same color

    auto piece{ board[newRow][newColumn].getPiece() };
    if (piece && piece->getColor() != kingColor)
        board[newRow][newColumn].removePiece();
    else if (piece && piece->getColor() == kingColor)
        return false;

    return true;
}
