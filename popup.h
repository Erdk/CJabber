#ifndef POPUP_H
#define POPUP_H

#include <string>
#include <vector>
#include <ncurses.h>

#include <basic_window.h>

using namespace std;

class Popup : public BasicWindow
{
protected:
    vector<string> splitMessage(string message);
    int getLongestMessage(vector<string> messages);

public:
    Popup() { }
    Popup(string header, string message);
};

#endif //POPUP_H