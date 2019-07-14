#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include <vector>

#include "UtilityTypes.h"
#include "TerminalWriter.h"
#include "TileRenderer.h"
#include "Queen.h"


int main (int argc, char **argv)
{

    RowCol dims(10, 10);
    RowCol offset(10, 10);

    TerminalWriter termWriter(dims, offset);

    TerminalPixelMatrix window;
    window.resize(10);
    for (int i = 0; i < 10; i++) {
        window[i].resize(10);
        for (int j = 0; j < 10; j++) {
            window[i][j] = TerminalPixel('a');
        }
    }

    termWriter.writeAll(window);

    /*
    offset.row = 9;
    offset.col = 9;
    termWriter.writePixel(offset, TerminalPixel('z'));

    TerminalPixelMatrix chunk;
    chunk.resize(3);
    for (int i = 0; i < 3; i++) {
        chunk[i].resize(3); 
        chunk[i][0] = TerminalPixel('0', red, yellow);
        chunk[i][1] = TerminalPixel('0', red, yellow);
        chunk[i][2] = TerminalPixel('0', red, yellow);
    }

    offset.row = 4;
    offset.col = 4;
    termWriter.writeChunk(offset, chunk);
    */

    Position blah(0, 0);
    Queen q(blah, false); 
    TileRenderer tileRenderer(3); 

    offset.row = 3;
    offset.col = 3;

    TerminalPixelMatrix tile = tileRenderer.render(&q);

    termWriter.writeChunk(offset, tile);


    return 0;  
}
