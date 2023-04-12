#include "TextureTable.h"

TextureTable::TextureTable(Renderer& renderer)
{
    SDL_Texture* whitePawnTexture{ renderer.loadTexture("../res/pawn.png") };
    SDL_Texture* whiteKnightTexture{ renderer.loadTexture("../res/knight.png") };
    SDL_Texture* whiteBishopTexture{ renderer.loadTexture("../res/bishop.png") };
    SDL_Texture* whiteRookTexture{ renderer.loadTexture("../res/rook.png") };
    SDL_Texture* whiteQueenTexture{ renderer.loadTexture("../res/queen.png") };
    SDL_Texture* whiteKingTexture{ renderer.loadTexture("../res/king.png") };

    SDL_Texture* blackPawnTexture{ renderer.loadTexture("../res/blackPawn.png") };
    SDL_Texture* blackKnightTexture{ renderer.loadTexture("../res/blackKnight.png") };
    SDL_Texture* blackBishopTexture{ renderer.loadTexture("../res/blackBishop.png") };
    SDL_Texture* blackRookTexture{ renderer.loadTexture("../res/blackRook.png") };
    SDL_Texture* blackQueenTexture{ renderer.loadTexture("../res/blackQueen.png") };
    SDL_Texture* blackKingTexture{ renderer.loadTexture("../res/blackKing.png") };

    m_table[{ PieceColor::white, PieceType::pawn }] = whitePawnTexture;
    m_table[{ PieceColor::white, PieceType::knight }] = whiteKnightTexture;
    m_table[{ PieceColor::white, PieceType::bishop }] = whiteBishopTexture;
    m_table[{ PieceColor::white, PieceType::rook }] = whiteRookTexture;
    m_table[{ PieceColor::white, PieceType::queen }] = whiteQueenTexture;
    m_table[{ PieceColor::white, PieceType::king }] = whiteKingTexture;

    m_table[{ PieceColor::black, PieceType::pawn }] = blackPawnTexture;
    m_table[{ PieceColor::black, PieceType::knight }] = blackKnightTexture;
    m_table[{ PieceColor::black, PieceType::bishop }] = blackBishopTexture;
    m_table[{ PieceColor::black, PieceType::rook }] = blackRookTexture;
    m_table[{ PieceColor::black, PieceType::queen }] = blackQueenTexture;
    m_table[{ PieceColor::black, PieceType::king }] = blackKingTexture;
}

SDL_Texture* TextureTable::operator[](const std::pair<PieceColor, PieceType>& pieceInfo)
{
    return m_table[pieceInfo];
}
