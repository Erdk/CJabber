#include "program.h"
Program::Program()
{
    initscr();
    keypad(stdscr, TRUE);
    height = LINES;
    width = COLS;

    // setting up chat and input window
    borderWindow = createWindow(5, width - 3, height - 5, 3);
    inputWindow = createWindow(3, width - 5, height - 4, 4);
    chatWindow = createWindow(height - 5, width, 0, 0);

    WindowDecorator::getInstance().setWindow(chatWindow, height - 5, width);
    scrollok(WindowDecorator::getInstance().getWindow(), TRUE);
}

Program::~Program()
{
    delete xmpp;
    destroyWindow(chatWindow);
    destroyWindow(inputWindow);
    destroyWindow(borderWindow);
    endwin();
}

WINDOW* Program::createWindow(int height, int width, int starty, int startx)
{
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    return local_win;
}

// destorying window
void Program::destroyWindow(WINDOW *local_win)
{
    wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(local_win);
    delwin(local_win);
}

void Program::repaintDecoration()
{
    mvprintw(height - 4, 0, ">> ");
    refresh();
    box(borderWindow, 0, 0);
    wrefresh(borderWindow);
    wclear(inputWindow);
    wrefresh(inputWindow);
    box(WindowDecorator::getInstance().getWindow(), 0, 0);
    wrefresh(WindowDecorator::getInstance().getWindow());
    wmove(inputWindow, 0, 1);
}

// XMPP
void Program::connect(string username, string server, string password, string resource)
{
    if (username.length() <= 0 || server.length() <= 0)
    {
        // error in configuration, aborting
    }

    if (password.length() <= 0)
    {
        // ask for password
    }

    xmpp = new XMPPconnection(username, server, resource, password);
    //while(connectionWaiting); // dirty hack, think about more pleasant solution
    //pthread_mutex_lock(&connect_mutex);
    pthread_cond_wait(&connect_var, &connect_mutex);
    //pthread_mutex_unlock(&connect_mutex);
    repaintDecoration();
}

void Program::talkTo(JID jid)
{
    do
    {
        stringstream msg;
        wgetnstr(inputWindow, msg_str, 512);
        if (!string(msg_str).empty())
        {
            msg << "ja: " << msg_str;
            WindowDecorator::getInstance().PrintWin(msg, Me);
            xmpp->sendMessage(jid, msg_str);
            wclear(inputWindow);
            wrefresh(inputWindow);
        }

    } while (!string(msg_str).empty());
}