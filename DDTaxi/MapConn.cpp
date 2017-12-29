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

void MapConn::setStartPos_slot(const QString &lng, const QString &lat){
    emit setStartPos_sig(lng, lat);
}
void MapConn::setCurPos_slot(const QString &lng, const QString &lat){
    emit setCurPos_sig(lng, lat);
}
void MapConn::setStartPosStr_slot(const QString &start){
    emit setStartPosStr_sig(start);
}
void MapConn::setEndPosStr_slot(const QString &end){
    emit setEndPosStr_sig(end);
}
