#ifndef PAYWIDGET_H
#define PAYWIDGET_H

#include <QWidget>

namespace Ui {
class PayWidget;
}

class PayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PayWidget(QWidget *parent = 0);
    ~PayWidget();

    void showinit();
    void pay();

private:
    Ui::PayWidget *ui;

    bool haveCharged;

signals:
    void ret();
    void pay_sig(const QString &password);
public slots:
    void getres(int ret);
private slots:
    void on_pushButton_ret_clicked();
};

#endif // PAYWIDGET_H
