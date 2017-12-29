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
    void addCar_sig(const QString &lng, const QString &lat);
    void removeCars_sig();
    void haveDriver();//写司机电话
    void startOrd();//行程开始
    void endOrd();//写账单信息

public slots:
    void signinCli(const QString &username, const QString &password);
    void signupCli(const QString &tel, const QString &nickname, const QString &psw, const QString &paypsw);
    void carsPaint(const QString &lng, const QString &lat);
    void sendPos(const QString &lng, const QString &lat);
    void sendStartPos(const QString &lng, const QString &lat, const QString &start, const QString &end);
    void delStartPos();
    void checkOrd(int state);
    void delOrdPos();
    void pay(const QString &password);
    void quit();

private:
    TcpClient *c;
    QThread *_thread;
    int ret;
    //bool message(int ret);
};

#endif // WORKER_H
