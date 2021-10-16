//
// Created by fakhri on 12/15/19.
//

#include "RPCHubClient.h"

#define HUB_SERVER_ADDRESS string("unix:") + "/tmp/" + string(getenv("USER")) + "/rpc/hub"

vector<AccountObject> RPCHubClient::getAccountList() {
    vector<AccountObject> rsult;
    string addr = HUB_SERVER_ADDRESS;
    capnp::EzRpcClient rpcClient(addr);
    auto &waitScope = rpcClient.getWaitScope();
    HubReader::Client client = rpcClient.getMain<HubReader>();
    try {
        auto actReq = client.getAccountsStatusRequest();
        auto actRes = actReq.send().wait(waitScope);
        for(auto act : actRes.getAccountsStatus()) {
            AccountObject account;
            switch (act.getStatus()){
                case HUBAccountStatus::Status::NONE:
                    account.setStatus(Status::none);
                    break;
                case HUBAccountStatus::Status::ERROR:
                    account.setStatus(Status::error);
                    break;
                case HUBAccountStatus::Status::ONLINE:
                    account.setStatus(Status::online);
                    break;
                case HUBAccountStatus::Status::OFFLINE:
                    account.setStatus(Status::offline);
                    break;
            }
            account.setTime(act.getTime().cStr());
            account.setUnread(act.getUnread());
            account.setType(act.getType().cStr());
            account.setIcon(act.getIcon().cStr());
            account.setLink(act.getLink().cStr());
            account.setAltLink(act.getAltLink().cStr());
            account.setTitle(act.getAccountInfo().getTitle().cStr());
            account.setID(act.getAccountInfo().getId().cStr());
            rsult.push_back(account);
        }
    } catch (kj::Exception e){
        cout << e.getDescription().cStr() << endl;
    }
    return rsult;
}

vector<MessageObject> RPCHubClient::getMessageList(int n) {
    vector<MessageObject> messageList;
    string addr = HUB_SERVER_ADDRESS;
    capnp::EzRpcClient rpcClient(addr);
    auto &waitScope = rpcClient.getWaitScope();
    HubReader::Client client = rpcClient.getMain<HubReader>();
    try {
        auto msgReq = client.getLastMessagesRequest();
        msgReq.setCount(n);
        auto msgRes = msgReq.send().wait(waitScope);
        for(auto msg : msgRes.getMessages()){
            MessageObject msgObj;
            msgObj.setIcon(msg.getIcon().cStr());
            msgObj.setMessage(msg.getMessage().cStr());
            msgObj.setSender(msg.getSender().cStr());
            msgObj.setLink(msg.getLink().cStr());
            msgObj.setAltLink(msg.getAltLink().cStr());
            msgObj.setTime(msg.getTime().cStr());
            msgObj.setUnread(msg.getUnread());
            msgObj.setMsgId(msg.getMsgId());
            messageList.push_back(msgObj);
        }
    } catch (kj::Exception e){
        cout << e.getDescription().cStr() << endl;
    }
    return messageList;
}

vector<MessageObject> RPCHubClient::getAllMessageList(string acc,int n){
    vector<MessageObject> messageList;
    string addr = HUB_SERVER_ADDRESS;
    capnp::EzRpcClient rpcClient(addr);
    auto &waitScope = rpcClient.getWaitScope();
    HubReader::Client client = rpcClient.getMain<HubReader>();
    try {
        auto msgReq = client.getAllMessagesRequest();
        msgReq.setCount(n);
        msgReq.setAccountID(acc);
        auto msgRes = msgReq.send().wait(waitScope);
        for(auto msg : msgRes.getMessages()){
            MessageObject msgObj;
            msgObj.setIcon(msg.getIcon().cStr());
            msgObj.setMessage(msg.getMessage().cStr());
            msgObj.setSender(msg.getSender().cStr());
            msgObj.setLink(msg.getLink().cStr());
            msgObj.setAltLink(msg.getAltLink().cStr());
            msgObj.setTime(msg.getTime().cStr());
            msgObj.setUnread(msg.getUnread());
            msgObj.setMsgId(msg.getMsgId());
            messageList.push_back(msgObj);
        }
    } catch (kj::Exception e){
        cout << e.getDescription().cStr() << endl;
    }
    return messageList;

}

MessageObject         RPCHubClient::getMessage(string acountId,string messageId){
    string addr = HUB_SERVER_ADDRESS;
    capnp::EzRpcClient rpcClient(addr);
    auto &waitScope = rpcClient.getWaitScope();
    HubReader::Client client = rpcClient.getMain<HubReader>();
    MessageObject msgObj;
    try {
        auto msgReq = client.getMessageRequest();
        msgReq.setAccountID(acountId);
        msgReq.setMsgId(messageId);
        auto msgRes = msgReq.send().wait(waitScope);
        auto message = msgRes.getMessage();
            msgObj.setIcon(message.getIcon().cStr());
            msgObj.setMessage(message.getMessage().cStr());
            msgObj.setSender(message.getSender().cStr());
            msgObj.setLink(message.getLink().cStr());
            msgObj.setAltLink(message.getAltLink().cStr());
            msgObj.setTime(message.getTime().cStr());
            msgObj.setUnread(message.getUnread());
            msgObj.setMsgId(message.getMsgId());
    } catch (kj::Exception e){
        cout << e.getDescription().cStr() << endl;
    }
    return msgObj;
}
