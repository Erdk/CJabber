#ifndef LOGHANDLER_H
#define LOGHANDLER_H

#include <iostream>
#include <fstream>

#include <gloox/loghandler.h>

using namespace std;
using namespace gloox;

class Logsink : public LogHandler
{
    ofstream logFile;

public:
    Logsink();
   ~Logsink();

    virtual void handleLog(LogLevel level, LogArea area, const string& message);
};

#endif //LOG_HANDLER_H
