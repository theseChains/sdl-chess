#include "Constants.h"
#include "Renderer.h"
#include "Window.h"

#include <SDL2/SDL_image.h>

#include <array>
#include <iostream>

int main()
{
    Window window{ constants::windowWidth, constants::windowHeight };
    Renderer renderer{ window.getWindow(), -1, SDL_RENDERER_SOFTWARE };

    std::array<std::array<SDL_Rect, 8>, 8> board{};
    for (int i{ 0 }; i < 8; ++i)
        for (int j{ 0 }; j < 8; ++j)
            board[i][j] = { i * 100, j * 100, 100, 100 };

    SDL_Texture* image{ renderer.loadTexture("../res/knight.png") };
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

            if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
                run = false;
        }

        renderer.clear();

        for (unsigned char i{ 0 }; i < 8; ++i)
        {
            for (unsigned char j{ 0 }; j < 8; ++j)
            {
                if ((i + j) % 2 == 0)
                    renderer.setDrawColor(230, 230, 230, 255);
                else
                    renderer.setDrawColor(150, 75, 0, 255);

                renderer.fillAndDrawRect(board[i][j]);

                renderer.copyTexture(image, nullptr, &pieces[i][j]);
            }
        }

        renderer.present();
    }

    return 0;
}
