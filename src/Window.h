#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

#include <tuple>

class Window
{
public:
    Window(int width, int height);

    int getWidth() const;
    int getHeight() const;
    SDL_Window* getWindow() const;

    ~Window();

private:
    SDL_Window* m_window{};
    int m_width{};
    int m_height{};
};

#endif
