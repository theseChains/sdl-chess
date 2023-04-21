#include "MoveValidator.h"

#include "Constants.h"

#include <stdexcept>
#include <iostream>

bool MoveValidator::moveIsValid(const std::array<std::array<Tile, 8>, 8>& board,
        const Piece& piece, int newRow, int newColumn)
{
    auto [pieceRow, pieceColumn]{ piece.getBoardPosition() };
    PieceColor color{ piece.getColor() };

    PieceType type{ piece.getType() };
    switch (type)
    {
        case PieceType::pawn:
            return pawnMoveIsValid(board, pieceRow, pieceColumn, newRow, newColumn, color);

        case PieceType::knight:
            return knightMoveIsValid(board, pieceRow, pieceColumn, newRow, newColumn, color);

        case PieceType::bishop:
            return bishopMoveIsValid(board, pieceRow, pieceColumn, newRow, newColumn, color);

        case PieceType::rook:
            return rookMoveIsValid(board, pieceRow, pieceColumn, newRow, newColumn, color);

        case PieceType::queen:
            return bishopMoveIsValid(board, pieceRow, pieceColumn, newRow, newColumn, color) ||
                rookMoveIsValid(board, pieceRow, pieceColumn, newRow, newColumn, color);

        case PieceType::king:
            return kingMoveIsValid(board, pieceRow, pieceColumn, newRow, newColumn, color);

        case PieceType::none:
            throw std::runtime_error{ "moveIsValid(): piece type none should not be checked" };
    }

    return true;
}

bool MoveValidator::pawnMoveIsValid(const std::array<std::array<Tile, 8>, 8>& board,
        int pawnRow, int pawnColumn, int newRow, int newColumn, PieceColor color)
{
    // todo: make a less lazy version of separating pawn move validation by color
    if (color == PieceColor::white)
    {
        auto piece{ board[newRow][newColumn].getPiece() };
        if (piece && piece->getColor() == PieceColor::black)
        {
            // can't attack forward
            if (pawnColumn == newColumn)
                return false;

            // a capture
            if (pawnRow - newRow == 1 && (pawnColumn - newColumn == 1 ||
                    pawnColumn - newColumn == -1))
                return true;

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
    // black pawn
    else
    {
        auto piece{ board[newRow][newColumn].getPiece() };
        if (piece && piece->getColor() == PieceColor::white)
        {
            // can't attack forward
            if (pawnColumn == newColumn)
                return false;

            // a capture
            if (newRow - pawnRow == 1 && (pawnColumn - newColumn == 1 ||
                    pawnColumn - newColumn == -1))
                return true;

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
}

bool MoveValidator::knightMoveIsValid(const std::array<std::array<Tile, 8>, 8>& board,
        int knightRow, int knightColumn, int newRow, int newColumn, PieceColor knightColor)
{
    if (!((std::abs(newRow - knightRow) == 2 && std::abs(newColumn - knightColumn) == 1) ||
        (std::abs(newRow - knightRow) == 1 && std::abs(newColumn - knightColumn) == 2)))
        return false;

    auto piece{ board[newRow][newColumn].getPiece() };
    // a piece of the same color stands on the new row and column
    if (piece && piece->getColor() == knightColor)
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

bool MoveValidator::bishopMoveIsValid(const std::array<std::array<Tile, 8>, 8>& board,
        int bishopRow, int bishopColumn, int newRow, int newColumn, PieceColor bishopColor)
{
    if (std::abs(newRow - bishopRow) != std::abs(newColumn - bishopColumn))
        return false;

    if (bishopJumpsOverPiece(board, bishopRow, bishopColumn, newRow, newColumn))
        return false;

    auto piece{ board[newRow][newColumn].getPiece() };
    // a piece of the same color stands on the new row and column
    if (piece && piece->getColor() == bishopColor)
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

bool MoveValidator::rookMoveIsValid(const std::array<std::array<Tile, 8>, 8>& board,
            int rookRow, int rookColumn, int newRow, int newColumn, PieceColor rookColor)
{
    if (newRow - rookRow != 0 && newColumn - rookColumn != 0)
        return false;

    if (rookJumpsOverPiece(board, rookRow, rookColumn, newRow, newColumn))
        return false;

    auto piece{ board[newRow][newColumn].getPiece() };
    // a piece of the same color stands on the new row and column
    if (piece && piece->getColor() == rookColor)
        return false;

    return true;
}

bool MoveValidator::kingMoveIsValid(const std::array<std::array<Tile, 8>, 8>& board,
            int kingRow, int kingColumn, int newRow, int newColumn, PieceColor kingColor)
{
    if (std::abs(newRow - kingRow) > 1 || std::abs(newColumn - kingColumn) > 1)
    {
        std::cout << "king move invalid by rules\n";
        return false;
    }

    auto piece{ board[newRow][newColumn].getPiece() };
    // a piece of the same color stands on the new row and column
    if (piece && piece->getColor() == kingColor)
        return false;

    std::cout << "king move is valid\n";

    return true;
}
