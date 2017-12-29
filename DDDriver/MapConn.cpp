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

void MapConn::setinfo(const QString &info){
    emit mapinfo(info);
}

void MapConn::setCurPos_slot(const QString &lng, const QString &lat){
    emit setCurPos_sig(lng, lat);
}

void MapConn::setDrvInfo_slot(const QString &info){
    emit setDrvInfo_sig(info);
}

void MapConn::setFare_slot(const QString &fare){
    emit setFare_sig(fare);
}
