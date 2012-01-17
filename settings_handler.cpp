#include <cstdlib>
#include <fstream>
#include <iostream>
#include <settings_handler.h>

SettingsHandler::SettingsHandler()
{
    size_t found;
    username = "";
    server   = "";
    password = "";
    resource = "";

    if(!rcIsEmpty())
    {
        string line;
        string tmp_username("username=");
        string tmp_server  ("server=");
        string tmp_password("password=");
        string tmp_resource("resource=");
        ifstream myfile(getRCFilename().c_str());

        if (myfile.is_open())
        {
            while (myfile.good())
            {
                getline (myfile, line);
                if (line.length() > 0)
                {
                    if (line.at(0) == '#')
                        continue;

                    found = line.find(tmp_username);
                    if (found != string::npos)
                    {
                        username = line.erase(0, tmp_username.length());
                        continue;
                    }

                    found = line.find(tmp_server);
                    if (found != string::npos)
                    {
                        server = line.erase(0, tmp_server.length());
                        continue;
                    }

                    found = line.find(tmp_password);
                    if (found != string::npos)
                    {
                        password = line.erase(0, tmp_password.length());
                        continue;
                    }

                    found = line.find(tmp_resource);
                    if (found != string::npos)
                    {
                        resource = line.erase(0, tmp_resource.length());
                        continue;
                    }
                }
            }
            myfile.close();
        }
        else
        {
            cout << "RC ERROR!" << endl;
        }
    }
    else
    {
        cout << "Writing config to: " << getRCFilename() << endl;
        ofstream rcFileStream;
        rcFileStream.open(getRCFilename().c_str());
        rcFileStream << "# CJabber RC file" << endl;
        rcFileStream << "# Uncomment apropriate lines and fill with correct data" << endl << endl;
        rcFileStream << "# required" << endl;
        rcFileStream << "#username=" << endl;
        rcFileStream << "# required" << endl;
        rcFileStream << "#server="   << endl;
        rcFileStream << "#optional, if not specified application will ask at startup" << endl;
        rcFileStream << "#password=" << endl;
        rcFileStream << "#optional, if not specified application will use default value" << endl;
        rcFileStream << "#resource=" << endl;
        rcFileStream.close();
    }
}

/**
 * Check if rc file is empty
 */
bool SettingsHandler::rcIsEmpty()
{
    int length;
    ifstream rcFileStream;

    rcFileStream.open(getRCFilename().c_str(), ios::binary);
    rcFileStream.seekg(0, ios::end);
    length = rcFileStream.tellg();
    rcFileStream.close();

    if (length > 0)
        return false;

    return true;
}

/**
 * Generates rc file filename basing on user's HOME var
 */
string SettingsHandler::getRCFilename()
{
    string filepath(getenv("HOME"));
    filepath += string("/.cjabber.rc");
    return filepath;
}


