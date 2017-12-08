#include "CallWidget.h"
#include "ui_CallWidget.h"

CallWidget::CallWidget(QWidget *parent) :
    QWidget(parent),
  ui(new Ui::CallWidget)
{
  ui->setupUi(this);
}

CallWidget::~CallWidget()
{
    delete ui;
}

void CallWidget::on_pushButton_call_clicked()
{
    //ui->webView_map->page()->mainFrame()->evaluateJavaScript(QString("Qttest(\"%1\")").arg("hello, I'm Qt!"));
}

