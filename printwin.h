#ifndef PRINTWIN_H
#define PRINTWIN_H

#include <string>
#include <vector>
#include <sstream>
#include <ncurses.h>

using namespace std;

enum Source
{
    Me,
    They,
    Log
};

class MessageWindow
{
    // for singleton
    MessageWindow() { input_x = -1; input_y = -1; }
    MessageWindow(const MessageWindow&);
    MessageWindow& operator=(const MessageWindow&);

    // window with message log
    WINDOW* msgLog;
    int height;
    int width;

    int input_x;
    int input_y;

public:
    static MessageWindow& getInstance()
    {
        static MessageWindow instance;
        return instance;
    }

    // getting WINDOW ref
    WINDOW* getWindow() { return msgLog; }
    void setWindow(WINDOW* win, int _height, int _width)
    {
        msgLog = win;
        height = _height - 2;
        width = _width - 2;
    }

    // only setters, because this is used only locally within PrintWin
    void setInputX(int x) { input_x = x + 1; }
    void setInputY(int y) { input_y = y; }

    void printWin(stringstream &msg, Source source);
};

#endif //PRINTWIN_H
