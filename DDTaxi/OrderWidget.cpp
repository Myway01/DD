#include "OrderWidget.h"
#include "ui_OrderWidget.h"

OrderWidget::OrderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderWidget)
{
    ui->setupUi(this);
}

OrderWidget::~OrderWidget()
{
    delete ui;
}
