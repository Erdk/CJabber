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

#include <locale.h>
#include <program.h>
#include <settings_handler.h>

int main()
{
    setlocale(LC_ALL, "pl_PL.UTF-8");
    SettingsHandler rc;
    CJabberCore program;
    XMPPstate xs;
    do{
        xs = program.connect(rc.getUsername(), rc.getServer(), rc.getPassword(), rc.getResource());
    } while (xs == BadPassword);
    
    if (xs == Ok)
    {
        program.innerEventLoop();
    }
    return 0;
}
