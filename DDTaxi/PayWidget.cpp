#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "PayWidget.h"
#include "ui_PayWidget.h"

#include "CliInfo.h"
#include "Worker.h"

PayWidget::PayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PayWidget)
{
    ui->setupUi(this);
}

PayWidget::~PayWidget()
{
    delete ui;
}

void PayWidget::showinit(){
    CliInfo *info = CliInfo::getCliInfo();
    QString fare = QString(info->fare) + "元";
    ui->label_fare->setText(fare);
    ui->lineEdit_password->clear();
    ui->pushButton_ret->setText("支付");
    haveCharged = false;

}

void PayWidget::on_pushButton_ret_clicked()
{
    if (!haveCharged){
        pay();
    }
    else{
        emit ret();
    }
}

void PayWidget::pay(){
    Worker *worker = new Worker();
    connect(this, SIGNAL(pay_sig(QString)), worker, SLOT(pay(QString)));
    connect(worker, SIGNAL(numret(int)), this, SLOT(getres(int)));
    emit pay_sig(ui->lineEdit_password->text());
}

void PayWidget::getres(int ret){
    CliInfo *info = CliInfo::getCliInfo();
    double bal;
    switch (ret) {
    case DD_INTERNETERR:
        this->ui->label_info->setText("网络错误！");
        break;
    case DD_INTERNETTIMEOUT:
        this->ui->label_info->setText("网络连接超时！");
        break;
    case -2:
        this->ui->label_info->setText("余额不足！");
        //跳转充值
        break;
    case -1:
        this->ui->label_info->setText("密码错误，请重新输入！");
        this->ui->lineEdit_password->setFocus();
        this->ui->lineEdit_password->selectAll();
        break;
    case 0:
        this->ui->label_info->setText("支付成功！");
        this->ui->pushButton_ret->setText("返回");
        haveCharged = true;

        bal = QString(info->bal).toDouble();
        bal -= QString(info->fare).toDouble();
        strcpy(info->bal, (QString::number(bal, 10, 2)).toLocal8Bit().data());
        break;
    default:
        this->ui->label_info->setText("未知错误！");
        break;
    }

}
