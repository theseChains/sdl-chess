#ifndef TEXTURE_TABLE_H
#define TEXTURE_TABLE_H

#include "PieceType.h"
#include "Renderer.h"

#include <SDL2/SDL.h>

#include <unordered_map>

class TextureTable
{
public:
    TextureTable(Renderer& renderer);
    SDL_Texture* operator[](PieceType type);

private:
    std::unordered_map<PieceType, SDL_Texture*> m_table{};
};

#endif
