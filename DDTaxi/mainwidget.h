#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include "LoginWidget.h"
#include "SignupWidget.h"
#include "CallWidget.h"

class MainWidget : public QWidget
{
    Q_OBJECT

private:
    QGridLayout *lay;
    LoginWidget *lgw;
    SignupWidget *suw;
    CallWidget *caw;

    void showWidget(QWidget *);

public:
    explicit MainWidget(QWidget *parent = 0);

signals:

public slots:
    int login_call();
    int login_signup();

};

#endif // MAINWIDGET_H
