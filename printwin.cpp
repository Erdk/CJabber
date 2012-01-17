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
