#include "KingMateLogic.h"
#include "MoveValidator.h"

#include <iostream>

bool kingHasLegalMoves(const std::array<std::array<Tile, 8>, 8>& board, const Piece& king,
        int currentRow, int currentColumn)
{
    for (int rowOffset{ -1 }; rowOffset < 2; ++rowOffset)
    {
        for (int columnOffset{ -1 }; columnOffset < 2; ++columnOffset)
        {
            if (rowOffset == 0 && columnOffset == 0)
                continue;

            int newRow{ currentRow + rowOffset };
            int newColumn{ currentColumn + columnOffset };

            if (newRow > 7 || newRow < 0 || newColumn > 7 || newColumn < 0)
                continue;

            if (MoveValidator::moveIsValid(board, king, newRow, newColumn) &&
                    !kingWillBeInCheck(board, king, newRow, newColumn))
                return true;
        }
    }

    return false;
}

bool pawnHasLegalMoves(const std::array<std::array<Tile, 8>, 8>& board, const Piece& pawn,
        int currentRow, int currentColumn)
{
    for (int columnOffset{ -1 }; columnOffset <= 1; ++columnOffset)
    {
        int newRow{ currentRow };
        if (pawn.getColor() == PieceColor::white)
            --newRow;
        else
            ++newRow;
        int newColumn{ currentColumn + columnOffset };

        if (newRow > 7 || newRow < 0 || newColumn > 7 || newColumn < 0)
            continue;

        if (MoveValidator::moveIsValid(board, pawn, newRow, newColumn) &&
                !kingWillBeInCheck(board, pawn, newRow, newColumn))
            return true;
    }

    return false;
}

bool knightHasLegalMoves(const std::array<std::array<Tile, 8>, 8>& board, const Piece& knight,
        int currentRow, int currentColumn)
{
    std::array<int, 8> rowOffsets{ -2, -2, -1, -1, 1, 1, 2, 2 };
    std::array<int, 8> columnOffsets{ 1, -1, 2, -2, 2, -2, 1, -1 };
    for (int i{ 0 }; i < 8; ++i)
    {
        int newRow{ currentRow + rowOffsets[i] };
        int newColumn{ currentColumn + columnOffsets[i] };

        if (newRow > 7 || newRow < 0 || newColumn > 7 || newColumn < 0)
            continue;

        if (MoveValidator::moveIsValid(board, knight, newRow, newColumn) &&
                !kingWillBeInCheck(board, knight, newRow, newColumn))
            return true;
    }

    return false;
}

bool bishopHasLegalMoves(const std::array<std::array<Tile, 8>, 8>& board, const Piece& bishop,
        int currentRow, int currentColumn)
{
    std::array<int, 4> rowDirections{ 1, 1, -1, -1 };
    std::array<int, 4> columnDirections{ 1, -1, 1, -1 };

    for (int i{ 0 }; i < 4; ++i)
    {
        int newRow{ currentRow + rowDirections[i] };
        int newColumn{ currentColumn + columnDirections[i] };

        while (newRow >= 0 && newRow < 8 && newColumn >= 0 && newColumn < 8)
        {
            if (MoveValidator::moveIsValid(board, bishop, newRow, newColumn) &&
                    !kingWillBeInCheck(board, bishop, newRow, newColumn))
                return true;

            newRow += rowDirections[i];
            newColumn += columnDirections[i];
        }
    }

    return false;
}

bool rookHasLegalMoves(const std::array<std::array<Tile, 8>, 8>& board, const Piece& rook,
        int currentRow, int currentColumn)
{
    std::array<int, 4> rowDirections{ 1, -1, 0, 0 };
    std::array<int, 4> columnDirections{ 0, 0, 1, -1 };

    for (int i{ 0 }; i < 4; ++i)
    {
        int newRow{ currentRow + rowDirections[i] };
        int newColumn{ currentColumn + columnDirections[i] };

        while (newRow >= 0 && newRow < 8 && newColumn >= 0 && newColumn < 8)
        {
            if (MoveValidator::moveIsValid(board, rook, newRow, newColumn) &&
                    !kingWillBeInCheck(board, rook, newRow, newColumn))
                return true;

            newRow += rowDirections[i];
            newColumn += columnDirections[i];
        }
    }

    return false;
}

bool playerHasLegalMoves(const std::array<std::array<Tile, 8>, 8>& board, PieceColor color)
{
    for (const auto& row : board)
    {
        for (const auto& tile : row)
        {
            auto piece{ tile.getPiece() };
            auto [pieceRow, pieceColumn]{ piece->getBoardPosition() };
            if (piece && piece->getColor() == color && piece->getType() == PieceType::pawn &&
                    pawnHasLegalMoves(board, piece.value(), pieceRow, pieceColumn))
                return true;
            else if (piece && piece->getColor() == color && piece->getType() == PieceType::knight &&
                    knightHasLegalMoves(board, piece.value(), pieceRow, pieceColumn))
                return true;
            else if (piece && piece->getColor() == color && piece->getType() == PieceType::bishop &&
                    bishopHasLegalMoves(board, piece.value(), pieceRow, pieceColumn))
                return true;
            else if (piece && piece->getColor() == color && piece->getType() == PieceType::rook &&
                    rookHasLegalMoves(board, piece.value(), pieceRow, pieceColumn))
                return true;
            else if (piece && piece->getColor() == color && piece->getType() == PieceType::queen &&
                    rookHasLegalMoves(board, piece.value(), pieceRow, pieceColumn) &&
                    bishopHasLegalMoves(board, piece.value(), pieceRow, pieceColumn))
                return true;
            else if (piece && piece->getColor() == color && piece->getType() == PieceType::king &&
                    kingHasLegalMoves(board, piece.value(), pieceRow, pieceColumn))
                return true;
        }
    }

    return false;
}

bool isKingCheckmated(const std::array<std::array<Tile, 8>, 8>& board, PieceColor kingColor)
{
    bool isCheckmated{ isKingInCheck(board, kingColor) && !playerHasLegalMoves(board, kingColor) };

    return isCheckmated;
}
