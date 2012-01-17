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

#include <keycodes.h>
#include <textpopup.h>

TextPopup::TextPopup(string header, bool hiddenChars)
{
    int height = 5; // borders + header + input field
    int width = 40; // should be feasable

    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
    int start_y = (max_y - height) / 2;
    int start_x = (max_x - width) / 2;

    WINDOW* popup = createWindow(height, width, start_y, start_x);
    box(popup, 0, 0);
    mvwprintw(popup, 1, (width - header.length()) / 2, "%s", header.c_str());
    refresh();
    wrefresh(popup);

    // all right, header printed, now hareder task: get input from user
    if (hiddenChars)
        noecho();

    WINDOW* inputField = createWindow(1, width - 2, start_y + 3, start_x + 1);
    input = "";
    string print_msg = "";
    bool end = false;
    int c;
    int cursorPosition = 0;

    while(!end)
    {
        c = wgetch(inputField);
        switch(c)
        {
            case ESC:
                break;
            case ENTER:
                wclear(inputField);
                wmove(inputField, 0, 0);
                wrefresh(inputField);
                end = true;
                break;
            case BACKSPACE:
                if (cursorPosition > 0)
                {
                    cursorPosition--;
                    input.erase(cursorPosition);
                    if (hiddenChars)
                        print_msg.erase(cursorPosition);
                    wclear(inputField);
                    if (hiddenChars)
                        wprintw(inputField, "%s", print_msg.c_str());
                    else
                        wprintw(inputField, "%s", input.c_str());
                    wrefresh(inputField);
                }
                break;
            default:
                input += (char)c;
                cursorPosition++;
                if (hiddenChars)
                {
                    print_msg += '*';
                    wclear(inputField);
                    wprintw(inputField, "%s", print_msg.c_str());
                    wrefresh(inputField);
                }
        }
    }
    if (hiddenChars)
        echo();

    wclear(inputField);
    wrefresh(inputField);
    wclear(popup);
    wrefresh(popup);
    destroyWindow(inputField);
    destroyWindow(popup);
    refresh();
}
