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
    this->resize(w->minimumSize());
    lay->addWidget(w);
    w->show();
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
    if (ifw != NULL){
        delete ifw;
    }
}

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    lay = new QGridLayout(this);
    lgw = new LoginWidget();
    suw = new SignupWidget();
    caw = new CallWidget();
    ifw = new InfoWidget();
    paw = new PayWidget();
    lay->setMargin(0);
    this->setWindowIcon(QIcon(":/new/icon/rsc/car.png"));
    showWidget(lgw);
    connect(lgw, SIGNAL(login()), this, SLOT(showcaw()));
    connect(lgw, SIGNAL(signup()), this, SLOT(showsuw()));
    connect(suw, SIGNAL(ret()), this, SLOT(showlgw()));
    connect(caw, SIGNAL(myinfo()), this, SLOT(showifw()));
    connect(caw, SIGNAL(pay()), this, SLOT(showpaw()));
    connect(ifw, SIGNAL(ret()), this, SLOT(retcaw()));
    connect(paw, SIGNAL(ret()), this, SLOT(showcaw()));
}

int MainWidget::showcaw(){
    showWidget(caw);
    caw->showinit();
    return 0;
}
int MainWidget::retcaw(){
    showWidget(caw);
    return 0;
}

int MainWidget::showsuw(){
    showWidget(suw);
    suw->showinit();
    return 0;
}

int MainWidget::showlgw(){
    showWidget(lgw);
    lgw->showinit();
    return 0;
}

int MainWidget::showifw(){
    showWidget(ifw);
    ifw->showinit();
    return 0;
}
int MainWidget::showpaw(){
    showWidget(paw);
    paw->showinit();
    return 0;
}
