#include "UserInput.h"

void UserInput::handleEvent(SDL_Event& event, Board& board)
{
    if (event.type == SDL_MOUSEMOTION)
        m_mousePosition = { event.motion.x, event.motion.y };

    if (event.type == SDL_MOUSEBUTTONDOWN && board.promotingPawn() &&
        event.button.button == SDL_BUTTON_LEFT)
    {
        board.checkForPromotionPieceSelection(m_mousePosition);
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN && !m_pieceSelected &&
             event.button.button == SDL_BUTTON_LEFT)
    {
        board.checkForPieceSelection(m_mousePosition, m_pieceSelected,
                                     m_currentColorToMove);
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN && m_pieceSelected &&
             event.button.button == SDL_BUTTON_LEFT)
    {
        board.checkForPieceMovement(m_mousePosition, m_pieceSelected,
                                    m_currentColorToMove);
    }
}
