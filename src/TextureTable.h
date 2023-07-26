#ifndef TEXTURE_TABLE_H
#define TEXTURE_TABLE_H

#include <SDL2/SDL.h>

#include <unordered_map>

#include "Colors.h"
#include "PieceType.h"
#include "Renderer.h"

class TextureTable
{
public:
    TextureTable(Renderer& renderer);
    SDL_Texture* operator[](const std::pair<PieceColor, PieceType>& pieceInfo);

private:
    struct PairHash
    {
        std::size_t operator()(
            const std::pair<PieceColor, PieceType>& pair) const
        {
            return std::hash<PieceColor>()(pair.first) ^
                   std::hash<PieceType>()(pair.second);
        }
    };

    std::unordered_map<std::pair<PieceColor, PieceType>, SDL_Texture*, PairHash>
        m_table{};
};

#endif
