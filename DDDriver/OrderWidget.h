#ifndef ORDERWIDGET_H
#define ORDERWIDGET_H

#include <QWidget>

namespace Ui {
class OrderWidget;
}

class OrderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OrderWidget(QWidget *parent = 0);
    ~OrderWidget();

private:
    Ui::OrderWidget *ui;
};

#endif // ORDERWIDGET_H
