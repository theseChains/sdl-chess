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

    m_table[{ PieceColor::white, PieceType::wPawn }] = whitePawnTexture;
    m_table[{ PieceColor::white, PieceType::wKnight }] = whiteKnightTexture;
    m_table[{ PieceColor::white, PieceType::wBishop }] = whiteBishopTexture;
    m_table[{ PieceColor::white, PieceType::wRook }] = whiteRookTexture;
    m_table[{ PieceColor::white, PieceType::wQueen }] = whiteQueenTexture;
    m_table[{ PieceColor::white, PieceType::wKing }] = whiteKingTexture;

    m_table[{ PieceColor::black, PieceType::bPawn }] = blackPawnTexture;
    m_table[{ PieceColor::black, PieceType::bKnight }] = blackKnightTexture;
    m_table[{ PieceColor::black, PieceType::bBishop }] = blackBishopTexture;
    m_table[{ PieceColor::black, PieceType::bRook }] = blackRookTexture;
    m_table[{ PieceColor::black, PieceType::bQueen }] = blackQueenTexture;
    m_table[{ PieceColor::black, PieceType::bKing }] = blackKingTexture;
}

SDL_Texture* TextureTable::operator[](const std::pair<PieceColor, PieceType>& pieceInfo)
{
    return m_table[pieceInfo];
}
