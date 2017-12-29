#include "InfoWidget.h"
#include "ui_InfoWidget.h"

#include <QMessageBox>
#include "Worker.h"
#include "DrvInfo.h"

InfoWidget::InfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoWidget)
{
    ui->setupUi(this);

    isConnected = true;
}

InfoWidget::~InfoWidget()
{
    delete ui;
}

void InfoWidget::showinit(){
    Worker *worker = new Worker();
    connect(this, SIGNAL(getinfo_sig()), worker, SLOT(getinfo_slot()));
    connect(worker, SIGNAL(getinfo_sig()), this, SLOT(getinfo_slot()));
    connect(worker, SIGNAL(numret(int)), this, SLOT(neterr(int)));
    emit getinfo_sig();
}

void InfoWidget::neterr(int ret){
    if (isConnected){
        if (ret == DD_INTERNETERR){
            QMessageBox errBox(this);
            errBox.setText("网络出错！");
            errBox.setInformativeText("是否重新连接？");
            errBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            errBox.setDefaultButton(QMessageBox::Yes);
            errBox.setButtonText(QMessageBox::Yes, "是");
            errBox.setButtonText(QMessageBox::No, "否");

            if (errBox.exec() == QMessageBox::Yes) {
                //reconnect 关闭功能，并刷新所有变量就好了showinit
            } else {
                isConnected = false;
            }
        }
        else if (ret == DD_INTERNETTIMEOUT){
            QMessageBox timeoutBox(this);
            timeoutBox.setText("网络连接超时！");
            timeoutBox.setInformativeText("是否重新连接？");
            timeoutBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            timeoutBox.setDefaultButton(QMessageBox::Yes);
            timeoutBox.setButtonText(QMessageBox::Yes, "是");
            timeoutBox.setButtonText(QMessageBox::No, "否");

            if (timeoutBox.exec() == QMessageBox::Yes) {
                //reconnect
            } else {
                isConnected = false;
            }
        }
    }
    else if (ret == 0){
        isConnected = true;
    }
}

void InfoWidget::getinfo_slot(){
    DrvInfo *info = DrvInfo::getDrvInfo();
    ui->label_nickname->setText(QString(info->nickname));
    ui->label_tel->setText(QString(info->tel));
    ui->label_bal->setText(QString(info->bal));
    ui->label_card->setText(QString(info->card));
    ui->label_clinickname->setText(QString(info->clinickname));
    ui->label_clitel->setText(QString(info->clitel));
}

void InfoWidget::on_pushButton_ret_clicked()
{
    emit ret();
}
