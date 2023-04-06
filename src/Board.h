#ifndef BOARD_H
#define BOARD_H

#include "Renderer.h"
#include "Tile.h"

#include <array>

class Board
{
public:
    Board();

    void draw(Renderer& renderer);

private:
    std::array<std::array<Tile, 8>, 8> m_board;
};

#endif
