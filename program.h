#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <ncurses.h>

#include "printwin.h"
#include "xmppconnection.h"

using namespace std;

class Program
{
    // variables and structures
    int height;
    int width;
    char msg_str[512];

    // gloox object which handle communication with XMPP/Jabber server
    XMPPconnection* xmpp;

    // window with chat
    WINDOW* chatWindow;

    // window with user input
    WINDOW* inputWindow;

    // simply the border around inputWindow
    WINDOW* borderWindow;

    WINDOW* createWindow(int height, int width, int starty, int startx);
    void   destroyWindow(WINDOW *local_win);

public:
    Program();
    ~Program();

    // handling windows
    void repaintDecoration();
    void connect(string username, string server, string password, string resource);
    void talkTo(JID jid);
};

#endif //PROGRAM_H