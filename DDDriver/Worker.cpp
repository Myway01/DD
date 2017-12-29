#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "Worker.h"
#include <QCryptographicHash>
#include <QMessageBox>
#include <QDebug>
#include "DrvInfo.h"

//用于检测用户是否重新执行网络操作，需要TcpClient函数的返回值存入ret变量，执行结构为循环体，重试则重新执行循环体内容，否则退出循环体
#define DD_INTTEST \
    if (ret < 0) { \
        if(ret == -2) emit numret(DD_INTERNETTIMEOUT); \
        else emit numret(DD_INTERNETERR); \
        _thread->quit(); \
        return; \
}

Worker::Worker(QObject *parent) : QObject(parent)
{
    _thread = new QThread();
    this->moveToThread(_thread);
    _thread->start();
    connect(_thread, SIGNAL(finished()), _thread, SLOT(deleteLater()));
    connect(_thread, SIGNAL(finished()), this, SLOT(deleteLater()));
    QString str = SERVERADDR;
    QByteArray ba = str.toLocal8Bit();
    char *addr = ba.data();   //得到c风格字符串
    c = new TcpClient(addr, SERVERPORT, 5);
}
Worker::~Worker(){
    qDebug()<<"worker end";
    if (_thread->isRunning()){qDebug()<<"_thread is running";}
    else qDebug()<<"thread end";
    qDebug()<<QThread::currentThread();
    delete c;
}

void Worker::quit(){
    _thread->quit();
}

/*bool Worker::message(int ret){
    if (ret == 0)
        return false;
    QMessageBox msgBox;
    if (ret == -1){
        msgBox.setText("网络出错！");
        msgBox.setInformativeText("是否重新连接？");
    }
    else if (ret == -2){
        msgBox.setText("网络超时！");
        msgBox.setInformativeText("是否重新连接？");
    }
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    msgBox.setButtonText(QMessageBox::Yes, "是");
    msgBox.setButtonText(QMessageBox::No, "否");

    if (msgBox.exec() == QMessageBox::Yes) {
        return true;
    } else {
        return false;
    }
}*///线程中无法执行ui操作
//返回值 DD_INTERNETERR：网络错误 -2：用户名错误 -1：密码错误 0：成功
void Worker::signinDrv(const QString &username, const QString &password){
    //qDebug()<<QThread::currentThread();
    //qDebug()<<c->state<<SERVERADDR;
    ret = c->state;DD_INTTEST
    //qDebug()<<"connect success\n";

    char type = DD_LOGIN_DRV;
    ret = c->Send(&type, 1, 3);DD_INTTEST

    struct DD_login_cli lg;
    QString md5;
    md5.append((QCryptographicHash::hash(password.toLatin1(), QCryptographicHash::Md5)).toHex());
    qDebug() << md5;
    strcpy(lg.tel, username.toLocal8Bit().data());
    strcpy(lg.psw, md5.toLocal8Bit().data());
    ret = c->Send((char*)&lg, sizeof(lg), 3);DD_INTTEST

    ret = c->Recv(&type, 1, 3);DD_INTTEST
    if(type < 0){
        emit numret((int)type);
        _thread->quit();
        return;
    }

    struct DD_drvinfo dinfo;
    DrvInfo *info = DrvInfo::getDrvInfo();
    ret = c->Recv((char*)&dinfo, sizeof(dinfo), 3);DD_INTTEST
    strcpy(info->tel, username.toLocal8Bit().data());
    strcpy(info->nickname, dinfo.nickname);
    strcpy(info->card, dinfo.card);
    strcpy(info->bal, dinfo.bal);
    qDebug()<<info->tel<<info->nickname<<info->bal<<info->card;
    emit numret(0);
    _thread->quit();
    return;
}

void Worker::signupDrv(const QString &tel, const QString &nickname, const QString &card, const QString &psw, const QString &paypsw){
    ret = c->state;DD_INTTEST

    char type = DD_SIGNUP_DRV;
    ret = c->Send(&type, 1, 3);DD_INTTEST

    struct DD_signup_drv su;
    QString pswmd5, paypswmd5;
    pswmd5.append((QCryptographicHash::hash(psw.toLatin1(), QCryptographicHash::Md5)).toHex());
    paypswmd5.append((QCryptographicHash::hash(paypsw.toLatin1(), QCryptographicHash::Md5)).toHex());
    qDebug() << pswmd5 << paypswmd5;
    strcpy(su.tel, tel.toLocal8Bit().data());
    strcpy(su.nickname, nickname.toLocal8Bit().data());
    strcpy(su.card, card.toLocal8Bit().data());
    strcpy(su.psw, pswmd5.toLocal8Bit().data());
    strcpy(su.paypsw, paypswmd5.toLocal8Bit().data());
    ret = c->Send((char*)&su, sizeof(su), 3); DD_INTTEST

    ret = c->Recv(&type, 1, 3); DD_INTTEST
    emit numret((int)type);
    _thread->quit();
    return;
}

void Worker::listen(const QString &lng, const QString &lat){
    ret = c->state;DD_INTTEST

    char type = DD_LISTEN_DRV;
    ret = c->Send(&type, 1, 3);DD_INTTEST

    struct DD_geo geo;
    DrvInfo *info = DrvInfo::getDrvInfo();
    strcpy(geo.name, info->tel);
    strcpy(geo.lng, lng.toLocal8Bit().data());
    strcpy(geo.lat, lat.toLocal8Bit().data());
    ret = c->Send((char*)&geo, sizeof(geo), 3);DD_INTTEST

    ret = c->Recv((char*)&geo, sizeof(geo), 3);DD_INTTEST
    if (strcmp(geo.name, "0") == 0) {
        emit addCliStart_sig("null", "", "", "");
    }
    else {
        strcpy(info->clitel, geo.name);
        char bufs[128];
        ret = c->Recv(bufs, 128, 3);DD_INTTEST//起点
        qDebug()<<"bufs"<<bufs;
        char bufe[128];
        ret = c->Recv(bufe, 128, 3);DD_INTTEST//终点
        char bufn[21];
        ret = c->Recv(bufn, 21, 3);DD_INTTEST//顾客姓名
        strcpy(info->clinickname, bufn);
        emit addCliStart_sig(QString(geo.lng), QString(geo.lat), QString(bufs), QString(bufe));
    }
        //qDebug()<<"recvgeo:"<<geo.name<<geo.lng<<geo.lat;
        //qDebug()<<geo.name<<strcmp(geo.name, "0");
    emit numret(0);
    return;
}

void Worker::delPos(){
    ret = c->state;DD_INTTEST

    char type = DD_DELPOS_DRV;
    ret = c->Send(&type, 1, 3);DD_INTTEST

    DrvInfo *info = DrvInfo::getDrvInfo();
    ret = c->Send(info->tel, 12, 3);DD_INTTEST
    emit numret(0);
    _thread->quit();
}

void Worker::sendState(int state){
    ret = c->state;DD_INTTEST

    char type = DD_SENDSTATE_DRV;
    ret = c->Send(&type, 1, 3);DD_INTTEST

    DrvInfo *info = DrvInfo::getDrvInfo();
    ret = c->Send(info->clitel, 12, 3);DD_INTTEST

    switch (state){
        case 0: type = '0'; break;
        case 1: type = '1'; break;
        case 2: type = '2'; break;
        case 3: type = '3'; break;
    }

    ret = c->Send(&type, 1, 3);DD_INTTEST

    switch (state){
        case 1: ret = c->Send(info->tel, 12, 3);DD_INTTEST break;
        case 2: ret = c->Send(info->tel, 12, 3);DD_INTTEST break;
        case 3: ret = c->Send(info->fare, 8, 3);DD_INTTEST break;
    }
    emit numret(0);
    _thread->quit();
}

void Worker::sendPos(const QString &lng, const QString &lat){
    ret = c->state;DD_INTTEST

    char type = DD_SENDPOS_DRV;
    ret = c->Send(&type, 1, 3);DD_INTTEST

    struct DD_geo geo;
    DrvInfo *info = DrvInfo::getDrvInfo();
    strcpy(geo.name, info->tel);
    strcpy(geo.lng, lng.toLocal8Bit().data());
    strcpy(geo.lat, lat.toLocal8Bit().data());
    ret = c->Send((char*)&geo, sizeof(geo), 3);DD_INTTEST
    ret = c->Send(info->clitel, 12, 3);DD_INTTEST

    ret = c->Recv((char*)&geo, sizeof(geo), 3);DD_INTTEST
    qDebug()<<"recvcli:"<<geo.name<<geo.lng<<geo.lat;
    if (strcmp(geo.name, "0") == 0) {
        emit(0);
        return;
    }
    emit addCli_sig(QString(geo.lng), QString(geo.lat));
    emit numret(0);
}

void Worker::getinfo_slot(){
    ret = c->state;DD_INTTEST

    char type = DD_GETINFO_DRV;
    ret = c->Send(&type, 1, 3);DD_INTTEST

    DrvInfo *info = DrvInfo::getDrvInfo();
    ret = c->Send(info->tel, 12, 3);DD_INTTEST

    ret = c->Recv(info->bal, 12, 3);DD_INTTEST
    emit getinfo_sig();
    emit(0);
    _thread->quit();
}

