#include <locale.h>
#include "program.h"

#include "settings_handler.h"

int main()
{
    setlocale(LC_ALL, "pl_PL.UTF-8");
    SettingsHandler rc;
//     cout << rc.getUsername() << endl;
//     cout << rc.getServer() << endl;
//     cout << rc.getPassword() << endl;
//     cout << rc.getResource() << endl;
    Program program;
    program.connect(rc.getUsername(), rc.getServer(), rc.getPassword(), rc.getResource());
    program.talkTo(JID("erdk@jabber.org"));
    return 0;
}
