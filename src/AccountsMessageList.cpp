#include "AccountsMessageList.h"

AccountsMessageList::AccountsMessageList(AccountObject account) :
 PXContentWidget(account.getTitle().c_str()), accountObject(account){
     RPCHubClient rpcHubClient;
     vector<MessageObject> messageList = rpcHubClient.getAllMessageList(account.getID().c_str(), MAX_MESSAGE_COUNT);
     QListWidget* listWidget = new QListWidget();
        listWidget->setStyleSheet(QString::fromStdString("QListWidget {background-color:transparent;}"));
        for(auto &m : messageList){
            // auto widgwtItem = new QListWidgetItem();
            // listWidget->addItem(widgwtItem);
            auto messageItem = new AccountsMessageListItem(m,(600 - listWidget->horizontalScrollBar()->size().height()-50)); 
            listWidget->addItem(messageItem);
            //messageHeightSize = messageItem->sizeHint().height();
            listWidget->setItemWidget(messageItem,messageItem->getWidget());
            messageItem->setSizeHint(messageItem->getWidget()->size()); 
        }
        connect(listWidget, SIGNAL(itemPressed(QListWidgetItem *)),this, SLOT(itemClickedHandler(QListWidgetItem *)));
        auto layout = new QVBoxLayout();
        //layout->addWidget(searchTextEdit);
        layout->addWidget(listWidget);
        layout->setAlignment(Qt::AlignTop);
        setLayout(layout);

}
 AccountObject AccountsMessageList::getAccountObject(){
     return(accountObject);
 }

void AccountsMessageList::itemClickedHandler(QListWidgetItem *item){
    auto messageItem = (AccountsMessageListItem*)item;
    emit messageClicked(messageItem->getMessage(),accountObject);
}