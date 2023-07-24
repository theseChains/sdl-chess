#ifndef TILE_H
#define TILE_H

#include "DrawColor.h"
#include "Piece.h"
#include "Colors.h"

#include <SDL2/SDL.h>

#include <optional>
#include <tuple>

class Tile
{
public:
    // todo: remove this
    Tile() = default;
    Tile(TileColor color, const std::optional<Piece>& piece, std::pair<int, int> position);

    const SDL_Rect& getRectangle() const;
    SDL_Rect& getRectangle();
    DrawColor getConvertedColor() const;
    const std::optional<Piece>& getPiece() const;
    std::optional<Piece>& getPiece();
    std::pair<int, int> getPosition() const;

    void removePiece();
    void placePiece(const Piece& piece);

    bool operator==(const Tile& other) const;

private:
    SDL_Rect m_rectangle{};
    TileColor m_color{};
    std::optional<Piece> m_piece{};
    std::pair<int, int> m_position{};
};

#endif
