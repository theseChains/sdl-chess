#include "Piece.h"

#include "Constants.h"

Piece::Piece(PieceType type, PieceColor color, SDL_Texture* texture, std::pair<int, int> position)
    : m_type{ type }, m_color{ color}, m_texture{ texture }, m_position{ position }
{
    m_rectangle = { position.first, position.second, constants::windowWidth / constants::boardSize,
        constants::windowHeight / constants::boardSize };
}

void Piece::draw(Renderer& renderer)
{
    renderer.copyTexture(m_texture, nullptr, &m_rectangle);
}

SDL_Rect& Piece::getRectangle()
{
    return m_rectangle;
}

void Piece::setPosition(std::pair<int, int> position)
{
    m_position = position;
    m_rectangle.x = position.first;
    m_rectangle.y = position.second;
}

PieceType Piece::getType() const
{
    return m_type;
}

std::pair<int, int> Piece::getPosition() const
{
    return m_position;
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
