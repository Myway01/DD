#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "LoginWidget.h"
#include "ui_LoginWidget.h"
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QDebug>

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

int LoginWidget::checkIn(const QString &username, const QString &passwor){
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
}

void LoginWidget::on_pushButton_signin_clicked()
{
    if (checkIn(QString(this->ui->lineEdit_username->text()), QString(this->ui->lineEdit_password->text())) == 0)
        emit login();
}

void LoginWidget::on_pushButton_signup_clicked()
{
    emit signup();
}
