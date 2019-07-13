#ifndef __TERMINAL_WRITER_H__
#define __TERMINAL_WRITER_H__

#include <vector>
#include <string>

#include "UtilityTypes.h"

enum Color { white, black, grey, red, green, blue };

struct TerminalPixel {
    Color bgColor;
    Color fontColor;
    char value;

    TerminalPixel(char value_in = '0', Color bgColor_in = black, Color fontColor_in = white)
        : value(value_in), bgColor(bgColor_in), fontColor(fontColor_in) {}

    bool operator==(const TerminalPixel &a) {
        return a.value == this->value && a.bgColor == this->bgColor && a.fontColor == this->fontColor;
    }

    bool operator!=(const TerminalPixel &a) {
        return !(*this == a);
    }
};

typedef std::vector<std::vector<TerminalPixel>> TerminalPixelMatrix;

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
