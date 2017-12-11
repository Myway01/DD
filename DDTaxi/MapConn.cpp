#include "MapConn.h"
#include <QDebug>
MapConn::MapConn(QWebEngineView *mapview, QString name, QObject *parent) : QObject(parent)
{
    QWebChannel* webchannel = new QWebChannel(mapview);
    mapview->page()->setWebChannel(webchannel);
    webchannel->registerObject(name, (QObject*)this);
}

void MapConn::recvText(const QString &s){
    qDebug()<<s;
}
