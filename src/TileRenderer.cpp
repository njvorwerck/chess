#include "TileRenderer.h"

TerminalPixelMatrix TileRenderer::render(GamePiece* piece) {
    char rep = piece == NULL ? BLANK : piece->getCharRepresentation();

    TerminalPixelMatrix tile;
    if (mPieceWidth == 1) {
        tile.resize(1);
        tile[0].push_back(TerminalPixel(rep));
        tile[0].push_back(TerminalPixel(BLANK));
    } else {
        tile.resize(mPieceWidth + 1);
        for (int i = 0; i < mPieceWidth; i++) {
            tile[i].resize(mPieceWidth);
            for (int j = 0; j < mPieceWidth; j++) {
                tile[i][j] = TerminalPixel(rep);
            }
            tile[i].push_back(TerminalPixel(BLANK));
        }
        tile.back().resize(mPieceWidth + 1);
        for (int i = 0; i < mPieceWidth + 1; i++) {
            tile.back()[i] = TerminalPixel(BLANK);
        }
    }

    return tile;
}


