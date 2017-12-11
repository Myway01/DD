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
public slots:
    void recvText(const QString &s);

};

#endif // WEBCONN_H
