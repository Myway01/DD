#ifndef WORKER_H
#define WORKER_H

#define DD_INTERNETERR 3211 //网络错误
#define DD_INTERNETTIMEOUT 3210 //网络超时

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

public slots:
    void signinCli(const QString &username, const QString &password);

private:
    QThread *_thread;
    char* SERVERADDR;
    unsigned int SERVERPORT;
    //bool message(int ret);
};

#endif // WORKER_H
