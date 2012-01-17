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

#include <printwin.h>
#include <xmppconnection.h>
#include <gloox/error.h>
#include <gloox/rosteritem.h>
#include <gloox/connectiontcpclient.h>
#include <gloox/messagesession.h>

using namespace std;

pthread_mutex_t connect_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t stop_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  connect_var   = PTHREAD_COND_INITIALIZER;

bool stop = false;

void* polling_thread(void* client)
{
    Client* cl = (Client*) client;
    pthread_mutex_lock(&stop_mutex);
    bool run = !stop;
    pthread_mutex_unlock(&stop_mutex);
    
    while(run)
    {
        pthread_mutex_lock(&stop_mutex);
        run = !stop;
        pthread_mutex_unlock(&stop_mutex);
        cl->recv(10);
    }
    pthread_exit(NULL);
}

XMPPconnection::XMPPconnection(string _username, string _server, string _resource, string _password)
{
    username = _username;
    server = _server;
    resource = _resource;
    password = _password;
    stringstream msg;

    jid = JID(username + "@" + server + "/" + resource);
    msg << jid.bare() << endl;
    client = new Client(jid, password);
    sink = new Logsink();
    client->logInstance().registerLogHandler(LogLevelDebug, LogAreaAll, sink);
    ConnectionTCPClient* conn = new ConnectionTCPClient(client, client->logInstance(), server);
    client->setTls(TLSRequired);
    client->setConnectionImpl(conn);
    client->registerConnectionListener(this);
    client->registerMessageHandler(this);

    client->connect(false);

    pthread_mutex_lock(&stop_mutex);
    stop = false;
    pthread_mutex_unlock(&stop_mutex);
    pthread_create(&reciver, NULL, polling_thread, (void*) client);
    pthread_mutex_lock(&connect_mutex);
}

XMPPconnection::~XMPPconnection()
{
    pthread_mutex_lock(&stop_mutex);
    stop = true;
    pthread_mutex_unlock(&stop_mutex);
    stringstream msg;
    msg << "(Not expected) XMPP destructor.";
    //while(pthread_cancel(reciver) != 0);
    pthread_join(reciver, NULL);
    delete client;
    delete sink;
}

void XMPPconnection::disconnect()
{
    client->disconnect();
}

void XMPPconnection::sendMessage(JID jid, const char* message)
{
    client->send(Message(Message::Chat, jid, string(message)));
}

ConnectionState XMPPconnection::getState()
{
    return client->state();
}

// ConnectionListener

void XMPPconnection::onConnect()
{
    pthread_cond_signal(&connect_var);
    pthread_mutex_unlock(&connect_mutex);
    //connectionWaiting = false;
    stringstream msg;
    msg << "onConnect" << endl;
/*
    RosterManager* rm = client->rosterManager();
    Roster* r = rm->roster();
    for(Roster::const_iterator i = r->begin(); i != r->end(); ++i)
    {
        pair<string, RosterItem* > item = *i;
        string first = item.first;
        RosterItem* ri = item.second;
        msg <<  first <<" - " <<  ri->jid() << endl;
    }

    MessageWindow::getInstance().printWin(msg, Log);*/
}

void XMPPconnection::onDisconnect(ConnectionError e)
{
    string error_message;
    switch(e)
    {
        case ConnNoError:               error_message = "ConnNoError";                 break;
        case ConnStreamError:           error_message = "ConnStreamError ";            break;
        case ConnStreamVersionError:    error_message = "ConnStreamVersionError ";     break;
        case ConnStreamClosed:          error_message = "ConnStreamClosed ";           break;
        case ConnProxyAuthRequired:     error_message = "ConnProxyAuthRequired";       break;
        case ConnProxyAuthFailed:       error_message = "ConnProxyAuthFailed";         break;
        case ConnProxyNoSupportedAuth:  error_message = "ConnProxyNoSupportedAuth";    break;
        case ConnIoError:               error_message = "ConnIoError";                 break;
        case ConnParseError:            error_message = "ConnParseError";              break;
        case ConnConnectionRefused:     error_message = "ConnConnectionRefused";       break;
        case ConnDnsError:              error_message = "ConnDnsError";                break;
        case ConnOutOfMemory:           error_message = "ConnOutOfMemory";             break;
        case ConnNoSupportedAuth:       error_message = "ConnNoSupportedAuth";         break;
        case ConnTlsFailed:             error_message = "ConnTlsFailed";               break;
        case ConnTlsNotAvailable:       error_message = "ConnTlsNotAvailable";         break;
        case ConnCompressionFailed:     error_message = "ConnCompressionFailed";       break;
        case ConnAuthenticationFailed:  error_message = "ConnAuthenticationFailed";
            pthread_cond_signal(&connect_var);
            pthread_mutex_unlock(&connect_mutex);
            //pthread_cancel(reciver);
            break;
        case ConnUserDisconnected:      error_message = "ConnUserDisconnected";        break;
        case ConnNotConnected:          error_message = "ConnNotConnected";            break;
        default:                        error_message = "Unknown error!";
    }

    stringstream msg;
    msg << "onDisconnect: " << error_message << endl;
    //printwin(msg, Log);
    //WindowDecorator::getInstance().PrintWin(msg, Log);
}

void XMPPconnection::onResourceBind(const std::string &resource)
{
    stringstream msg;
    msg << "onResourceBind: " << resource << endl;
    //printwin(msg);
}

void XMPPconnection::onResourceBindError(const Error *error)
{
    stringstream msg;
    msg << "onResourceBindError: " << error->text() << endl;
    MessageWindow::getInstance().printWin(msg, Log);
}

void XMPPconnection::onSessionCreateError(const Error *error)
{
    stringstream msg;
    msg << "onSessionCreateError: " << error->text() << endl;
    MessageWindow::getInstance().printWin(msg, Log);
}

void XMPPconnection::onStreamEvent(StreamEvent event)
{
    stringstream msg;
    //msg << "onStreamEvent" << endl;
}

// from MessageHandler
void XMPPconnection::handleMessage(const Message &msg, MessageSession *session)
{
    if (!msg.body().empty())
    {
        stringstream smsg;
        smsg << msg.from().username() << ": " << msg.body() << endl;
        MessageWindow::getInstance().printWin(smsg, They);
    }
}

