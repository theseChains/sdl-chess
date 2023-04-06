#ifndef TILE_H
#define TILE_H

#include "DrawColor.h"
#include "Piece.h"
#include "TileColor.h"

#include <SDL2/SDL.h>

#include <optional>
#include <tuple>

class Tile
{
public:
    // this one doesn't quite make sense, gotta find a way around
    Tile() = default;
    Tile(TileColor color, const std::optional<Piece>& piece, std::pair<int, int> position);

    const SDL_Rect& getRectangle() const;
    SDL_Rect& getRectangle();
    DrawColor getConvertedColor() const;
    const std::optional<Piece>& getPiece() const;
    std::optional<Piece> getPiece();

private:
    SDL_Rect m_rectangle{};
    TileColor m_color{};
    std::optional<Piece> m_piece{};
};

#endif