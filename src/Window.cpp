#include "Window.h"

#include <stdexcept>

Window::Window(int width, int height) : m_width{ width }, m_height{ height }
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        throw std::runtime_error{ "Window::Window() - could not initialize sdl" };

    SDL_Window* window{ SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            width, height, SDL_WINDOW_SHOWN) };

    if (window == nullptr)
        throw std::runtime_error{ "Window::Window() - could not initialize the sdl window" };

    m_window = window;
}

int Window::getWidth() const
{
    return m_width;
}

int Window::getHeight() const
{
    return m_height;
}

std::pair<int, int> Window::getSize() const
{
    return { m_width, m_height };
}

SDL_Window* Window::getWindow() const
{
    return m_window;
}

Window::~Window()
{
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
