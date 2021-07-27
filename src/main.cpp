#include <QCommandLineParser>
#include <QApplication>
#include "MainWindow.h"

#include "Logger.h"

#define APPLICATION_NAME    "px-hub-gui"
#define APPLICATION_VERSION "0.0.3"

Logger gLogger(std::string(APPLICATION_NAME));

int main (int argc, char** argv) {
    auto app = new QApplication(argc, argv);
    QApplication::setApplicationName(APPLICATION_NAME);
    QApplication::setApplicationVersion(APPLICATION_VERSION);

    MainWindow window;
    window.show();

   
    return app->exec(); 
}
