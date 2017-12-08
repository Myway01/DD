#include "ordWidget.h"
#include "ui_ordWidget.h"

ordWidget::ordWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ordWidget)
{
    ui->setupUi(this);
}

ordWidget::~ordWidget()
{
    delete ui;
}
