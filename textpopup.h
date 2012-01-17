#ifndef TEXTPOPUP_H
#define TEXTPOPUP_H

#include <popup.h>

class TextPopup : public Popup
{
    string input;
public:
    TextPopup(string header, bool hiddenChars);
    void cleanTextPopup();
    string getInput() { return input; }
};

#endif //TEXTPOPUP_H