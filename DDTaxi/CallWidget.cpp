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
