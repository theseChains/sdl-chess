#ifndef TILE_COLOR_H
#define TILE_COLOR_H

enum class TileColor
{
    light,
    dark
};

TileColor getTileColor(int x, int y);

#endif
