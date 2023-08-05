#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>

#include "Aliases.h"
#include "Colors.h"
#include "Move.h"
#include "Tile.h"

class GameLogic
{
public:
    GameLogic(TileBoard& tileBoard, Move& lastMove);

    bool playerMoveIsValid(const Piece& piece, int newRow, int newColumn) const;
    bool playerTookEnPassant(const Piece& piece, int newRow, int newColumn,
                             int oldRow, int oldColumn) const;
    void checkForEnPassantCapture(const Piece& piece, int newRow, int newColumn,
                                  int oldRow, int oldColumn);
    bool playerCastled(const Piece& piece, int newColumn, int oldColumn) const;
    void checkForCastling(const Piece& piece, int newRow, int newColumn,
                          int oldColumn);
    bool playerPromotingPawn(const Piece& piece, int newRow,
                             int newColumn) const;

    void updateFiftyMoveCounter(const Piece& piece, int newRow, int newColumn,
                                int oldRow, int oldColumn);
    void updatePieceProperties(int newRow, int newColumn);

    void resetFiftyMoveCounter();
    void incrementFiftyMoveCounter();

    PieceColor checkForGameEnd(const std::vector<TileBoard>& positions,
                               PieceColor currentColorToMove) const;

private:
    TileBoard& m_tileBoard;
    Move& m_lastMove;
    int m_fiftyMoveCounter{};
};

#endif
