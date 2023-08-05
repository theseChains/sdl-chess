#include "Tile.h"

#include "Constants.h"
#include "PositionConversions.h"

Tile::Tile(TileColor color, const std::optional<Piece>& piece,
           std::pair<int, int> position)
    : m_color{ color }, m_piece{ piece }, m_position{ position }
{
    auto [rectangleX, rectangleY]{ convertToRectanglePosition(position) };
    m_rectangle = { rectangleX, rectangleY, constants::tileWidth,
                    constants::tileHeight };
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
        return colors::lightTile;

    return colors::darkTile;
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

bool Tile::isHighlighted() const
{
    return m_isHighlighted;
}

void Tile::removePiece()
{
    m_piece = std::nullopt;
}

void Tile::placePiece(const Piece& piece)
{
    m_piece = piece;
}

void Tile::highlight()
{
    m_isHighlighted = true;
}

void Tile::dehighlight()
{
    m_isHighlighted = false;
}

bool Tile::operator==(const Tile& other) const
{
    if (getPiece() && other.getPiece())
        return (m_piece.value() == other.m_piece.value() &&
                m_position == other.m_position);
    else if (!getPiece() && !other.getPiece())
        return (m_position == other.m_position);

    return false;
}
