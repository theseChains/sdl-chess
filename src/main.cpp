#include "Constants.h"
#include "Window.h"

#include <iostream>

int main()
{
    Window window{ constants::windowWidth, constants::windowHeight };
    SDL_Renderer* renderer{ SDL_CreateRenderer(window.getWindow(), -1, SDL_RENDERER_SOFTWARE) };

    SDL_Rect rectangle{ 0, 0, 100, 100 };

    bool run{ true };
    SDL_Event event{};
    while (run)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
                run = false;

            SDL_SetRenderDrawColor(renderer, 120, 120, 230, 255);
            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &rectangle);
            SDL_RenderDrawRect(renderer, &rectangle);

            SDL_RenderPresent(renderer);
        }
    }

    return 0;
}
