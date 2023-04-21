#include "Application.h"

#include <cmath>
#include <iostream>

Application::Application()
    : m_window{ constants::windowWidth, constants::windowHeight }
    , m_renderer{ m_window.getWindow(), -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_SOFTWARE }
    , m_textures{ m_renderer }
    , m_board{ m_textures }
    , m_userInput{}
{
}

void Application::run()
{
    bool keepRunning{ true };
    while (keepRunning)
    {
        processInput(keepRunning);
        draw();
    }
}

void Application::processInput(bool& keepRunning)
{
    SDL_Event event{};
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
            keepRunning = false;

        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
            keepRunning = false;

        m_userInput.handleEvent(event, m_board);
    }
}

void Application::draw()
{
    m_renderer.clear();
    m_board.draw(m_renderer);
    m_renderer.present();
}
