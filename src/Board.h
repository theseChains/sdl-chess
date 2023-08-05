#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <functional>
#include <optional>
#include <vector>

#include "Aliases.h"
#include "BoardDrawer.h"
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
    std::optional<std::reference_wrapper<Tile>> findTile(
        std::pair<int, int> position);

    TileBoard& getTiles();
    bool promotingPawn() const;

private:
    TileBoard m_tileBoard{};
    Move m_lastMove{};
    TextureTable& m_textureTable;
    Renderer& m_renderer;
    std::vector<TileBoard> m_positions{};
    BoardDrawer m_boardDrawer;

    bool m_promotingPawn{ false };

    void initializeTile(TextureTable& table, int i, int j);
    void placePieceAtChosenTile(int newRow, int newColumn,
                                const std::optional<Piece>& piece);
    void checkBoardTile(Tile& tile, bool& keepGoing, int newRow, int newColumn,
                        bool& pieceSelected, PieceColor& currentColorToMove);
};

#endif
