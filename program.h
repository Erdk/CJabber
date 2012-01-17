#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <ncurses.h>
#include <printwin.h>
#include <basic_window.h>
#include <xmppconnection.h>

using namespace std;

enum Command
{
    Continue,
    Quit,
};

class CJabberCore : public BasicWindow
{
    // true if cannot read username and server from config
    // if true => abort program execution
    bool invalidRC;

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

    // person we talk to
    JID jid;

    // react on command
    Command getCommand(string command);

    // prints usage info into message log
    void printInfo();

public:
    CJabberCore();
   ~CJabberCore();

    // handling windows
    void repaintDecoration();
    void connect(string username, string server, string password, string resource);
    void innerEventLoop();

    string askForPassword();
    void printErrorAndExit();
};

#endif //PROGRAM_H