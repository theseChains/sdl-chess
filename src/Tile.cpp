#include "Tile.h"

Tile::Tile(TileColor color, const std::optional<Piece>& piece, std::pair<int, int> position)
    : m_color{ color }, m_piece{ piece }
{
    // todo: replace 100 with constants
    m_rectangle = { position.first, position.second, 100, 100 };
}

const SDL_Rect& Tile::getRectangle() const
{
    return m_rectangle;
}

SDL_Rect& Tile::getRectangle()
{
    return m_rectangle;
}

DrawColor Tile::getConvertedColor() const
{
    if (m_color == TileColor::light)
        return { 230, 230, 230, 255 };

    return { 150, 75, 0, 255 };
}
