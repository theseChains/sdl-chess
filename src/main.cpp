#include <SDL2/SDL.h>

#include <iostream>

int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "couldn't initialize sdl\n";
        return 1;
    }

    SDL_Window* window{ SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            640, 480, SDL_WINDOW_SHOWN) };

    if (window == nullptr)
    {
        std::cerr << "couldn't initialize the window\n";
        return 1;
    }

    bool run{ true };
    SDL_Event event{};
    while (run)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
                run = false;
        }
    }

    return 0;
}
