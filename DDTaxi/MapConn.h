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
    void geoinfo();
    void addcar(const QString &lng, const QString &lat);
    void removecars();

    void mapinfo(const QString &info);
    void setStartPos_sig(const QString &lng, const QString &lat);
    void setCurPos_sig(const QString &lng, const QString &lat);
    void setStartPosStr_sig(const QString &start);
    void setEndPosStr_sig(const QString &end);
public slots:
    void recvText(const QString &s);
    void setinfo(const QString &info);
    void setStartPos_slot(const QString &lng, const QString &lat);
    void setCurPos_slot(const QString &lng, const QString &lat);
    void setStartPosStr_slot(const QString &start);
    void setEndPosStr_slot(const QString &end);

};

#endif // WEBCONN_H
