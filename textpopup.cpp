#include <keycodes.h>
#include <textpopup.h>

TextPopup::TextPopup(string header, bool hiddenChars)
{
    int height = 5; // borders + header + input field
    int width = 40; // should be feasable

    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
    int start_y = (max_y - height) / 2;
    int start_x = (max_x - width) / 2;

    WINDOW* popup = createWindow(height, width, start_y, start_x);
    box(popup, 0, 0);
    mvwprintw(popup, 1, (width - header.length()) / 2, "%s", header.c_str());
    refresh();
    wrefresh(popup);

    // all right, header printed, now hareder task: get input from user
    if (hiddenChars)
        noecho();

    WINDOW* inputField = createWindow(1, width - 2, start_y + 3, start_x + 1);
    input = "";
    string print_msg = "";
    bool end = false;
    int c;
    int cursorPosition = 0;

    while(!end)
    {
        c = wgetch(inputField);
        switch(c)
        {
            case ESC:
                break;
            case ENTER:
                wclear(inputField);
                wmove(inputField, 0, 0);
                wrefresh(inputField);
                end = true;
                break;
            case BACKSPACE:
                if (cursorPosition > 0)
                {
                    cursorPosition--;
                    input.erase(cursorPosition);
                    if (hiddenChars)
                        print_msg.erase(cursorPosition);
                    wclear(inputField);
                    if (hiddenChars)
                        wprintw(inputField, "%s", print_msg.c_str());
                    else
                        wprintw(inputField, "%s", input.c_str());
                    wrefresh(inputField);
                }
                break;
            default:
                input += (char)c;
                cursorPosition++;
                if (hiddenChars)
                {
                    print_msg += '*';
                    wclear(inputField);
                    wprintw(inputField, "%s", print_msg.c_str());
                    wrefresh(inputField);
                }
        }
    }
    if (hiddenChars)
        echo();

    destroyWindow(inputField);
}
