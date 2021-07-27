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

#define MAX_MESSAGE_COUNT 50

class AccountsMessageList : public PXContentWidget {
Q_OBJECT
public:
    AccountsMessageList(AccountObject account);

};

#endif //PX_HUB_GUI_ACCOUNTSMESSAGELIST_H