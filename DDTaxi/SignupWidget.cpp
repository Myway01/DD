#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "SignupWidget.h"
#include "ui_SignupWidget.h"
#include "Worker.h"

SignupWidget::SignupWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignupWidget)
{
    ui->setupUi(this);
    ui->pushButton_signup->setShortcut(Qt::Key_Return);
}

SignupWidget::~SignupWidget()
{
    delete ui;
}

void SignupWidget::showinit(){
    ui->lineEdit_tel->clear();
    ui->lineEdit_nickname->clear();
    ui->lineEdit_psw->clear();
    ui->lineEdit_cpsw->clear();
    ui->lineEdit_paypsw->clear();
    ui->lineEdit_cpaypsw->clear();
    ui->label_error->clear();
    ui->lineEdit_tel->setFocus();
}

void SignupWidget::on_pushButton_ret_clicked()
{
    emit ret();
}

void SignupWidget::on_pushButton_signup_clicked()
{
    QString username = this->ui->lineEdit_tel->text();
    QString nickname = this->ui->lineEdit_nickname->text();
    QString psw = this->ui->lineEdit_psw->text();
    QString cpsw = this->ui->lineEdit_cpsw->text();
    QString paypsw = this->ui->lineEdit_paypsw->text();
    QString cpaypsw = this->ui->lineEdit_cpaypsw->text();

    if (username.length() != 11){
        if(username.length() == 0){
            this->ui->label_error->setText("请输入手机号码！");
            this->ui->lineEdit_tel->setFocus();
        }
        else{
            this->ui->label_error->setText("手机号码格式错误！");
            this->ui->lineEdit_tel->setFocus();
            this->ui->lineEdit_tel->selectAll();
        }
        return;
    }
    if (nickname.length() == 0){
        this->ui->label_error->setText("请输入您的姓名！");
        this->ui->lineEdit_nickname->setFocus();
        return;
    }
    if (psw.length() < 6){
        if(psw.length() == 0){
            this->ui->label_error->setText("请输入登录密码！");
            this->ui->lineEdit_psw->setFocus();
        }
        else{
            this->ui->label_error->setText("登录密码长度不足！");
            this->ui->lineEdit_psw->setFocus();
            this->ui->lineEdit_psw->selectAll();
            this->ui->lineEdit_cpsw->clear();
        }
        return;
    }
    if (psw != cpsw){
        this->ui->label_error->setText("登录密码两次输入不同！");
        this->ui->lineEdit_psw->setFocus();
        this->ui->lineEdit_psw->selectAll();
        this->ui->lineEdit_cpsw->clear();
        return;
    }
    if (psw.length() != 6){
        if(psw.length() == 0){
            this->ui->label_error->setText("请输入支付密码！");
            this->ui->lineEdit_paypsw->setFocus();
        }
        else{
            this->ui->label_error->setText("支付密码长度错误！");
            this->ui->lineEdit_paypsw->setFocus();
            this->ui->lineEdit_paypsw->selectAll();
            this->ui->lineEdit_cpaypsw->clear();
        }
        return;
    }
    if (paypsw != cpaypsw){
        this->ui->label_error->setText("支付密码两次输入不同！");
        this->ui->lineEdit_paypsw->setFocus();
        this->ui->lineEdit_paypsw->selectAll();
        this->ui->lineEdit_cpaypsw->clear();
        return;
    }
    this->ui->label_error->setText("等待服务器响应...");

    Worker *worker = new Worker();
    connect(this, SIGNAL(signup_sig(QString,QString,QString,QString)), worker, SLOT(signupCli(QString,QString,QString,QString)));
    connect(worker, SIGNAL(numret(int)), this, SLOT(signup_slot(int)));
    emit signup_sig(username, nickname, psw, paypsw);
    this->ui->pushButton_ret->setEnabled(false);
    this->ui->pushButton_signup->setEnabled(false);
    return;
}

void SignupWidget::signup_slot(int ret){
    switch (ret) {
    case DD_INTERNETERR:
        this->ui->label_error->setText("网络错误！");
        break;
    case DD_INTERNETTIMEOUT:
        this->ui->label_error->setText("网络连接超时！");
        break;
    case -2:
        this->ui->label_error->setText("注册失败！");
        this->ui->lineEdit_tel->setFocus();
        this->ui->lineEdit_tel->selectAll();
        break;
    case -1:
        this->ui->label_error->setText("用户名已存在！");
        this->ui->lineEdit_tel->setFocus();
        this->ui->lineEdit_tel->selectAll();
        break;
    case 0:
        this->ui->label_error->setText("注册成功！");
        break;
    default:
        this->ui->label_error->setText("未知错误！");
        break;
    }
    this->ui->pushButton_ret->setEnabled(true);
    this->ui->pushButton_signup->setEnabled(true);
    return;
}
