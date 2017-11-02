#include "MainWidget.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("asd123456");
    db.setDatabaseName("Test");
    bool bRet = db.open();
    if(bRet == false){
        qDebug() << "false" << db.lastError().text();
    }
    else
        qDebug() << "true";


    MainWidget mw;
    mw.show();

    return a.exec();
}
