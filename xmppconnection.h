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

#ifndef XMPPCONNECTION_H
#define XMPPCONNECTION_H

#include <string>
#include <pthread.h>
#include <logsink.h>
#include <gloox/gloox.h>
#include <gloox/client.h>
#include <gloox/connectionlistener.h>
#include <gloox/messagehandler.h>
#include <gloox/rostermanager.h>
#include <gloox/message.h>

using namespace std;
using namespace gloox;

//extern bool connectionWaiting;
extern pthread_mutex_t connect_mutex;
extern pthread_cond_t  connect_var;

class XMPPconnection : public ConnectionListener, MessageHandler
{
    JID jid;
    Client* client;
    Logsink* sink;

    string username;
    string server;
    string resource;
    string password;

    pthread_t reciver;

public:
    XMPPconnection(string _username, string _server, string _resource, string _password);
    ~XMPPconnection();

    // sends message to particular id
    void sendMessage(JID jid, const char* msg);

    // disconnects from server
    void disconnect();

    // returns connection state
    ConnectionState getState();

    // from ConnectionListener
    virtual void onConnect();
    virtual void onDisconnect(ConnectionError e);

    virtual void onResourceBind(const std::string &resource);
    virtual void onResourceBindError(const Error *error);
    virtual void onSessionCreateError(const Error *error);
    virtual void onStreamEvent(StreamEvent event);
    virtual bool onTLSConnect(const CertInfo &info) { return true; }

    // from MessagHandler
    virtual void handleMessage(const Message& msg, MessageSession* session = 0);

    // user interaction
    void printRoster();

    bool isAuth() { client->authed(); }
};

#endif // XMPPCONNECTION_H
