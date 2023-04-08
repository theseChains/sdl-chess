#include "Application.h"

#include <iostream>

Application::Application()
    : m_window{ constants::windowWidth, constants::windowHeight }
    , m_renderer{ m_window.getWindow(), -1, SDL_RENDERER_SOFTWARE }
    , m_textures{ m_renderer }
    , m_board{ m_textures }
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

SDL_Point mousePosition{};
bool pieceSelected{ false };

void Application::processInput(SDL_Event& event, bool& keepRunning)
{
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
            keepRunning = false;

        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
            keepRunning = false;

        if (event.type == SDL_MOUSEMOTION)
            mousePosition = { event.motion.x, event.motion.y };

        if (event.type == SDL_MOUSEBUTTONDOWN && !pieceSelected &&
                event.button.button == SDL_BUTTON_LEFT)
            m_board.checkForPieceSelection(mousePosition, pieceSelected);
        else if (event.type == SDL_MOUSEBUTTONDOWN && pieceSelected &&
                event.button.button == SDL_BUTTON_LEFT)
            m_board.checkForPieceMovement(mousePosition, pieceSelected);
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
