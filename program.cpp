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

#include <popup.h>
#include <program.h>
#include <keycodes.h>
#include <textpopup.h>

CJabberCore::CJabberCore()
{
    initscr();
    cbreak();
    //keypad(stdscr, TRUE);
    height = LINES;
    width = COLS;

    // setting up chat and input window
    borderWindow = createWindow(5,          width - 3, height - 5, 3);
    inputWindow  = createWindow(3,          width - 5, height - 4, 4);
    chatWindow   = createWindow(height - 5, width    , 0         , 0);
    keypad(inputWindow, TRUE);

    // for proper input cursor position
    wrefresh(inputWindow);
    wmove(inputWindow, 0, 0);
    int y, x;
    getparyx(inputWindow, y, x);
    MessageWindow::getInstance().setInputX(x);
    MessageWindow::getInstance().setInputY(y);

    // setting refs for printMsg
    MessageWindow::getInstance().setWindow(chatWindow, height - 5, width);
    scrollok(MessageWindow::getInstance().getWindow(), TRUE);
    jid = JID("");
}

CJabberCore::~CJabberCore()
{
    if (xmpp != NULL)
        delete xmpp;
    destroyWindow(chatWindow);
    destroyWindow(inputWindow);
    destroyWindow(borderWindow);
    endwin();
}

void CJabberCore::repaintDecoration()
{
    mvprintw(height - 4, 0, ">> ");
    refresh();
    box(borderWindow, 0, 0);
    wrefresh(borderWindow);
    wclear(inputWindow);
    wrefresh(inputWindow);
    box(MessageWindow::getInstance().getWindow(), 0, 0);
    wrefresh(MessageWindow::getInstance().getWindow());
    wmove(inputWindow, 0, 0);
}

// XMPP
XMPPstate CJabberCore::connect(string username, string server, string password, string resource)
{
    if (username.length() <= 0 || server.length() <= 0)
    {
        invalidRC = true;
        string header  = "Błąd!";
        string message = "Sprawdź użytkownika i hasło|pliku konfiguracyjnym!|(Naciśnij dowolny klawisz)";
        Popup p(header, message);
        xmpp = NULL;
    }

    else
    {
        invalidRC = false;
        if (password.length() <= 0)
        {
            TextPopup p("Podaj hasło:", true);
            password = p.getInput();
        }

        xmpp = new XMPPconnection(username, server, resource, password);

        // waiting for connection
        pthread_cond_wait(&connect_var, &connect_mutex);
    }

    XMPPstate xs;
    if (xmpp == NULL)
    {
        xs = BadRC;
    }
    else
    {
        if (xmpp->isAuth())
        {
            xs = Ok;
        }
        else
        {
            xs = BadPassword;
            delete xmpp;
        }
    }

    return xs;
}

void CJabberCore::innerEventLoop()
{
    repaintDecoration();
    int c;
    bool end = invalidRC;
    string buffer = "";
    stringstream bufferToSend;
    int bufferLength = 0;
    int cursorPosition = 0;

    printInfo();
    
    while(!end)
    {
        c = wgetch(inputWindow);
        switch(c)
        {
            case ESC:
                end = true;
                wclear(inputWindow);
                wrefresh(inputWindow);
                wmove(inputWindow, 0, 0);
                break;
            case ENTER:
                wclear(inputWindow);
                wmove(inputWindow, 0, 0);
                wrefresh(inputWindow);
                if (buffer.length() > 0)
                {
                    if (jid == true && buffer.at(0) != '/')
                    {
                        bufferToSend << "ja: " << buffer;
                        MessageWindow::getInstance().printWin(bufferToSend, Me);
                        xmpp->sendMessage(jid, buffer.c_str());

                    }
                    else
                    {
                        Command c = getCommand(buffer);
                        if (c == Quit)
                        {
                            end = true;
                        }
                    }
                }
                bufferToSend.str("");
                bufferToSend.clear();
                buffer.clear();
                cursorPosition = 0;
                repaintDecoration();
                break;
            case BACKSPACE:
                if (cursorPosition > 0)
                {
                    cursorPosition--;
                    buffer.erase(cursorPosition);
                    wclear(inputWindow);
                    wprintw(inputWindow, "%s", buffer.c_str());
                    wrefresh(inputWindow);
                }
                break;
            default:
                buffer += (char)c;
                cursorPosition++;
        }
    }
}

Command CJabberCore::getCommand(string command)
{
    stringstream s;
    if (command.length() > 0)
    {
        if (command.at(0) == '/')
        {
            size_t found;
            found = command.find("talk");
            if (found != string::npos)
            {
                string tmp = command.erase(0, 6);
                jid = JID(tmp);
                if (jid != true)
                {
                    printInfo();
                    s << "Błędnie podany identyfikator użytkownika.";
                    MessageWindow::getInstance().printWin(s, Log);
                    return Continue;
                }
                return Continue;
            }
            else
            {
                found = command.find("quit");
                if (found != string::npos)
                {
                    return Quit;
                }
                else
                {
                    found = command.find("roster");
                    if (found != string::npos)
                    {
                        xmpp->printRoster();
                        return Continue;
                    }

                    printInfo();
                    return Continue;
                }
            }
        }
        else
        {
            printInfo();
            return Continue;
        }
    }
}

void CJabberCore::printInfo()
{
    stringstream s;
    s << " /quit lub wcisąć <ESC> na klawiaturze, aby wyjść.";
    MessageWindow::getInstance().printWin(s, Log);
    s.str("");
    s.flush();
    s << " /talk user@serwer.com aby rozmawiać z innym użytkownikiem.";
    MessageWindow::getInstance().printWin(s, Log);
    s.str("");
    s.flush();
    s << " /roster pobiera i wyświetla listę znajmoych.";
    MessageWindow::getInstance().printWin(s, Log);
    s.str("");
    s.flush();
    s << "CJabber: jak korzystać?";
    MessageWindow::getInstance().printWin(s, Log);
}