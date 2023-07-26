#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Board.h"
#include "Constants.h"
#include "Renderer.h"
#include "TextureTable.h"
#include "UserInput.h"
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
    UserInput m_userInput;

    void processInput(bool& keepRunning);
    void draw();
};

#endif
