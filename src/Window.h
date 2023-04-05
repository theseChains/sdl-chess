#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

class Window
{
public:
    Window(int width, int height);

private:
    int m_width{};
    int m_height{};
};

#endif
