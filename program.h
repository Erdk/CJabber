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

#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <ncurses.h>
#include <printwin.h>
#include <basic_window.h>
#include <xmppconnection.h>

using namespace std;

enum XMPPstate
{
    BadRC,
    BadPassword,
    Ok,
};

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
    XMPPstate connect(string username, string server, string password, string resource);
    void innerEventLoop();

    string askForPassword();
    void printErrorAndExit();
};

#endif //PROGRAM_H