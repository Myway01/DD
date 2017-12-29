#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "Worker.h"
#include <QCryptographicHash>
#include <QMessageBox>
#include <QDebug>
#include "CliInfo.h"

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
void Worker::signinCli(const QString &username, const QString &password){
    qDebug()<<QThread::currentThread();
    qDebug()<<c->state<<SERVERADDR;
    ret = c->state;DD_INTTEST
    //qDebug()<<"connect success\n";

    char type = DD_LOGIN_CLI;
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

    struct DD_info_cli cinfo;
    CliInfo *info = CliInfo::getCliInfo();
    ret = c->Recv((char*)&cinfo, sizeof(cinfo), 3);DD_INTTEST
    strcpy(info->tel, username.toLocal8Bit().data());
    strcpy(info->nickname, cinfo.nickname);
    strcpy(info->bal, cinfo.bal);
    qDebug()<<info->tel<<info->nickname<<info->bal;
    emit numret(0);
    _thread->quit();
    return;
}

void Worker::signupCli(const QString &tel, const QString &nickname, const QString &psw, const QString &paypsw){
    ret = c->state;DD_INTTEST

    char type = DD_SIGNUP_CLI;
    ret = c->Send(&type, 1, 3);DD_INTTEST

    struct DD_signup_cli su;
    QString pswmd5, paypswmd5;
    pswmd5.append((QCryptographicHash::hash(psw.toLatin1(), QCryptographicHash::Md5)).toHex());
    paypswmd5.append((QCryptographicHash::hash(paypsw.toLatin1(), QCryptographicHash::Md5)).toHex());
    qDebug() << pswmd5 << paypswmd5;
    strcpy(su.tel, tel.toLocal8Bit().data());
    strcpy(su.nickname, nickname.toLocal8Bit().data());
    strcpy(su.psw, pswmd5.toLocal8Bit().data());
    strcpy(su.paypsw, paypswmd5.toLocal8Bit().data());
    ret = c->Send((char*)&su, sizeof(su), 3); DD_INTTEST

    ret = c->Recv(&type, 1, 3); DD_INTTEST
    emit numret((int)type);
    _thread->quit();
    return;
}

void Worker::carsPaint(const QString &lng, const QString &lat){
    ret = c->state;DD_INTTEST

    char type = DD_GETCARS_CLI;
    ret = c->Send(&type, 1, 3);DD_INTTEST

    struct DD_geo geo;
    CliInfo *info = CliInfo::getCliInfo();
    strcpy(geo.name, info->tel);
    strcpy(geo.lng, lng.toLocal8Bit().data());
    strcpy(geo.lat, lat.toLocal8Bit().data());
    ret = c->Send((char*)&geo, sizeof(geo), 3);DD_INTTEST

    emit removeCars_sig();

    while(1){
        ret = c->Recv((char*)&geo, sizeof(geo), 3);DD_INTTEST
        if (strcmp(geo.name, "0") == 0) break;
        emit addCar_sig(QString(geo.lng), QString(geo.lat));
        //qDebug()<<"recvgeo:"<<geo.name<<geo.lng<<geo.lat;
        //qDebug()<<geo.name<<strcmp(geo.name, "0");
    } //最后一个DD_geo标记
    emit numret(0);
    return;
}
void Worker::sendPos(const QString &lng, const QString &lat){
    ret = c->state;DD_INTTEST

    char type = DD_SENDPOS_CLI;
    ret = c->Send(&type, 1, 3);DD_INTTEST

    struct DD_geo geo;
    CliInfo *info = CliInfo::getCliInfo();
    strcpy(geo.name, info->tel);
    strcpy(geo.lng, lng.toLocal8Bit().data());
    strcpy(geo.lat, lat.toLocal8Bit().data());
    ret = c->Send((char*)&geo, sizeof(geo), 3);DD_INTTEST
    ret = c->Send(info->drvtel, 12, 3);DD_INTTEST

    ret = c->Recv((char*)&geo, sizeof(geo), 3);DD_INTTEST
    qDebug()<<"recvdrv:"<<geo.name<<geo.lng<<geo.lat;
    emit removeCars_sig();
    emit addCar_sig(QString(geo.lng), QString(geo.lat));
    emit numret(0);

}
void Worker::delOrdPos(){
    ret = c->state;DD_INTTEST

    char type = DD_DELORDPOS_CLI;
    ret = c->Send(&type, 1, 3);DD_INTTEST

    CliInfo *info = CliInfo::getCliInfo();
    ret = c->Send(info->tel, 12, 3);DD_INTTEST
    emit numret(0);
    _thread->quit();    //此为结束发送位置的函数
}
void Worker::sendStartPos(const QString &lng, const QString &lat, const QString &start, const QString &end){
    ret = c->state;DD_INTTEST

    char type = DD_SETSTARTPOS_CLI;
    ret = c->Send(&type, 1, 3);DD_INTTEST

    struct DD_geo geo;
    CliInfo *info = CliInfo::getCliInfo();
    strcpy(geo.name, info->tel);
    strcpy(geo.lng, lng.toLocal8Bit().data());
    strcpy(geo.lat, lat.toLocal8Bit().data());
    ret = c->Send((char*)&geo, sizeof(geo), 3);DD_INTTEST
    char buf[128];
    strcpy(buf, start.toLocal8Bit().data());DD_INTTEST
    ret = c->Send(buf, 128, 3);
    strcpy(buf, end.toLocal8Bit().data());DD_INTTEST
    ret = c->Send(buf, 128, 3);
    qDebug()<<"send:"<<geo.name<<geo.lng<<geo.lat<<start<<end;
    emit numret(0);

    _thread->quit();

}

void Worker::delStartPos(){
    ret = c->state;DD_INTTEST

    char type = DD_DELSTARTPOS_CLI;
    ret = c->Send(&type, 1, 3);DD_INTTEST

    CliInfo *info = CliInfo::getCliInfo();
    ret = c->Send(info->tel, 12, 3);DD_INTTEST
    qDebug()<<"del";
    emit numret(0);

    _thread->quit();
}

void Worker::checkOrd(int state){
    ret = c->state;//DD_INTTEST

    char type = DD_CHECKORD_CLI;
    ret = c->Send(&type, 1, 3);//DD_INTTEST

    CliInfo *info = CliInfo::getCliInfo();
    ret = c->Send(info->tel, 12, 3);//DD_INTTEST
    //发送当前状态
    switch (state){
        case 0: type = '0'; break;
        case 1: type = '1'; break;
        case 2: type = '2'; break;
        case 3: type = '3'; break;
    }
    ret = c->Send(&type, 1, 3);//DD_INTTEST

    char retstate = 0;
    ret = c->Recv(&retstate, 1, 3);//DD_INTTEST
    if (retstate == type){
        return;
    }
    qDebug()<<"retstate:"<<retstate;
    //暂时只实现从0到1，从1到2，和从2到3的转变，  0：呼叫状态 1：被接单状态 2：开始行程状态 3：行程结束
    if (retstate == '1'){
        //drvinfo
        struct DD_info_drv drvinfo;
        ret = c->Recv((char*)&drvinfo, sizeof(drvinfo), 3);//DD_INTTEST
        strcpy(info->drvtel, drvinfo.tel);
        strcpy(info->drvnickname, drvinfo.nickname);
        strcpy(info->drvcard, drvinfo.card);
        qDebug()<<"drvinfo:"<<info->drvtel<<info->drvnickname<<info->drvcard;
        emit haveDriver();
    }
    else if (retstate == '2'){
        //beginOrd
        emit startOrd();
    }
    else if (retstate == '3'){
        //fare
        char fare[8] = {0};
        ret = c->Recv(fare, 8, 3);//DD_INTTEST
        strcpy(info->fare, fare);

        emit endOrd();
    }
    emit numret(0);
}

void Worker::pay(const QString &password){
    ret = c->state;DD_INTTEST

    char type = DD_PAY_CLI;
    ret = c->Send(&type, 1, 3);DD_INTTEST

    struct DD_pay_cli pa;
    CliInfo *info = CliInfo::getCliInfo();
    strcpy(pa.clitel, info->tel);
    strcpy(pa.drvtel, info->drvtel);
    strcpy(pa.fare, info->fare);
    QString md5;
    md5.append((QCryptographicHash::hash(password.toLatin1(), QCryptographicHash::Md5)).toHex());
    qDebug() << md5;
    strcpy(pa.psw, md5.toLocal8Bit().data());
    ret = c->Send((char*)&pa, sizeof(pa), 3);DD_INTTEST

    ret = c->Recv(&type, 1, 3);DD_INTTEST
    qDebug()<<"type"<<int(type);
    emit numret((int)type);
    _thread->quit();
}
