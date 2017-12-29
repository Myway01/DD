#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "LoginWidget.h"
#include "ui_LoginWidget.h"
//#include <QSqlQuery>
//#include <QCryptographicHash>
#include <QDebug>
//#include "DDprocess.h"
#include "Worker.h"
#include "CliInfo.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    ui->pushButton_signin->setShortcut(Qt::Key_Return);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::showinit(){
    ui->lineEdit_username->clear();
    ui->lineEdit_password->clear();
    ui->label_error->clear();
    ui->lineEdit_username->setFocus();
}

/*int LoginWidget::checkIn(const QString &username, const QString &passwor){
    QString md5;
    md5.append((QCryptographicHash::hash(passwor.toLatin1(), QCryptographicHash::Md5)).toHex());
    qDebug() << md5;

    QString password = md5;
    //QString sql = "select password from t001 where username = '" + username + "'";
    QString sql = "select password from t001 where username = :username";
    //防止SQL注入攻击
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":username", username);
    query.exec();
    //query.exec(sql);
    if (!query.next()){
        this->ui->label_error->setText("用户名不存在！");
        this->ui->lineEdit_username->setFocus();
        this->ui->lineEdit_username->selectAll();
        return 1;
    }
    else if (query.value(0).toString() != password){
        this->ui->label_error->setText("密码错误，请重新输入！");
        this->ui->lineEdit_password->setFocus();
        this->ui->lineEdit_password->selectAll();
        return 2;
    }
    else
        return 0;

}*/

void LoginWidget::on_pushButton_signin_clicked()
{
    /*emit login();
    CliInfo *info = CliInfo::getCliInfo();
    strcpy(info->tel, "18322303006");
    return;*/
    QString username = this->ui->lineEdit_username->text();
    QString password = this->ui->lineEdit_password->text();
    if (username.length() != 11){
        if(username.length() == 0){
            this->ui->label_error->setText("请输入用户名！");
            this->ui->lineEdit_username->setFocus();
        }
        else{
            this->ui->label_error->setText("用户名格式错误！");
            this->ui->lineEdit_username->setFocus();
            this->ui->lineEdit_username->selectAll();
        }
        return;
    }
    if (password.length() < 6){
        if(password.length() == 0){
            this->ui->label_error->setText("请输入密码！");
            this->ui->lineEdit_password->setFocus();
        }
        else{
            this->ui->label_error->setText("密码长度不足！");
            this->ui->lineEdit_password->setFocus();
            this->ui->lineEdit_password->selectAll();
        }
        return;
    }
    this->ui->label_error->setText("等待服务器响应...");

    qDebug()<<QThread::currentThread();
    Worker *worker = new Worker();
    connect(this, SIGNAL(login_sig(QString,QString)), worker, SLOT(signinCli(QString,QString)));
    connect(worker, SIGNAL(numret(int)), this, SLOT(login_slot(int)));
    //worker->signinCli(username, password);
    emit login_sig(username, password);
    this->ui->pushButton_signin->setEnabled(false);
    this->ui->pushButton_signup->setEnabled(false);
    return;
}

void LoginWidget::on_pushButton_signup_clicked()
{
    emit signup();
}

void LoginWidget::login_slot(int ret){
    switch (ret) {
    case DD_INTERNETERR:
        this->ui->label_error->setText("网络错误！");
        break;
    case DD_INTERNETTIMEOUT:
        this->ui->label_error->setText("网络连接超时！");
        break;
    case -2:
        this->ui->label_error->setText("用户名不存在！");
        this->ui->lineEdit_username->setFocus();
        this->ui->lineEdit_username->selectAll();
        break;
    case -1:
        this->ui->label_error->setText("密码错误，请重新输入！");
        this->ui->lineEdit_password->setFocus();
        this->ui->lineEdit_password->selectAll();
        break;
    case 0:
        emit login();
        break;
    default:
        this->ui->label_error->setText("未知错误！");
        break;
    }
    this->ui->pushButton_signin->setEnabled(true);
    this->ui->pushButton_signup->setEnabled(true);
    return;
}
