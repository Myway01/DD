#ifndef MAPCONN_H
#define MAPCONN_H

#include <QObject>
#include <QWebEngineView>
#include <QWebChannel>

class MapConn : public QObject
{
    Q_OBJECT
public:
    explicit MapConn(QWebEngineView *mapview, QString name = "QtConn", QObject *parent = nullptr);

signals:
    void sendText(const QString &s);
    void getpos();
    void addCliStart(const QString &lng_start, const QString &lat_start, const QString &startPos, const QString &endPos);
    void removeCliStart();
    void addCli(const QString &lng, const QString &lat);
    void removeCli();
    void sendStart(const QString &lng, const QString &lat);
    void sendEnd(const QString &lng, const QString &lat);

    void mapinfo(const QString &info);
    void setCurPos_sig(const QString &lng, const QString &lat);
    void setDrvInfo_sig(const QString &info);
    void setFare_sig(const QString &fare);
public slots:
    void recvText(const QString &s);
    void setinfo(const QString &info);
    void setFare_slot(const QString &fare);
    void setCurPos_slot(const QString &lng, const QString &lat);
    void setDrvInfo_slot(const QString &info);

};

#endif // WEBCONN_H
