#ifndef BOARD_H
#define BOARD_H

#include "Renderer.h"
#include "TextureTable.h"
#include "Tile.h"

#include <array>

class Board
{
public:
    Board(TextureTable& table);

    void draw(Renderer& renderer);

    void checkForPieceSelection(SDL_Point mousePosition, bool& pieceSelected);
    void checkForPieceMovement(SDL_Point mousePosition, bool& pieceSelected);
    std::array<std::array<Tile, 8>, 8>& getTiles();

private:
    std::array<std::array<Tile, 8>, 8> m_board;

    void initializeTile(TextureTable& table, int i, int j);
};

#endif
