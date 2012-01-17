/******************************************************************************
 * Copyright 2012 Lukas 'Erdk' Redynk <mr.erdk@gmail.com>
 * 
 * This file is part of CJabber.
 *
 * CJabber is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * CJabber is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with CJabber; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 *****************************************************************************/

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
