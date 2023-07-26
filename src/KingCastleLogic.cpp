#include "KingCastleLogic.h"

#include <algorithm>
#include <iostream>

#include "Constants.h"

bool kingCanCastle(const TileBoard& board, int kingRow, int kingColumn,
                   int newRow, int newColumn, PieceColor kingColor)
{
    std::array<int, 2> validColumns{ 2, 6 };
    std::array<int, 2> validRows{ constants::topRow, constants::bottomRow };
    if (std::ranges::find(validColumns, newColumn) == validColumns.end() ||
        std::ranges::find(validRows, newRow) == validRows.end())
        return false;

    if (newColumn == 2 &&
        (board[newRow][newColumn + 1].getPiece().has_value() ||
         board[newRow][newColumn].getPiece().has_value() ||
         board[newRow][newColumn - 1].getPiece().has_value()))
        return false;

    if (newColumn == 6 &&
        (board[newRow][newColumn - 1].getPiece().has_value() ||
         board[newRow][newColumn].getPiece().has_value()))
        return false;

    auto king{ board[kingRow][kingColumn].getPiece() };
    if (!king || king->hasMoved())
        return false;

    int rookRow{ kingColor == PieceColor::white ? constants::bottomRow
                                                : constants::topRow };
    int rookColumn{ newColumn == 2 ? 0 : 7 };

    auto rook{ board[rookRow][rookColumn].getPiece() };
    if (!rook || rook->hasMoved())
        return false;

    return true;
}

void moveRookForCastling(TileBoard& board, int kingRow, int newKingColumn)
{
    int newRookColumn{ newKingColumn == 2 ? 3 : 5 };
    int oldRookColumn{ newKingColumn == 2 ? 0 : 7 };

    Piece& rook{ board[kingRow][oldRookColumn].getPiece().value() };
    Tile& newTile{ board[kingRow][newRookColumn] };
    Tile& oldTile{ board[kingRow][oldRookColumn] };
    oldTile.removePiece();
    newTile.placePiece(rook);
    newTile.getPiece()->setPositionFromBoardPosition(
        { kingRow, newRookColumn });
    rook.setHasMoved();
}
