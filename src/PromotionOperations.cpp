#include "PromotionOperations.h"

#include <stdexcept>

#include "Constants.h"
#include "PositionConversions.h"

PromotionPieces initializePromotionPieces(TextureTable& textureTable,
                                          TileBoard& tileBoard,
                                          const Move& lastMove)
{
    auto [pawnRow, pawnColumn]{ lastMove.to };
    Piece pawn{ tileBoard[pawnRow][pawnColumn].getPiece().value() };
    PieceColor color{ pawn.getColor() };
    auto [tileRow,
          tileColumn]{ convertToScreenPosition({ pawnRow, pawnColumn }) };
    Piece queen{ PieceType::queen,
                 color,
                 textureTable[{ color, PieceType::queen }],
                 { getPromotionPieceScreenRow(tileRow, PieceType::queen, color),
                   tileColumn } };
    Piece rook{ PieceType::rook,
                color,
                textureTable[{ color, PieceType::rook }],
                { getPromotionPieceScreenRow(tileRow, PieceType::rook, color),
                  tileColumn } };
    Piece bishop{ PieceType::bishop,
                  color,
                  textureTable[{ color, PieceType::bishop }],
                  { getPromotionPieceScreenRow(tileRow, PieceType::bishop,
                                               color),
                    tileColumn } };
    Piece knight{ PieceType::knight,
                  color,
                  textureTable[{ color, PieceType::knight }],
                  { getPromotionPieceScreenRow(tileRow, PieceType::knight,
                                               color),
                    tileColumn } };

    return { queen, rook, bishop, knight };
}

int getPromotionPieceScreenRow(int tileRow, PieceType type, PieceColor color)
{
    int pieceScreenRow{ tileRow };
    int direction{ color == PieceColor::white ? 1 : -1 };
    int pawnTileDifference{};
    switch (type)
    {
        case PieceType::queen:
            pawnTileDifference = constants::promotionQueenPositionDifference;
            break;
        case PieceType::rook:
            pawnTileDifference = constants::promotionRookPositionDifference;
            break;
        case PieceType::bishop:
            pawnTileDifference = constants::promotionBishopPositionDifference;
            break;
        case PieceType::knight:
            pawnTileDifference = constants::promotionKnightPositionDifference;
            break;
        default:
            throw std::runtime_error{ "incorrect promotion piece" };
    }

    pieceScreenRow +=
        pawnTileDifference * direction * constants::screenPositionMultiplier;

    return pieceScreenRow;
}

bool pawnIsPromoting(TileBoard& board, int pawnRow, int pawnColumn)
{
    Piece pawn{ board[pawnRow][pawnColumn].getPiece().value() };
    if ((pawn.getColor() == PieceColor::white &&
         pawnRow != constants::topRow) ||
        (pawn.getColor() == PieceColor::black &&
         pawnRow != constants::bottomRow))
        return false;

    return true;
}

void handlePromotedPieceSelection(Tile& pawnTile, TextureTable& textureTable,
                                  int boardRow, int pawnRow, int pawnColumn)
{
    PieceColor color{ pawnTile.getPiece()->getColor() };
    pawnTile.removePiece();
    std::pair<int, int> newPieceScreenPosition{ convertToScreenPosition(
        { pawnRow, pawnColumn }) };
    if (std::abs(boardRow - pawnRow) ==
        constants::promotionQueenPositionDifference)
    {
        Piece queen{ PieceType::queen, color,
                     textureTable[{ color, PieceType::queen }],
                     newPieceScreenPosition };
        pawnTile.placePiece(queen);
    }
    else if (std::abs(boardRow - pawnRow) ==
             constants::promotionRookPositionDifference)
    {
        Piece rook{ PieceType::rook, color,
                    textureTable[{ color, PieceType::rook }],
                    newPieceScreenPosition };
        pawnTile.placePiece(rook);
    }
    else if (std::abs(boardRow - pawnRow) ==
             constants::promotionBishopPositionDifference)
    {
        Piece bishop{ PieceType::bishop, color,
                      textureTable[{ color, PieceType::bishop }],
                      newPieceScreenPosition };
        pawnTile.placePiece(bishop);
    }
    else if (std::abs(boardRow - pawnRow) ==
             constants::promotionKnightPositionDifference)
    {
        Piece knight{ PieceType::knight, color,
                      textureTable[{ color, PieceType::knight }],
                      newPieceScreenPosition };
        pawnTile.placePiece(knight);
    }
}
