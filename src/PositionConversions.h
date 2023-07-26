#ifndef POSITION_CONVERSIONS_H
#define POSITION_CONVERSIONS_H

#include <SDL2/SDL.h>

std::pair<int, int> getBoardPositionFromMouse(SDL_Point mousePosition);
std::pair<int, int> convertToBoardPosition(std::pair<int, int> position);
std::pair<int, int> convertToScreenPosition(std::pair<int, int> position);

#endif
