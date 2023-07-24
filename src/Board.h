#ifndef BOARD_H
#define BOARD_H

#include "Move.h"
#include "Renderer.h"
#include "TextureTable.h"
#include "Tile.h"

#include <array>
#include <functional>
#include <optional>
#include <vector>

class Board
{
public:
    Board(TextureTable& table, Renderer& renderer);

    void draw();

    void checkForPieceSelection(SDL_Point mousePosition, bool& pieceSelected,
            PieceColor curentColorToMove);
    void checkForPromotionPieceSelection(SDL_Point mousePosition);
    void checkForPieceMovement(SDL_Point mousePosition, bool& pieceSelected,
            PieceColor& curentColorToMove);
    std::optional<std::reference_wrapper<Tile>> findTile(std::pair<int, int> position);

    std::array<std::array<Tile, 8>, 8>& getTiles();
    bool promotingPawn() const;

private:
    std::array<std::array<Tile, 8>, 8> m_board{};
    Move m_lastMove{};
    TextureTable& m_textureTable;
    Renderer& m_renderer;
    std::vector<std::array<std::array<Tile, 8>, 8>> m_positions{};

    bool m_promotingPawn{ false };

    void initializeTile(TextureTable& table, int i, int j);
    void placePieceAtChosenTile(int newRow, int newColumn, const std::optional<Piece>& piece);
    void checkBoardTile(Tile& tile, bool& keepGoing, int newRow, int newColumn,
            bool& pieceSelected, PieceColor& currentColorToMove);
};

#endif
