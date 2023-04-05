#include "Window.h"

#include <iostream>
#include <exception>

Window::Window(int width, int height) : m_width{ width }, m_height{ height }
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        throw std::runtime_error{ "could not initialize sdl" };

    SDL_Window* window{ SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            width, height, SDL_WINDOW_SHOWN) };

    if (window == nullptr)
        throw std::runtime_error{ "could not initialize the sdl window" };
}
