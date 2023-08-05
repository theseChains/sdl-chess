#include "Piece.h"

#include "Constants.h"
#include "PositionConversions.h"

Piece::Piece(PieceType type, PieceColor color, SDL_Texture* texture,
             std::pair<int, int> position)
    : m_type{ type },
      m_color{ color },
      m_texture{ texture },
      m_position{ position }
{
    auto [rectangleX, rectangleY]{ convertToRectanglePosition(position) };
    m_rectangle = { rectangleX, rectangleY, constants::tileWidth,
                    constants::tileHeight };
}

SDL_Rect& Piece::getRectangle()
{
    return m_rectangle;
}

const SDL_Rect& Piece::getRectangle() const
{
    return m_rectangle;
}

SDL_Texture* Piece::getTexture() const
{
    return m_texture;
}

void Piece::setPosition(std::pair<int, int> position)
{
    m_position = position;
    auto [rectangleX, rectangleY]{ convertToRectanglePosition(position) };
    m_rectangle.x = rectangleX;
    m_rectangle.y = rectangleY;
}

void Piece::setPositionFromBoardPosition(std::pair<int, int> position)
{
    position = convertToScreenPosition(position);
    setPosition(position);
}

void Piece::setHasMoved()
{
    m_hasMoved = true;
}

PieceType Piece::getType() const
{
    return m_type;
}

std::pair<int, int> Piece::getPosition() const
{
    return m_position;
}

std::pair<int, int> Piece::getBoardPosition() const
{
    return convertToBoardPosition(m_position);
}

PieceColor Piece::getColor() const
{
    return m_color;
}

void Piece::select()
{
    m_isSelected = true;
}

void Piece::deselect()
{
    m_isSelected = false;
}

bool Piece::isSelected() const
{
    return m_isSelected;
}

bool Piece::hasMoved() const
{
    return m_hasMoved;
}

bool Piece::operator==(const Piece& other) const
{
    return (m_type == other.m_type && m_color == other.m_color &&
            m_position == other.m_position);
}
