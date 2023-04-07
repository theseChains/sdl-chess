#include "Piece.h"

#include "Constants.h"

Piece::Piece(PieceType type, PieceColor color, SDL_Texture* texture, std::pair<int, int> position)
    : m_type{ type }, m_color{ color}, m_texture{ texture }, m_position{ position }
{
    // todo: replace 100's with constants
    m_rectangle = { position.first, position.second, constants::windowWidth / constants::boardSize,
        constants::windowHeight / constants::boardSize };
}

void Piece::draw(Renderer& renderer)
{
    renderer.copyTexture(m_texture, nullptr, &m_rectangle);
}
