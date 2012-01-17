#ifndef SETTINGS_HANDLER_H
#define SETTINGS_HANDLER_H

#include <string>

using namespace std;

class SettingsHandler
{
    string username;
    string server;
    string password;
    string resource;

    bool rcIsEmpty();
    string getRCFilename();

public:
    SettingsHandler();

    string getUsername() { return username; }
    string getServer()   { return server;   }
    string getPassword() { return password; }
    string getResource() { return resource; }
};

#endif //SETTINGS_HANDLER_H