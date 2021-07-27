//
// Created by fakhri on 12/15/19.
//

#ifndef LXQT_PANEL_RPCHUBCLIENT_H
#define LXQT_PANEL_RPCHUBCLIENT_H
#include <vector>
#include <capnp/ez-rpc.h>
#include <pwd.h>
#include <sys/stat.h>
#include <zconf.h>
#include <AccountParser.h>
#include <hub.capnp.h>
#include "AccountObject.h"
#include "MessageObject.h"

class RPCHubClient {
public:
    vector<AccountObject> getAccountList();
    vector<MessageObject> getMessageList(int n);
};


#endif //LXQT_PANEL_RPCHUBCLIENT_H
