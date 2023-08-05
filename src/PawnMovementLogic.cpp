#include "PawnMovementLogic.h"

#include <iostream>

#include "Constants.h"

bool whitePawnMoveIsValid(const TileBoard& board, int pawnRow, int pawnColumn,
                          int newRow, int newColumn)
{
    auto piece{ board[newRow][newColumn].getPiece() };
    if (piece && piece->getColor() == PieceColor::black)
    {
        if (pawnColumn == newColumn || pawnRow == newRow)
            return false;

        if (pawnRow - newRow == 1 &&
            (pawnColumn - newColumn == 1 || pawnColumn - newColumn == -1))
            return true;

        return false;
    }
    else
    {
        if (pawnColumn != newColumn || pawnRow == newRow)
            return false;
        if (newRow > pawnRow)
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

bool blackPawnMoveIsValid(const TileBoard& board, int pawnRow, int pawnColumn,
                          int newRow, int newColumn)
{
    auto piece{ board[newRow][newColumn].getPiece() };
    if (piece && piece->getColor() == PieceColor::white)
    {
        if (pawnColumn == newColumn || pawnRow == newRow)
            return false;

        if (newRow - pawnRow == 1 &&
            (pawnColumn - newColumn == 1 || pawnColumn - newColumn == -1))
            return true;

        return false;
    }
    else
    {
        if (pawnColumn != newColumn || pawnRow == newRow)
            return false;
        if (newRow < pawnRow)
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

bool canTakeEnPassant(TileBoard& board, const Piece& piece, int newRow,
                      int newColumn, const Move& lastMove)
{
    if (piece.getType() != PieceType::pawn ||
        lastMove.pieceType != PieceType::pawn)
        return false;

    PieceColor color{ piece.getColor() };
    auto [oldRow, oldColumn]{ piece.getBoardPosition() };
    if ((color == PieceColor::white && (newRow != 2 || oldRow != 3)) ||
        (color == PieceColor::black && (newRow != 5 || oldRow != 4)) ||
        oldColumn == newColumn || std::abs(newColumn - oldColumn) > 1)
        return false;

    if (!board[oldRow][newColumn].getPiece())
        return false;

    Piece pawnToCapture{ board[oldRow][newColumn].getPiece().value() };
    if (lastMove.to != pawnToCapture.getBoardPosition())
        return false;

    int pawnToCaptureStartingRow{ pawnToCapture.getColor() == PieceColor::white
                                      ? constants::whitePawnStartRow
                                      : constants::blackPawnStartRow };
    std::pair<int, int> pawnToCaptureStartingPosition{ pawnToCaptureStartingRow,
                                                       newColumn };
    if (lastMove.from != pawnToCaptureStartingPosition)
        return false;

    return true;
}
