#include "MainWindow.h"
#include <QThread>
#include <sys/statvfs.h>
#include "PXProgressIndicator.h"
#include "MessagebodyWidget.h"
#include "AccountsMessageList.h"


MainWindow::MainWindow(QString defultUrl, QWidget *parent) :
        PXMainWindow("HUB", QIcon::fromTheme("px-hub"), "px-desktop-wiki:page=PantherX-GUI-Library/index.html", parent),
        _defaultUrl(defultUrl){
    buildSidebar();
    topBar()->settingsButtonAction()->setVisible(false);
    topBar()->helpButtonAction()->setVisible(false);
    topBar()->searchBox()->setDisabled(true);
}


bool getFreeDiskSpace(QString path, QString &result){
    struct statvfs fiData;
    if((statvfs(path.toStdString().c_str(),&fiData)) < 0 ) {
        result = "Failed to stat " + path;
        return false;
    } else {
        auto free_kb = (fiData.f_bsize * fiData.f_bfree)/1024;
        float free_gb;
        if(free_kb > 1024){
            auto free_mb = float(free_kb / 1024);
            if(free_mb > 1024){
                free_gb = float(free_mb / 1024);
                result = QString::number(free_gb, 'f', 1)+"GB";
            } else result = QString::number(free_mb)+"MB";
        } else
            result = QString::number(free_kb)+"KB";
        return true;
    }
}

void MainWindow::buildSidebar(){
    auto section = new PXSideBarItem("Accounts",PXSideBarItem::ItemType::Item, nullptr);
    addItemToSideBar(section);
    AccountObject nopAccount;
    auto overViewMessageList = new AccountsMessageList(nopAccount,true);
    auto overView = new PXSideBarItem("Overview",PXSideBarItem::ItemType::Subitem, overViewMessageList);
    addItemToSideBar(overView);
    overViewMessageList->setAttribute(Qt::WA_Hover);
    connect(overViewMessageList, &AccountsMessageList::messageClicked, [&](const MessageObject &msg,const  AccountObject &acc){            
            auto messageBodyWidget = new MessageBodyWidget(msg,acc);
            addContent(messageBodyWidget);
        });
    setDefaultItem(overView);
    RPCHubClient rpcHubClient;
    vector<AccountObject> accountList= rpcHubClient.getAccountList();
    for(auto account:accountList){
        auto accountMessageList = new AccountsMessageList(account,false);
        auto item = new PXSideBarItem(account.getTitle().c_str(), PXSideBarItem::ItemType::Subitem, accountMessageList);
        item->setIcon(QIcon::fromTheme(account.getIcon().c_str()));
        addItemToSideBar(item);
        
        if(!_defaultUrl.isEmpty()){
            if(account.getTitle() == _defaultUrl.toStdString()){
                setDefaultItem(item);                 
            }
        }
        connect(accountMessageList, &AccountsMessageList::messageClicked, [&](const MessageObject &msg,const  AccountObject &acc){            
            auto messageBodyWidget = new MessageBodyWidget(msg,acc);
            addContent(messageBodyWidget);
        });       
    }
} 

PXContentWidget *MainWindow::buildView(){
    auto label = new QLabel("Content Area");
    label->setStyleSheet("QLabel{color: red}");
    label->setFont(QFont("default", 32, QFont::Normal));
    auto layout = new QHBoxLayout;
    layout->addWidget(label);
    layout->setAlignment(Qt::AlignCenter);
    auto widget = new PXContentWidget("Search Box");
    widget->setLayout(layout);
    widget->setAttribute(Qt::WA_Hover);
    return widget;
}

QWidget *MainWindow::buildSidebarWidget(){
    auto label = new QLabel("Label", this);
    auto button = new QPushButton("Button", this);
    auto edit = new QLineEdit(this);

    auto layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(button);
    layout->addWidget(edit);
    auto widget = new QWidget(this);
    widget->setLayout(layout);

    return widget;
}

MainWindow::~MainWindow() {
}

void MainWindow::searchBoxTextEdited(const QString &text){
    qDebug() << contentWidget()->currentWidget() << text;
}

// void MainWindow::settingsButtonPressed() {
//     qDebug() << "Settings Button Handler";
//     setSideBarVisible(!isSideBarVisible());
// }

void MainWindow::sideBarItemHandler (QListWidgetItem* item){
    PXMainWindow::sideBarItemHandler(item);
}
