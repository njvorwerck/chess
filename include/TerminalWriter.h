#ifndef __TERMINAL_WRITER_H__
#define __TERMINAL_WRITER_H__

#include <vector>
#include <string>

#include "UtilityTypes.h"

enum Color : unsigned int { black, maroon, green, brown, violet, purple, teal, 
    lightGrey, grey, red, neonGreen, yellow, blue, magenta, neonTeal, white };

struct TerminalPixel {
    Color bgColor;
    Color fontColor;
    char value;

    TerminalPixel(char value_in = '0', Color fontColor_in = white, Color bgColor_in = black)
        : value(value_in), fontColor(fontColor_in), bgColor(bgColor_in) {}

    bool operator==(const TerminalPixel &a) {
        return a.value == this->value && a.bgColor == this->bgColor && a.fontColor == this->fontColor;
    }

    bool operator!=(const TerminalPixel &a) {
        return !(*this == a);
    }
};

typedef std::vector<std::vector<TerminalPixel>> TerminalPixelMatrix;

void printTerminalPixelMatrix(TerminalPixelMatrix& matrix);


/**
  * This class provides a "window" into the terminal
  */
class TerminalWriter {

    RowCol mTerminalDims;
    RowCol mWindowDims;
    RowCol mOffset;
    TerminalPixelMatrix mCurrentWindow;

    void init(RowCol dimensions, RowCol offset);
    void rawWritePixel(RowCol offset, TerminalPixel pixel);

public:

    TerminalWriter(RowCol dimensions);
    TerminalWriter(RowCol dimensions, RowCol offset);

    void writeAll(TerminalPixelMatrix &window);
    void writePixel(RowCol offset, TerminalPixel pixel);
    void writeChunk(RowCol baseOffset, TerminalPixelMatrix &chunk);
    TerminalPixelMatrix getWindow();

    void forcePrint();

};

#endif
