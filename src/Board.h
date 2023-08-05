#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <vector>

#include "Aliases.h"
#include "BoardDrawer.h"
#include "GameLogic.h"
#include "Move.h"
#include "Renderer.h"
#include "TextureTable.h"
#include "Tile.h"

class Board
{
public:
    Board(TextureTable& table, Renderer& renderer);

    void draw();

    void highlightValidMoves(const Piece& piece);
    void resetMoveHighlight();
    void checkForPieceSelection(SDL_Point mousePosition, bool& pieceSelected,
                                PieceColor curentColorToMove);
    void checkForPromotionPieceSelection(SDL_Point mousePosition);
    void checkForPieceMovement(SDL_Point mousePosition, bool& pieceSelected,
                               PieceColor& curentColorToMove);
    Tile& getTileReferenceByPosition(std::pair<int, int> position);

    TileBoard& getTiles();
    bool promotingPawn() const;

private:
    TileBoard m_tileBoard{};
    BoardDrawer m_boardDrawer;
    GameLogic m_gameLogic;

    TextureTable& m_textureTable;
    Renderer& m_renderer;

    void initializeTile(TextureTable& table, int i, int j);
    void placePieceAtChosenTile(int newRow, int newColumn,
                                const std::optional<Piece>& piece);
    bool checkBoardTile(Tile& tile, int newRow, int newColumn,
                        bool& pieceSelected, PieceColor& currentColorToMove);
};

#endif
