#include "Constants.h"
#include "Window.h"

#include <array>
#include <iostream>

int main()
{
    Window window{ constants::windowWidth, constants::windowHeight };
    SDL_Renderer* renderer{ SDL_CreateRenderer(window.getWindow(), -1, SDL_RENDERER_SOFTWARE) };

    std::array<std::array<SDL_Rect, 8>, 8> board{};
    for (int i{ 0 }; i < 8; ++i)
        for (int j{ 0 }; j < 8; ++j)
            board[i][j] = { i * 100, j * 100, 100, 100 };

    bool run{ true };
    SDL_Event event{};
    while (run)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
                run = false;

            SDL_RenderClear(renderer);

            for (unsigned char i{ 0 }; i < 8; ++i)
            {
                for (unsigned char j{ 0 }; j < 8; ++j)
                {
                    SDL_SetRenderDrawColor(renderer, i * 32, j * 32, 255, 255);
                    SDL_RenderFillRect(renderer, &board[i][j]);
                    SDL_RenderDrawRect(renderer, &board[i][j]);
                }
            }

            SDL_RenderPresent(renderer);
        }
    }

    return 0;
}
