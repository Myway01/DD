#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "InfoWidget.h"
#include "ui_InfoWidget.h"

#include <QMessageBox>
#include "CliInfo.h"

InfoWidget::InfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoWidget)
{
    ui->setupUi(this);
}

InfoWidget::~InfoWidget()
{
    delete ui;
}

void InfoWidget::showinit(){
    CliInfo *info = CliInfo::getCliInfo();
    ui->label_nickname->setText(QString(info->nickname));
    ui->label_tel->setText(QString(info->tel));
    ui->label_bal->setText(QString(info->bal));
    ui->label_drvcard->setText(QString(info->drvcard));
    ui->label_drvnickname->setText(QString(info->drvnickname));
    ui->label_drvtel->setText(QString(info->drvtel));
}

void InfoWidget::on_pushButton_ret_clicked()
{
    emit ret();
}
