#include "logsink.h"
#include <sstream>
#include <string>

Logsink::Logsink()
{
    logFile.open("run.log", ios::out);
}

Logsink::~Logsink()
{
    logFile.close();
}

// from LogHandler
void Logsink::handleLog(LogLevel level, LogArea area, const string &message)
{
    logFile << "XMPP: " << message << endl;
    logFile.flush();
}

