#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Board.h"
#include "Constants.h"
#include "TextureTable.h"
#include "Renderer.h"
#include "Window.h"

class Application
{
public:
    Application();

    void run();

private:
    Window m_window;
    Renderer m_renderer;
    TextureTable m_textures;
    Board m_board;

    void processInput(SDL_Event& event, bool& keepRunning);
    void update();
    void draw();
};

#endif
