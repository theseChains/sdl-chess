#include "Piece.h"

#include "Constants.h"

Piece::Piece(PieceType type, PieceColor color, SDL_Texture* texture, std::pair<int, int> position)
    : m_type{ type }, m_color{ color}, m_texture{ texture }, m_position{ position }
{
    // switch x and y for rectangle position
    m_rectangle = { position.second, position.first, constants::windowWidth / constants::boardSize,
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
    // switch the order for proper rendering
    m_rectangle.x = position.second;
    m_rectangle.y = position.first;
}

void Piece::setBoardPosition(std::pair<int, int> position)
{
    m_position = { position.first * 100, position.second * 100 };
    // switch the order for proper rendering
    m_rectangle.x = position.second * 100;
    m_rectangle.y = position.first * 100;
}

void Piece::setPawnMovedTwoSquares()
{
    m_hasMovedTwoSquares = true;
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
    return { m_position.first / 100, m_position.second / 100 };
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

bool Piece::canBeTakenEnPassant() const
{
    return m_hasMovedTwoSquares && m_type == PieceType::pawn;
}

bool Piece::hasMoved() const
{
    return m_hasMoved;
}
