#include <QApplication>
#include <QDebug>
#include <QTextCodec>
#include "MainWidget.h"
#include "TcpClient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    WinsockStart();

    MainWidget mw;
    mw.show();

    return a.exec();
}
