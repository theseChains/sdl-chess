#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Constants.h"
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

    void processInput(SDL_Event& event, bool& keepRunning);
    void update();
    void draw();
};

#endif