#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();

    void showinit();

signals:
    void login();
    void signup();
    void login_sig(const QString &username, const QString &password);

private slots:
    void on_pushButton_signup_clicked();

    void on_pushButton_signin_clicked();

    void login_slot(int ret);

protected:

private:
    Ui::LoginWidget *ui;
    //int checkIn(const QString &username, const QString &password);
};

#endif // LOGINWIDGET_H
