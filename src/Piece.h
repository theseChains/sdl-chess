#ifndef PIECE_H
#define PIECE_H

#include <SDL2/SDL_image.h>

#include <tuple>

#include "Colors.h"
#include "PieceType.h"

class Piece
{
public:
    Piece(PieceType type, PieceColor color, SDL_Texture* texture,
          std::pair<int, int> position);

    SDL_Rect& getRectangle();
    const SDL_Rect& getRectangle() const;
    SDL_Texture* getTexture() const;
    PieceType getType() const;
    std::pair<int, int> getPosition() const;
    std::pair<int, int> getBoardPosition() const;
    PieceColor getColor() const;
    bool hasMoved() const;

    void setPosition(std::pair<int, int> position);
    void setPositionFromBoardPosition(std::pair<int, int> position);
    void setHasMoved();

    void select();
    void deselect();
    bool isSelected() const;

    bool operator==(const Piece& other) const;

private:
    PieceType m_type{};
    PieceColor m_color{};
    SDL_Rect m_rectangle{};
    SDL_Texture* m_texture{};
    std::pair<int, int> m_position{};
    bool m_isSelected{ false };

    bool m_hasMoved{ false };
};

#endif
