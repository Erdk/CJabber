#include <locale.h>
#include <program.h>
#include <settings_handler.h>

int main()
{
    setlocale(LC_ALL, "pl_PL.UTF-8");
    SettingsHandler rc;
    CJabberCore program;
    program.connect(rc.getUsername(), rc.getServer(), rc.getPassword(), rc.getResource());
    //program.talkTo(JID("erdk@jabber.org"));
    program.innerEventLoop();
    return 0;
}
