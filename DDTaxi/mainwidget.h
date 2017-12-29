#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include "LoginWidget.h"
#include "SignupWidget.h"
#include "CallWidget.h"
#include "InfoWidget.h"
#include "PayWidget.h"

class MainWidget : public QWidget
{
    Q_OBJECT

private:
    QGridLayout *lay;
    LoginWidget *lgw;
    SignupWidget *suw;
    CallWidget *caw;
    InfoWidget *ifw;
    PayWidget *paw;

    void showWidget(QWidget *);

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

signals:

public slots:
    int showcaw();
    int retcaw();
    int showsuw();
    int showlgw();
    int showifw();
    int showpaw();

};

#endif // MAINWIDGET_H
