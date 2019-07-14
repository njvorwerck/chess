#ifndef __TILE_RENDERER_H__
#define __TILE_RENDERER_H__

#include "GamePiece.h"
#include "TerminalWriter.h"

class TileRenderer {

    Color mP1Color;
    Color mP2Color;
    Color mTile1Color;
    Color mTile2Color;

    size_t mPieceWidth;
    const char BLANK = ' ';

public:

    TileRenderer(size_t pieceWidth) : mPieceWidth(pieceWidth) { }

    TerminalPixelMatrix render(GamePiece* piece);

};

#endif
