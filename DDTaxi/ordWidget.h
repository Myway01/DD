#ifndef ORDWIDGET_H
#define ORDWIDGET_H

#include <QWidget>

namespace Ui {
class ordWidget;
}

class ordWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ordWidget(QWidget *parent = 0);
    ~ordWidget();

private:
    Ui::ordWidget *ui;
};

#endif // ORDWIDGET_H
