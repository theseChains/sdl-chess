#include "Renderer.h"

Renderer::Renderer(SDL_Window* window, int index, unsigned int flags)
{
    m_renderer = SDL_CreateRenderer(window, index, flags);
}

void Renderer::clear()
{
    SDL_RenderClear(m_renderer);
}

void Renderer::present()
{
    SDL_RenderPresent(m_renderer);
}

void Renderer::setDrawColor(unsigned char red, unsigned char green,
                            unsigned char blue, unsigned char alpha)
{
    SDL_SetRenderDrawColor(m_renderer, red, green, blue, alpha);
}

void Renderer::setDrawColor(const DrawColor& color)
{
    SDL_SetRenderDrawColor(m_renderer, color.red, color.green, color.blue,
                           color.alpha);
}

void Renderer::fillRect(const SDL_Rect& rectangle)
{
    SDL_RenderFillRect(m_renderer, &rectangle);
}

void Renderer::drawRect(const SDL_Rect& rectangle)
{
    SDL_RenderDrawRect(m_renderer, &rectangle);
}

void Renderer::fillAndDrawRect(const SDL_Rect& rectangle)
{
    fillRect(rectangle);
    drawRect(rectangle);
}

void Renderer::drawPiece(const Piece& piece)
{
    copyTexture(piece.getTexture(), nullptr, &piece.getRectangle());
}

void Renderer::drawTile(const Tile& tile)
{
    setDrawColor(tile.getConvertedColor());
    fillAndDrawRect(tile.getRectangle());
}

SDL_Texture* Renderer::loadTexture(const std::string& path)
{
    return IMG_LoadTexture(m_renderer, path.data());
}

void Renderer::copyTexture(SDL_Texture* texture, const SDL_Rect* source,
                           const SDL_Rect* destination)
{
    SDL_RenderCopy(m_renderer, texture, source, destination);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_renderer);
}
