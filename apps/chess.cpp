#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include <vector>

#include "UtilityTypes.h"
#include "TerminalWriter.h"


int main (int argc, char **argv)
{
    /*
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    printf ("lines %d\n", w.ws_row);
    printf ("columns %d\n", w.ws_col);
    std::string blah;

    std::cout << "\033[2J";

    std::string fillScreen = "";
    for (size_t i = 0; i < w.ws_row; i++) {
        fillScreen += "\n";
    }
    printf("%s", fillScreen.c_str()); 
    std::cout << "\033[20;20H";

    size_t toRemove = 0;
    while (std::cin >> blah && blah != "a") {
        toRemove = blah.size();
    }

    std::cout << "\033[20;" + std::to_string(20) + "H";
    
    for (int i = 0; i < toRemove; i++) {
        replaceChar(20, 20 + i, 'e');
    }

    std::cout << "\033[1;1H";
    */

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

    offset.row = 9;
    offset.col = 9;
    termWriter.writePixel(offset, TerminalPixel('z'));

    TerminalPixelMatrix chunk;
    chunk.resize(3);
    for (int i = 0; i < 3; i++) {
        chunk[i].resize(3); 
        chunk[i][0] = TerminalPixel('0');
        chunk[i][1] = TerminalPixel('0');
        chunk[i][2] = TerminalPixel('0');
    }

    offset.row = 4;
    offset.col = 4;
    termWriter.writeChunk(offset, chunk);


    return 0;  
}
