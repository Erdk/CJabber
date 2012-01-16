#ifndef XMPPCONNECTION_H
#define XMPPCONNECTION_H

#include <string>

#include <gloox/gloox.h>
#include <gloox/client.h>
#include <gloox/connectionlistener.h>
#include <gloox/message.h>
#include <gloox/messagehandler.h>
#include <gloox/rostermanager.h>
#include <gloox/message.h>

#include "logsink.h"

using namespace std;
using namespace gloox;

extern bool connectionWaiting;

class XMPPconnection : public ConnectionListener, MessageHandler
{
    JID jid;
    Client* client;
    Logsink* sink;

    string username;
    string server;
    string resource;
    string password;

public:
    XMPPconnection(string _username, string _server, string _resource, string _password);
    ~XMPPconnection();

    // sends message to particular id
    void sendMessage(JID jid, const char* msg);

    // disconnects from server
    void disconnect() { client->disconnect(); }

    // returns connection state
    ConnectionState getState() { return client->state(); }

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
};

#endif // XMPPCONNECTION_H
