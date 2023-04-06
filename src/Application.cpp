#include "Application.h"

Application::Application()
    : m_window{ constants::windowWidth, constants::windowHeight }
    , m_renderer{ m_window.getWindow(), -1, SDL_RENDERER_SOFTWARE }
{
}

void Application::run()
{
    bool keepRunning{ true };
    SDL_Event event{};
    while (keepRunning)
    {
        processInput(event, keepRunning);
        update();
        draw();
    }
}

void Application::processInput(SDL_Event& event, bool& keepRunning)
{
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
            keepRunning = false;

        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
            keepRunning = false;
    }
}

void Application::update()
{
}

void Application::draw()
{
    m_renderer.clear();
    m_board.draw(m_renderer);
    m_renderer.present();
}
