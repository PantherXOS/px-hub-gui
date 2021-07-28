#include "AccountsMessageList.h"

AccountsMessageList::AccountsMessageList(AccountObject account) :
 PXContentWidget(account.getTitle().c_str()){
     RPCHubClient rpcHubClient;
     vector<MessageObject> messageList = rpcHubClient.getAllMessageList(account.getTitle().c_str(), MAX_MESSAGE_COUNT);
     cout<<"*************"<<messageList.size()<<endl;
     QListWidget* listWidget = new QListWidget();
        listWidget->setStyleSheet(QString::fromStdString("QListWidget {background-color:transparent;}"));
        for(auto &m : messageList){
            auto widgwtItem = new QListWidgetItem();
            listWidget->addItem(widgwtItem);
            auto messageItem = new AccountsMessageListItem(m,(600 - listWidget->horizontalScrollBar()->size().height()-50)); 
            
            //messageHeightSize = messageItem->sizeHint().height();
            listWidget->setItemWidget(widgwtItem,messageItem);
            widgwtItem->setSizeHint(messageItem->size()); 
        }
        auto layout = new QVBoxLayout();
        //layout->addWidget(searchTextEdit);
        layout->addWidget(listWidget);
        layout->setAlignment(Qt::AlignTop);
        setLayout(layout);

}