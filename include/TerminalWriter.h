#ifndef __TERMINAL_WRITER_H__
#define __TERMINAL_WRITER_H__

#include <vector>
#include <string>

#include "UtilityTypes.h"

/**
  * This class provides a "window" into the terminal
  */
class TerminalWriter {

    RowCol mTerminalDims;
    RowCol mWindowDims;
    RowCol mOffset;
    std::vector<std::string> mCurrentWindow;

    void init(RowCol dimensions, RowCol offset);
    void rawWritePixel(RowCol offset, char pixel);

public:

    TerminalWriter(RowCol dimensions);
    TerminalWriter(RowCol dimensions, RowCol offset);

    void writeAll(std::vector<std::string> &window);
    void writePixel(RowCol offset, char pixel);
    std::vector<std::string> getWindow();

};

#endif
