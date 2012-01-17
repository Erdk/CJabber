/******************************************************************************
 * Copyright 2012 Lukas 'Erdk' Redynk <mr.erdk@gmail.com>
 * 
 * This file is part of CJabber.
 *
 * CJabber is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * CJabber is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with CJabber; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 *****************************************************************************/

#ifndef LOGHANDLER_H
#define LOGHANDLER_H

#include <fstream>
#include <iostream>
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
