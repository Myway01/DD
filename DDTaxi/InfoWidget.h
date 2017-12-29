#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QWidget>

namespace Ui {
class InfoWidget;
}

class InfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InfoWidget(QWidget *parent = 0);
    ~InfoWidget();

    void showinit();

private:
    Ui::InfoWidget *ui;

signals:
    void ret();

public slots:

private slots:
    void on_pushButton_ret_clicked();
};

#endif // INFOWIDGET_H
