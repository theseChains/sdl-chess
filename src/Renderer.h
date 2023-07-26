#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

#include "DrawColor.h"

class Renderer
{
public:
    Renderer(SDL_Window* window, int index, unsigned int flags);

    void clear();
    void present();

    void setDrawColor(unsigned char red, unsigned char green,
                      unsigned char blue, unsigned char alpha);
    void setDrawColor(const DrawColor& color);

    void fillRect(const SDL_Rect& rectangle);
    void drawRect(const SDL_Rect& rectangle);
    void fillAndDrawRect(const SDL_Rect& rectangle);

    SDL_Texture* loadTexture(const std::string& path);
    // source and destination can be null, hence pass by pointer
    void copyTexture(SDL_Texture* texture, const SDL_Rect* source,
                     const SDL_Rect* destination);

    ~Renderer();

private:
    SDL_Renderer* m_renderer{};
};

#endif
