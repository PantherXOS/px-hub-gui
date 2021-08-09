#ifndef PX_HUB_GUI_MESSAGEBODYWIDGET_H
#define PX_HUB_GUI_MESSAGEBODYWIDGET_H

#include <QDebug>
#include <QString>
#include <QWidgetAction>
#include <QHBoxLayout>
#include <QLabel>
#include <QFont>
#include <QtGui/QDesktopServices>
#include <QUrl>
#include <QMouseEvent>
#include <QDateTime>
#include <string>
#include <QtWidgets/QWidgetAction>
#include <QScrollBar>
#include <QFrame>
#include <QFont>
#include <QIcon>
#include <QListWidget>
#include <QTextEdit>

#include "Settings.h"
#include "MessageObject.h"
#include "PXContentWidget.h"
#include "PXSeperator.h"

class MessageBodyWidget : public PXContentWidget
{
    Q_OBJECT
public:
    MessageBodyWidget(const MessageObject &message, const AccountObject &account, PXContentWidget *parent = nullptr) : PXContentWidget((account.getTitle()+"/"+message.getSender()).c_str(), parent)
    {
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        
        messageLink = QString::fromStdString(message.getLink());
        auto messageSender = new QLabel;
        QFont messageSenderFont = messageSender->font();
        messageSenderFont.setPointSize(CONTENT_MSG_SENDER_FONT_SIZE);

        QFont messageTimeFont = messageSender->font();
        messageTimeFont.setPointSize(CONTENT_MSG_TIME_FONT_SIZE);

        QFont messageContentFont = messageSender->font();
        messageContentFont.setPointSize(CONTENT_MSG_FONT_SIZE);
       
        string acc = message.getSender();
        if (acc.size() > MAX_ACCOUNT_SIZE)
            acc = acc.substr(0, MAX_ACCOUNT_SIZE) + "...";
        messageSender->setText(QString::fromStdString(acc));
        messageSender->setFont(messageSenderFont);

        auto from = new QLabel();
        QFont fromFont = messageSender->font();
        fromFont.setPointSize(CONTENT_TITLE_FONT_SIZE);
        fromFont.setBold(true);
        from->setText(QString::fromStdString("From : "));
        from->setFont(fromFont);

        auto llayout = new QHBoxLayout;
         llayout->addWidget(from);
        llayout->addWidget(messageSender);
        llayout->setAlignment(Qt::AlignLeft);
        llayout->setMargin(0);
        llayout->setSpacing(0);
        llayout->setContentsMargins(0, 0, 0, 0);
        

        auto messageReciever = new QLabel;
        string racc =account.getTitle();
        if (racc.size() > MAX_ACCOUNT_SIZE)
            racc = racc.substr(0, MAX_ACCOUNT_SIZE) + "...";
        messageReciever->setText(QString::fromStdString(racc));
        messageReciever->setFont(messageSenderFont);


        auto reciver = new QLabel();
        QFont reciverFont = messageSender->font();
        reciverFont.setPointSize(CONTENT_TITLE_FONT_SIZE);
        reciverFont.setBold(true);
        reciver->setText(QString::fromStdString("To      : "));
        reciver->setFont(reciverFont);

        auto tolayout = new QHBoxLayout;
        tolayout->addWidget(reciver);
        tolayout->addWidget(messageReciever);
        tolayout->setAlignment(Qt::AlignLeft);
        tolayout->setMargin(0);
        tolayout->setSpacing(0);
        tolayout->setContentsMargins(0, 0, 0, 0);

        auto date = new QLabel();
        QFont dateFont = messageSender->font();
        dateFont.setPointSize(CONTENT_TITLE_FONT_SIZE);
        dateFont.setBold(true);
        date->setText(QString::fromStdString("Date : "));
        date->setFont(dateFont);

        auto messageTime = new QLabel;
        getVisibleTime(QString::fromStdString(message.getTime()));
        messageTime->setText(getVisibleTime(QString::fromStdString(message.getTime())));
        messageTime->setFont(messageTimeFont);

        auto rlayout = new QHBoxLayout;
        rlayout->addWidget(date);
        rlayout->addWidget(messageTime);
        rlayout->setAlignment(Qt::AlignLeft);
        rlayout->setMargin(0);
        rlayout->setSpacing(0);
        rlayout->setContentsMargins(0, 0, 0, 0);

        QFontMetrics fm(messageContentFont);
        int textWidth = fm.horizontalAdvance(QString::fromStdString(message.getMessage()));
        auto _msg = message.getMessage();

        auto messageContent = new QTextEdit;
        messageContent->setText(QString::fromStdString(_msg));
        messageContent->setFont(messageContentFont);
        messageContent->setAlignment(Qt::AlignTop);
        messageContent->setReadOnly(true);
        //messageContent->setWordWrap(true);
        messageContent->setContentsMargins(0, 0, 0, 0);

        
        auto Tlayout = new QVBoxLayout;
        Tlayout->addLayout(llayout);
        Tlayout->addLayout(tolayout);
        Tlayout->addLayout(rlayout);
        //Tlayout->addWidget(messageContent);
        Tlayout->setAlignment(Qt::AlignTop);
        Tlayout->setMargin(0);
        Tlayout->setSpacing(0);
        Tlayout->setContentsMargins(7, 0, 0, 0);

        auto messagelayout = new QVBoxLayout;
        messagelayout->addWidget(messageContent);
        messagelayout->setAlignment(Qt::AlignTop);
        messagelayout->setMargin(0);
        messagelayout->setSpacing(0);
        messagelayout->setContentsMargins(7, 0, 0, 0);

        auto glayout = new QVBoxLayout;
        //glayout->addLayout(ilayout);
        glayout->addLayout(Tlayout);
        glayout->addLayout(messagelayout);
        glayout->setMargin(5);
        glayout->setSpacing(4);
        // glayout->setContentsMargins(0,0,0,0);
       PXSeperator* pxSeorator = new PXSeperator();
        auto flayout = new QVBoxLayout;
        flayout->addLayout(glayout);
       // flayout->addLayout(sepraterlayout);
        flayout->setMargin(0);
        flayout->setSpacing(0);
        flayout->setContentsMargins(0, 0, 0,0);


        setObjectName(QString::fromStdString("PxHubItem"));
        setLayout(flayout);
        setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        setAttribute(Qt::WA_Hover);
        setMouseTracking(true);
    }

    QLabel *buildIconFromTheme(QString icon, QSize size)
    {
        QIcon qicon = QIcon::fromTheme(icon);
        QPixmap pixmap = qicon.pixmap(size, QIcon::Normal, QIcon::On);
        auto iconLabel = new QLabel;
        iconLabel->setAttribute(Qt::WA_TranslucentBackground);
        iconLabel->setPixmap(pixmap);
        iconLabel->setFixedSize(size);
        return iconLabel;
    }

    QString getMessageLink()
    {
        return messageLink;
    }

private:
    QString messageLink;
    QString getVisibleTime(QString messageTime)
    {
        QDateTime dt = QDateTime::fromString(messageTime,
                                             Qt::ISODate)
                           .toLocalTime();
        QString result;
        qint64 secDifference = dt.secsTo(QDateTime::currentDateTime());
        if ((secDifference / 60) > 60)
        {
            int hour = secDifference / 3600;
            if (hour < 24)
                result = dt.toString(QString::fromStdString("ddd  dd.MM  h:mm a"))+ QString::fromStdString(" ( ")+QString::number(secDifference / 3600) + QString::fromStdString("h ago )");
            else{
                 qint64 dayDifference = dt.daysTo(QDateTime::currentDateTime());
                result = dt.toString(QString::fromStdString("ddd  dd.MM  h:mm a"))+QString::fromStdString(" ( ")+QString::number(dayDifference) + QString::fromStdString("days ago )");;
            }
        }
        else
        {
           
            result = dt.toString(QString::fromStdString("ddd  dd.MM  h:mm a"))+ QString::fromStdString(" ( ")+QString::number(secDifference / 60) + QString::fromStdString("m ago )");
        }
        return result;
        // }
    }
};

#endif //PX_HUB_GUI_MESSAGEBODYWIDGET_H