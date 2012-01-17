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

#include <printwin.h>

void MessageWindow::printWin(stringstream &msg, Source source)
{
    wborder(MessageWindow::getInstance().getWindow(), ' ', ' ', ' ',' ',' ',' ',' ',' ');

    string msgTextTmp;
    string msgText = msg.str();
    int rest = msgText.length() % width;
    if (width != 0)
    {
        msgTextTmp = msgText.substr(msgText.length() - rest, rest);
        mvwprintw(MessageWindow::getInstance().getWindow(), 0, 2, msgTextTmp.c_str());
        wscrl(MessageWindow::getInstance().getWindow(), -1);
        msgText.erase(msgText.length() - rest, rest);
    }

    while (msgText.length() > 0)
    {
        int part = msgText.length() / width;
        msgTextTmp = msgText.substr((part - 1) * width, width);
        mvwprintw(MessageWindow::getInstance().getWindow(), 0, 2, msgTextTmp.c_str());
        wscrl(MessageWindow::getInstance().getWindow(), -1);
        msgText.erase((part - 1) * width, width);
    }

    //mvwprintw(MessageWindow::getInstance().getWindow(), 0, 2, msgText.c_str());
    wscrl(MessageWindow::getInstance().getWindow(), -1);

    box(MessageWindow::getInstance().getWindow(), 0, 0);
    wrefresh(MessageWindow::getInstance().getWindow());
    move(input_y, input_x);
    refresh();
}
