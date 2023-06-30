#ifndef BOARD_H
#define BOARD_H

#include "Renderer.h"
#include "TextureTable.h"
#include "Tile.h"

#include <array>
#include <functional>
#include <optional>

class Board
{
public:
    Board(TextureTable& table);

    void draw(Renderer& renderer);

    void checkForPieceSelection(SDL_Point mousePosition, bool& pieceSelected,
            PieceColor curentColorToMove);
    void checkForPieceMovement(SDL_Point mousePosition, bool& pieceSelected,
            PieceColor& curentColorToMove);
    std::optional<std::reference_wrapper<Tile>> findTile(std::pair<int, int> position);
    std::array<std::array<Tile, 8>, 8>& getTiles();

private:
    std::array<std::array<Tile, 8>, 8> m_board;

    void initializeTile(TextureTable& table, int i, int j);
    void placePieceAtChosenTile(int newRow, int newColumn, const std::optional<Piece>& piece);
    void checkBoardTile(Tile& tile, bool& keepGoing, int newRow, int newColumn,
            bool& pieceSelected, PieceColor& currentColorToMove);
};

#endif
