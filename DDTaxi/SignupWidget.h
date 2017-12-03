#ifndef SIGNUPWIDGET_H
#define SIGNUPWIDGET_H

#include <QWidget>

namespace Ui {
class SignupWidget;
}

class SignupWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SignupWidget(QWidget *parent = 0);
    ~SignupWidget();

signals:
    void ret();
    void signup();

private slots:
    void on_pushButton_ret_clicked();

private:
    Ui::SignupWidget *ui;
};

#endif // SIGNUPWIDGET_H
