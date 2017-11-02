#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include "LoginWidget.h"
#include "SignupWidget.h"

class MainWidget : public QWidget
{
    Q_OBJECT

private:
    QGridLayout *lay;
    LoginWidget *lgw;
    SignupWidget * suw;

    void showWidget(QWidget *);

public:
    explicit MainWidget(QWidget *parent = nullptr);

signals:

public slots:
    int login_call();
    int login_signup();

};

#endif // MAINWIDGET_H
