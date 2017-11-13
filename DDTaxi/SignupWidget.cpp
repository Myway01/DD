#include "SignupWidget.h"
#include "ui_SignupWidget.h"

SignupWidget::SignupWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignupWidget)
{
    ui->setupUi(this);
}

SignupWidget::~SignupWidget()
{
    delete ui;
}
