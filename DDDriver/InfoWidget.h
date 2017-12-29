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

    bool isConnected;

signals:
    void getinfo_sig();
    void ret();

public slots:
    void getinfo_slot();
    void neterr(int ret);

private slots:
    void on_pushButton_ret_clicked();
};

#endif // INFOWIDGET_H
