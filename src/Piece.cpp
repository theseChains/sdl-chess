#include "Piece.h"

Piece::Piece(PieceType type, SDL_Texture* texture, std::pair<int, int> position)
    : m_type{ type }, m_texture{ texture }, m_position{ position }
{
    // todo: replace 100's with constants
    m_rectangle = { position.first, position.second, 100, 100 };
}

void Piece::draw(Renderer& renderer)
{
    renderer.copyTexture(m_texture, nullptr, &m_rectangle);
}
