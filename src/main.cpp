#include <QCommandLineParser>
#include <QApplication>
#include "MainWindow.h"

#include "Logger.h"

#define APPLICATION_NAME    "px-hub-gui"
#define APPLICATION_VERSION "0.0.3"

Logger gLogger(std::string(APPLICATION_NAME));

#define ARG_NAME_PAGE       "account"

QMap<QString, QString> parseUrlScheme(const QString &url) {
    QStringList elements = url.split(':');
    QMap<QString, QString> map;
    if(elements.size() == 2){
        QStringList entries = elements[1].split("?");
        for(const auto &entry : entries) {
            QStringList parts = entry.split('=');
            if(parts.size() == 2) {
                QString result = parts[1];
                if(parts[0] == ARG_NAME_PAGE)
                    map[ARG_NAME_PAGE] = result;
            }
        }
    }
    return map;
}

int main (int argc, char** argv) {
     QMap<QString, QString> urlArgs;
    if(argc > 1) {
        for(int i=0; i<argc; i++)   
            urlArgs.insert(parseUrlScheme(argv[i]));
    }
    auto app = new QApplication(argc, argv);
    QApplication::setApplicationName(APPLICATION_NAME);
    QApplication::setApplicationVersion(APPLICATION_VERSION);

     QCommandLineParser parser;
    parser.setApplicationDescription(APPLICATION_NAME);
    parser.addHelpOption();
    parser.addVersionOption();
    
    QCommandLineOption accountOption(QStringList() << "a" << "account",
                                    "Enter account name for openning as default","account");
    parser.addOption(accountOption);
    parser.process(*app);

    QString acc = (parser.value(accountOption).isEmpty() ? urlArgs[ARG_NAME_PAGE] : parser.value(accountOption));
    
    MainWindow window(acc);
    window.showMaximized();

   
    return app->exec(); 
}
