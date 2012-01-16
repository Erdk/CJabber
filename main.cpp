#include <iostream>
#include <locale.h>
#include <ncurses.h>

#include "printwin.h"
#include "xmppconnection.h"

WINDOW* createNewWin(int height, int width, int startx, int starty);
void destroyWin(WINDOW* localWin);

int main()
{
    // variables and structures
    int height;
    int width;
    char msg_str[512];
    XMPPconnection* xmpp;
    WINDOW* chatWindow;
    WINDOW* inputWindow;
    WINDOW* borderWindow;

    setlocale(LC_ALL, "pl_PL.UTF-8");
    initscr();
    keypad(stdscr, TRUE);
    height = LINES;
    width = COLS;

    // setting up chat and input window
    borderWindow = createNewWin(5, width - 3, height - 5, 3);
    inputWindow = createNewWin(3, width - 5, height - 4, 4);
    chatWindow = createNewWin(height - 5, width, 0, 0);
    WindowDecorator::getInstance().setWindow(chatWindow, height - 5, width);
    scrollok(WindowDecorator::getInstance().getWindow(), TRUE);
    xmpp = new XMPPconnection("testerdk", "jabber.org", "debug", "qwer1234");

    while(connectionWaiting); // dirty hack, think about more pleasant solution

    mvprintw(height - 4, 0, ">> ");
    refresh();
    box(borderWindow, 0, 0);
    wrefresh(borderWindow);
    wclear(inputWindow);
    wrefresh(inputWindow);
    box(WindowDecorator::getInstance().getWindow(), 0, 0);
    wrefresh(WindowDecorator::getInstance().getWindow());
    wmove(inputWindow, 0, 0);
    //refresh();

    do
    {
        stringstream msg;
        wgetnstr(inputWindow, msg_str, 512);
        if (!string(msg_str).empty())
        {
            msg << "ja: " << msg_str;
            WindowDecorator::getInstance().PrintWin(msg, Me);
            JID jid("erdk@jabber.org");
            xmpp->sendMessage(jid, msg_str);
            wclear(inputWindow);
            wrefresh(inputWindow);
        }

    } while (!string(msg_str).empty());

    delete xmpp;
    destroyWin(chatWindow);
    endwin();
    return 0;
}
// for creating new window
WINDOW *createNewWin(int height, int width, int starty, int startx)
{
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    box(local_win, 0 , 0);          /* 0, 0 gives default characters
                                        * for the vertical and horizontal
                                        * lines                        */
    //wrefresh(local_win);            /* Show that box                */
    return local_win;
}

// destorying window
void destroyWin(WINDOW *local_win)
{
        /* box(local_win, ' ', ' '); : This won't produce the desired
         * result of erasing the window. It will leave it's four corners
         * and so an ugly remnant of window.
         */
        wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
        /* The parameters taken are
         * 1. win: the window on which to operate
         * 2. ls: character to be used for the left side of the window
         * 3. rs: character to be used for the right side of the window
         * 4. ts: character to be used for the top side of the window
         * 5. bs: character to be used for the bottom side of the window
         * 6. tl: character to be used for the top left corner of the window
         * 7. tr: character to be used for the top right corner of the window
         * 8. bl: character to be used for the bottom left corner of the window
         * 9. br: character to be used for the bottom right corner of the window
         */
        wrefresh(local_win);
        delwin(local_win);
}