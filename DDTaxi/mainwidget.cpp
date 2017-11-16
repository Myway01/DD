#include "MainWidget.h"
#include <QDebug>
#include <QIcon>

void MainWidget::showWidget(QWidget *w){
    if (lay->count()){
        QWidget *p = lay->itemAt(0)->widget();
        lay->removeWidget(p);
        p->hide();
    }
    this->setSizePolicy(w->sizePolicy());
    this->setMaximumSize(w->maximumSize());
    this->setMinimumSize(w->minimumSize());
    lay->addWidget(w);
}

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    lay = new QGridLayout(this);
    lgw = new LoginWidget(this);
    lay->setMargin(0);
    this->setWindowIcon(QIcon(":/new/icon/car.png"));
    showWidget(lgw);
    connect(lgw, SIGNAL(login()), this, SLOT(login_call()));
    connect(lgw, SIGNAL(signup()), this, SLOT(login_signup()));
}

int MainWidget::login_call(){
    caw = new CallWidget(this);
    //lgw->hide();
    showWidget(caw);
    return 0;
}

int MainWidget::login_signup(){
    //lgw->hide();
    suw = new SignupWidget(this);
    showWidget(suw);
    return 0;
}
