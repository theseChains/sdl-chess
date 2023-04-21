#include "Tile.h"

#include "Constants.h"

Tile::Tile(TileColor color, const std::optional<Piece>& piece, std::pair<int, int> position)
    : m_color{ color }, m_piece{ piece }, m_position{ position }
{
    // switch the x and y for rectangle position
    m_rectangle = { position.second, position.first, constants::windowWidth / constants::boardSize,
        constants::windowHeight / constants::boardSize };
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

const std::optional<Piece>& Tile::getPiece() const
{
    return m_piece;
}

std::optional<Piece>& Tile::getPiece()
{
    return m_piece;
}

std::pair<int, int> Tile::getPosition() const
{
    return m_position;
}

void Tile::removePiece()
{
    m_piece = std::nullopt;
}

void Tile::placePiece(const Piece& piece)
{
    m_piece = piece;
}
