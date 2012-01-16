#include "printwin.h"

void WindowDecorator::PrintWin(stringstream &msg, Source source)
{
    int y, x;
    getyx(stdscr, y, x);
    wborder(WindowDecorator::getInstance().getWindow(), ' ', ' ', ' ',' ',' ',' ',' ',' ');

    string msgTextTmp;
    string msgText = msg.str();
    int rest = msgText.length() % width;
    if (width != 0)
    {
        msgTextTmp = msgText.substr(msgText.length() - rest, rest);
        mvwprintw(WindowDecorator::getInstance().getWindow(), 0, 2, msgTextTmp.c_str());
        wscrl(WindowDecorator::getInstance().getWindow(), -1);
        msgText.erase(msgText.length() - rest, rest);
    }

    while (msgText.length() > 0)
    {
        int part = msgText.length() / width;
        msgTextTmp = msgText.substr((part - 1) * width, width);
        mvwprintw(WindowDecorator::getInstance().getWindow(), 0, 2, msgTextTmp.c_str());
        wscrl(WindowDecorator::getInstance().getWindow(), -1);
        msgText.erase((part - 1) * width, width);
    }

    //mvwprintw(WindowDecorator::getInstance().getWindow(), 0, 2, msgText.c_str());
    wscrl(WindowDecorator::getInstance().getWindow(), -1);

    box(WindowDecorator::getInstance().getWindow(), 0, 0);
    wrefresh(WindowDecorator::getInstance().getWindow());
    move(y, x);
    refresh();
}
