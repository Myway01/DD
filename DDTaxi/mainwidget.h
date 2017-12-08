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
    ~MainWidget();

signals:

public slots:
    int showcaw();
    int showsuw();
    int showlgw();

};

#endif // MAINWIDGET_H
