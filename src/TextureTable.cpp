#include "TextureTable.h"

TextureTable::TextureTable(Renderer& renderer)
{
    SDL_Texture* pawnTexture{ renderer.loadTexture("../res/pawn.png") };
    SDL_Texture* knightTexture{ renderer.loadTexture("../res/knight.png") };
    SDL_Texture* bishopTexture{ renderer.loadTexture("../res/bishop.png") };
    SDL_Texture* rookTexture{ renderer.loadTexture("../res/rook.png") };
    SDL_Texture* queenTexture{ renderer.loadTexture("../res/queen.png") };
    SDL_Texture* kingTexture{ renderer.loadTexture("../res/king.png") };

    m_table[PieceType::pawn] = pawnTexture;
    m_table[PieceType::knight] = knightTexture;
    m_table[PieceType::bishop] = bishopTexture;
    m_table[PieceType::rook] = rookTexture;
    m_table[PieceType::queen] = queenTexture;
    m_table[PieceType::king] = kingTexture;
}

SDL_Texture* TextureTable::operator[](PieceType type)
{
    return m_table[type];
}
