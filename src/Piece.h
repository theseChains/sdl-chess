#ifndef PIECE_H
#define PIECE_H

#include "PieceType.h"
#include "Renderer.h"

#include <SDL2/SDL_image.h>

#include <tuple>

class Piece
{
public:
    Piece(PieceType type, SDL_Texture* texture, std::pair<int, int> position);

    void draw(Renderer& renderer);

private:
    PieceType m_type{};
    SDL_Rect m_rectangle{};
    SDL_Texture* m_texture{};
    std::pair<int, int> m_position{};
};

#endif