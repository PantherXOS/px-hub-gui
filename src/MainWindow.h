#ifndef EXAMPLE_MAINWINDOW
#define EXAMPLE_MAINWINDOW

#include <QPushButton>
#include <QLineEdit>

#include "PXMainWindow.h"
#include "PXSideBarItem.h"
#include "RPCHubClient.h"
#include "AccountsMessageList.h"

class MainWindow : public PXMainWindow {
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    void             buildSidebar();
    QWidget         *buildSidebarWidget();
    PXContentWidget *buildView();

private slots:
    void searchBoxTextEdited(const QString&) override;
    void settingsButtonPressed() override;
    void sideBarItemHandler     (QListWidgetItem*) override;
};

#endif //EXAMPLE_MAINWINDOW
