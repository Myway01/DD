#ifndef WORKER_H
#define WORKER_H

#define DD_INTERNETERR 3211 //网络错误
#define DD_INTERNETTIMEOUT 3210 //网络超时
#define SERVERADDR "192.168.246.128"
#define SERVERPORT 8001

#include <QObject>
#include <QThread>
#include "TcpClient.h"
#include "DDstructs.h"

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);
    virtual ~Worker();

signals:
    void numret(int);
    void addCliStart_sig(const QString &lng_start, const QString &lat_start, const QString &startPos, const QString &endPos);
    void removeCliStart_sig();
    void addCli_sig(const QString &lng, const QString &lat);
    void removeCli_sig();
    void getinfo_sig();

public slots:
    void signinDrv(const QString &username, const QString &password);
    void signupDrv(const QString &tel, const QString &nickname, const QString &card, const QString &psw, const QString &paypsw);
    void listen(const QString &lng, const QString &lat);
    void sendPos(const QString &lng, const QString &lat);
    void quit();
    void delPos();
    void sendState(int state);
    void getinfo_slot();

private:
    TcpClient *c;
    QThread *_thread;
    int ret;
    //bool message(int ret);
};

#endif // WORKER_H
