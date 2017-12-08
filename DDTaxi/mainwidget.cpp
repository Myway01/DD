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

MainWidget::~MainWidget(){
    if (lgw != NULL){
        delete lgw;
    }
    if (suw != NULL){
        delete suw;
    }
    if (caw != NULL){
        delete caw;
    }
}

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    lay = new QGridLayout(this);
    lgw = new LoginWidget();
    suw = new SignupWidget();
    caw = new CallWidget();
    lay->setMargin(0);
    this->setWindowIcon(QIcon(":/new/icon/car.png"));
    showWidget(lgw);
    connect(lgw, SIGNAL(login()), this, SLOT(showcaw()));
    connect(lgw, SIGNAL(signup()), this, SLOT(showsuw()));
    connect(suw, SIGNAL(ret()), this, SLOT(showlgw()));
}

int MainWidget::showcaw(){
    showWidget(caw);
    return 0;
}

int MainWidget::showsuw(){
    showWidget(suw);
    return 0;
}

int MainWidget::showlgw(){
    showWidget(lgw);
    return 0;
}
