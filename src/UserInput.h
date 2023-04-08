#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <SDL2/SDL.h>

#include "Board.h"

class UserInput
{
public:
    UserInput() = default;

    void handleEvent(SDL_Event& event, Board& board);

private:
    SDL_Point m_mousePosition{};
    bool m_pieceSelected{ false };
};

#endif
