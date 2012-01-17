#ifndef BASIC_WINDOW_H
#define BASIC_WINDOW_H

#include <ncurses.h>

class BasicWindow
{
protected:
    WINDOW* createWindow(int height, int width, int starty, int startx)
    {
        WINDOW *local_win;
        local_win = newwin(height, width, starty, startx);
        return local_win;
    }

    void destroyWindow(WINDOW *local_win)
    {
        wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
        wrefresh(local_win);
        delwin(local_win);
    }
};

#endif //BASIC_WINDOW_H