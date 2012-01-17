#include <popup.h>
#include <algorithm>

Popup::Popup(string header, string message)
{
    vector<string> messages = splitMessage(message);
    int width = getLongestMessage(messages);
    if (width < header.length())
        width = header.length();
    width += 4; // borders

    int height = messages.size();
    height += 2; // for header and vspace
    height += 2; // borders

    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
    int start_y = (max_y - height) / 2;
    int start_x = (max_x - width) / 2;

    WINDOW* popup = createWindow(height, width, start_y, start_x);
    box(popup, 0, 0);
    mvwprintw(popup, 1, (width - header.length()) / 2, "%s", header.c_str());

    int i = 0;
    vector<string>::iterator it;
    for (it = messages.begin(); it != messages.end(); it++)
    {
        mvwprintw(popup, 3 + i, (width - (*it).length()) / 2, "%s", (*it).c_str());
        i++;
    }

    refresh();
    wrefresh(popup);
    getch();
    destroyWindow(popup);
}

vector<string> Popup::splitMessage(string message)
{
    string delimiter("|");
    vector<string> ret = vector<string>();
    size_t found;

    while (message.length() > 0)
    {
        found = message.find(delimiter);
        if (found == string::npos)
        {
            ret.push_back(message);
            break;
        }
        else
        {
            string add = message.substr(0, found);
            ret.push_back(add);
            if(message.length() < found + 1)
                message.erase(0, found);
            else
                message.erase(0, found + 1);
        }
    }

    return ret;
}

int Popup::getLongestMessage(vector<string> messages)
{
    int current = 0, longest = 0;
    vector<string>::iterator it;

    for (it = messages.begin(); it != messages.end(); it++)
    {
        current = (*it).length();
        if (current > longest)
            longest = current;
    }

    return longest;
}