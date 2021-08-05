//
// Created by Fakhri on 2021-07-27.
//

#ifndef PX_HUB_GUI_ACCOUNTSMESSAGELIST_H
#define PX_HUB_GUI_ACCOUNTSMESSAGELIST_H

#include <PXContentWidget.h>
#include <QListWidget>

#include "AccountObject.h"
#include "RPCHubClient.h"
#include "AccountsMessageListItem.h"
#include "Logger.h"
#include "MessagebodyWidget.h"

#define MAX_MESSAGE_COUNT 50

class AccountsMessageList : public PXContentWidget {
Q_OBJECT
public:
    AccountsMessageList(AccountObject account);
    AccountObject getAccountObject();

private slots:

    void itemClickedHandler(QListWidgetItem *item);

signals:
    void messageClicked(const MessageObject &message, const AccountObject &acc);

private:
    AccountObject accountObject;
};

#endif //PX_HUB_GUI_ACCOUNTSMESSAGELIST_H