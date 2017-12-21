#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "DDprocess.h"
#include <QCryptographicHash>
#include <QMessageBox>
#include <QDebug>
#include "CliInfo.h"

//用于检测用户是否重新执行网络操作，需要TcpClient函数的返回值存入ret变量，执行结构为循环体，重试则重新执行循环体内容，否则退出循环体
#define DD_INTTEST \
    if (ret < 0) { \
        if(message(ret)) continue; \
        else break; \
}

QString str = "192.168.246.128";
QByteArray ba = str.toLocal8Bit();
char* SERVERADDR = ba.data();
unsigned int SERVERPORT = 8001;

bool message(int ret){
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
}
//返回值 DD_INTERNETERR：网络错误 -2：用户名错误 -1：密码错误 0：成功
int signinCli(const QString &username, const QString &password){
    while(1){
        TcpClient *c = new TcpClient(SERVERADDR, SERVERPORT, 5);
        int ret = 0;
        //qDebug()<<c->state<<SERVERADDR;
        ret = c->state;DD_INTTEST
        //qDebug()<<"lianjiezhengchang\n";

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
        if(type < 0) return type;

        struct DD_info_cli cinfo;
        CliInfo *info = CliInfo::getCliInfo();
        ret = c->Recv((char*)&cinfo, sizeof(cinfo), 3);DD_INTTEST
        strcpy(info->tel, username.toLocal8Bit().data());
        strcpy(info->nickname, cinfo.nickname);
        strcpy(info->bal, cinfo.bal);
        qDebug()<<info->tel<<info->nickname<<info->bal;
        return 0;
    }
    return DD_INTERNETERR;
}

