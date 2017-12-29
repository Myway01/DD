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

    void showinit();

signals:
    void ret();
    void signup();
    void signup_sig(const QString &tel, const QString &nickname, const QString &card, const QString &psw, const QString &paypsw);

private slots:
    void on_pushButton_ret_clicked();

    void on_pushButton_signup_clicked();

    void signup_slot(int ret);

protected:
    
private:
    Ui::SignupWidget *ui;
};

#endif // SIGNUPWIDGET_H
