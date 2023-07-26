#include "PromotionOperations.h"

#include "Constants.h"

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

void drawPromotionPieces(const TileBoard& board, TextureTable& textureTable,
                         Renderer& renderer, const Move& lastMove)
{
    auto [pawnRow, pawnColumn]{ lastMove.to };
    Piece pawn{ board[pawnRow][pawnColumn].getPiece().value() };
    PieceColor color{ pawn.getColor() };
    int tileRow{ pawnRow * 100 };
    int tileColumn{ pawnColumn * 100 };
    Piece queen{ PieceType::queen,
                 color,
                 textureTable[{ color, PieceType::queen }],
                 { tileRow, tileColumn } };
    Piece rook{ PieceType::rook,
                color,
                textureTable[{ color, PieceType::rook }],
                { tileRow + (color == PieceColor::white ? 100 : -100),
                  tileColumn } };
    Piece bishop{ PieceType::bishop,
                  color,
                  textureTable[{ color, PieceType::bishop }],
                  { tileRow + (color == PieceColor::white ? 200 : -200),
                    tileColumn } };
    Piece knight{ PieceType::knight,
                  color,
                  textureTable[{ color, PieceType::knight }],
                  { tileRow + (color == PieceColor::white ? 300 : -300),
                    tileColumn } };

    renderer.setDrawColor(colors::white);
    renderer.fillAndDrawRect(
        { queen.getPosition().second, queen.getPosition().first,
          constants::windowWidth / constants::boardSize,
          constants::windowHeight / constants::boardSize });
    renderer.fillAndDrawRect(
        { rook.getPosition().second, rook.getPosition().first,
          constants::windowWidth / constants::boardSize,
          constants::windowHeight / constants::boardSize });
    renderer.fillAndDrawRect(
        { bishop.getPosition().second, bishop.getPosition().first,
          constants::windowWidth / constants::boardSize,
          constants::windowHeight / constants::boardSize });
    renderer.fillAndDrawRect(
        { knight.getPosition().second, knight.getPosition().first,
          constants::windowWidth / constants::boardSize,
          constants::windowHeight / constants::boardSize });

    queen.draw(renderer);
    rook.draw(renderer);
    bishop.draw(renderer);
    knight.draw(renderer);
}

void handlePromotedPieceSelection(Tile& pawnTile, TextureTable& textureTable,
                                  int boardRow, int pawnRow, int pawnColumn)
{
    PieceColor color{ pawnTile.getPiece()->getColor() };
    pawnTile.removePiece();
    if (boardRow == pawnRow)
    {
        Piece queen{ PieceType::queen,
                     color,
                     textureTable[{ color, PieceType::queen }],
                     { pawnRow * 100, pawnColumn * 100 } };
        pawnTile.placePiece(queen);
    }
    else if (std::abs(boardRow - pawnRow) == 1)
    {
        Piece rook{ PieceType::rook,
                    color,
                    textureTable[{ color, PieceType::rook }],
                    { pawnRow * 100, pawnColumn * 100 } };
        pawnTile.placePiece(rook);
    }
    else if (std::abs(boardRow - pawnRow) == 2)
    {
        Piece bishop{ PieceType::bishop,
                      color,
                      textureTable[{ color, PieceType::bishop }],
                      { pawnRow * 100, pawnColumn * 100 } };
        pawnTile.placePiece(bishop);
    }
    else if (std::abs(boardRow - pawnRow) == 3)
    {
        Piece knight{ PieceType::knight,
                      color,
                      textureTable[{ color, PieceType::knight }],
                      { pawnRow * 100, pawnColumn * 100 } };
        pawnTile.placePiece(knight);
    }
}
