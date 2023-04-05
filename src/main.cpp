#include "Window.h"

#include <iostream>

int main()
{
    Window window{ 640, 480 };

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
