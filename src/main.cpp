#include "Constants.h"
#include "Window.h"

#include <SDL2/SDL_image.h>

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

    SDL_Texture* image{ IMG_LoadTexture(renderer, "../res/pawn.png") };
    int imageWidth{};
    int imageHeight{};
    SDL_QueryTexture(image, nullptr, nullptr, &imageWidth, &imageHeight);

    std::array<std::array<SDL_Rect, 8>, 8> pieces{};
    for (int i{ 0 }; i < 8; ++i)
        for (int j{ 0 }; j < 8; ++j)
            pieces[i][j] = { i * 100, j * 100, imageWidth, imageHeight };

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
                    if ((i + j) % 2 == 0)
                        SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
                    else
                        SDL_SetRenderDrawColor(renderer, 150, 75, 0, 255);

                    SDL_RenderFillRect(renderer, &board[i][j]);
                    SDL_RenderDrawRect(renderer, &board[i][j]);

                    SDL_RenderCopy(renderer, image, nullptr, &pieces[i][j]);
                }
            }

            SDL_RenderPresent(renderer);
        }
    }

    return 0;
}
