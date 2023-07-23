#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <SDL2/SDL.h>

#include "Board.h"
#include "Colors.h"

class UserInput
{
public:
    UserInput() = default;

    void handleEvent(SDL_Event& event, Board& board);

private:
    SDL_Point m_mousePosition{};
    // could probably move those variables out of here..
    bool m_pieceSelected{ false };
    PieceColor m_currentColorToMove{ PieceColor::white };
};

#endif
