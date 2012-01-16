#ifndef PRINTWIN_H
#define PRINTWIN_H

#include <string>
#include <sstream>
#include <vector>
#include <ncurses.h>

using namespace std;

enum Source
{
    Me,
    They,
    Log
};

class WindowDecorator
{
    // for singleton
    WindowDecorator() {}
    WindowDecorator(const WindowDecorator&);
    WindowDecorator& operator=(const WindowDecorator&);

    // window with message log
    WINDOW* msgLog;
    int height;
    int width;

public:

    WINDOW* getWindow() { return msgLog; }
    void setWindow(WINDOW* win, int _height, int _width)
    {
        msgLog = win;
        height = _height - 2;
        width = _width - 2;
    }

    void PrintWin(stringstream &msg, Source source);

    static WindowDecorator& getInstance()
    {
        static WindowDecorator instance;
        return instance;
    }
};

#endif //PRINTWIN_H
