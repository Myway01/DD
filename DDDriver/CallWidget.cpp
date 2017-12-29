#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "CallWidget.h"
#include "ui_CallWidget.h"

#include <QMessageBox>
#include <QtTextToSpeech/QTextToSpeech>
#include "DrvInfo.h"

CallWidget::CallWidget(QWidget *parent) :
    QWidget(parent),
  ui(new Ui::CallWidget)
{
  ui->setupUi(this);
  map_view = new QWebEngineView(this);
  mapconn = new MapConn(map_view);
  this->ui->gridLayout_map->addWidget(map_view);
  connect(mapconn, SIGNAL(mapinfo(QString)), this, SLOT(setinfo(QString)));
  connect(mapconn, SIGNAL(setCurPos_sig(QString,QString)), this, SLOT(setCurPos(QString,QString)));
  connect(mapconn, SIGNAL(setDrvInfo_sig(QString)), this, SLOT(setDrvInfo(QString)));
  connect(mapconn, SIGNAL(setFare_sig(QString)), this, SLOT(setFare(QString)));
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(getCurPos_slot()));
  havePermission = false;
  isConnected = true;
  haveStarted = false;
  timer->start(3000);
}

CallWidget::~CallWidget()
{
    delete ui;
    if (listenWorker)
        emit listenWorkerQuit_sig();
    if (sendPosWorker)
        emit sendPosWorkerQuit_sig();
}

void CallWidget::showinit(){
    listenWorker = NULL;
    sendPosWorker = NULL;
    state = 0;

    ui->label_info->clear();
    if (haveStarted){
        ui->pushButton_start->setEnabled(false);
        ui->pushButton_start->setStyleSheet("background-color: rgb(aa, aa, aa);");
        ui->pushButton_take->setEnabled(true);
        ui->pushButton_take->setStyleSheet("QPushButton {  background-color: rgb(255, 255, 0);color: rgb(255, 255, 255); border-radius: 3px; border-color: rgb(127, 127, 127); } QPushButton:hover { background-color: rgb(255, 255, 255);color: rgb(255, 255, 0);}");
        ui->pushButton_quit->setEnabled(true);
        ui->pushButton_take->setStyleSheet("QPushButton {  background-color: rgb(255, 255, 0);color: rgb(255, 255, 255); border-radius: 3px; border-color: rgb(127, 127, 127); } QPushButton:hover { background-color: rgb(255, 255, 255);color: rgb(255, 255, 0);}");
        startListen();
    }
    else {
        ui->pushButton_start->setEnabled(true);
        ui->pushButton_start->setStyleSheet("QPushButton {  background-color: rgb(255, 255, 0);color: rgb(255, 255, 255); border-radius: 3px; border-color: rgb(127, 127, 127); } QPushButton:hover { background-color: rgb(255, 255, 255);color: rgb(255, 255, 0);}");
        ui->pushButton_take->setEnabled(false);
        ui->pushButton_take->setStyleSheet("background-color: rgb(aa, aa, aa);");
        ui->pushButton_quit->setEnabled(false);
        ui->pushButton_take->setStyleSheet("background-color: rgb(aa, aa, aa);");

    }
    QWebEnginePage *page = map_view->page();
    if (!havePermission){
        connect(page, &QWebEnginePage::featurePermissionRequested,
                [this, page](const QUrl &securityOrigin, QWebEnginePage::Feature feature) {
            if (feature != QWebEnginePage::Geolocation)
                return;

            QMessageBox msgBox(this);
            msgBox.setText(QString("DD打车想要获取您的位置权限"));
            msgBox.setInformativeText(QString("确定要将您的位置信息发送给DD打车吗？"));
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::Yes);
            msgBox.setButtonText(QMessageBox::Yes, "是");
            msgBox.setButtonText(QMessageBox::No, "否");

            if (msgBox.exec() == QMessageBox::Yes) {
                page->setFeaturePermission(
                            securityOrigin, feature, QWebEnginePage::PermissionGrantedByUser);
                havePermission = true;
            } else {
                page->setFeaturePermission(
                            securityOrigin, feature, QWebEnginePage::PermissionDeniedByUser);
            }
        });
    }
    page->load(QUrl(QStringLiteral("qrc:/new/map/rsc/map.html")));
}

void CallWidget::startListen(){
    listenWorker = new Worker();
    listentimer = new QTimer(this);
    ticktimer = new QTimer(this);
    connect(this, SIGNAL(listen_sig(QString,QString)), listenWorker, SLOT(listen(QString,QString)));
    connect(this, SIGNAL(listenWorkerQuit_sig()), listenWorker, SLOT(quit()));
    connect(listenWorker, SIGNAL(addCliStart_sig(QString,QString,QString,QString)), this, SLOT(addCliStart(QString,QString,QString,QString)));
    connect(listenWorker, SIGNAL(removeCliStart_sig()), this, SLOT(removeCliStart()));
    connect(listenWorker, SIGNAL(numret(int)), this, SLOT(neterr(int)));
    connect(listentimer, SIGNAL(timeout()), this, SLOT(listen_slot()));
    connect(ticktimer, SIGNAL(timeout()), this, SLOT(listentick()));
    listentimer->start(15000);
    ticktimer->start(1000);
    emit listen_slot();
}
void CallWidget::endListen(){
    disconnect(listentimer, SIGNAL(timeout()), this, SLOT(listen_slot()));
    disconnect(ticktimer, SIGNAL(timeout()), this, SLOT(listentick()));
    delPos();
    if (listenWorker != NULL){
        emit listenWorkerQuit_sig();
        listenWorker = NULL;
    }
    delete listentimer;
    delete ticktimer;
    this->ui->label_2->setText("信息：");
}
void CallWidget::listen_slot(){
    emit listen_sig(_lng, _lat);
    tick = 15;
}
void CallWidget::addCliStart(const QString &lng_start, const QString &lat_start, const QString &startPos, const QString &endPos){
    if(lng_start == "null") {
        state = 0;
        ui->label_info->setText("正在搜索叫车的乘客...");
        return;
    }
    state = 1;
    emit mapconn->addCliStart(lng_start, lat_start, startPos, endPos);
    QTextToSpeech *tts = new QTextToSpeech(this);
    if(tts->state()==QTextToSpeech::Ready)
    {
        QString s = "实时：从 " + startPos + " 到 " + endPos;
        tts->say(s);
    }
}
void CallWidget::removeCliStart(){
    emit mapconn->removeCliStart();
    //qDebug()<<"removecars";
}
void CallWidget::listentick(){
    ui->label_2->setText(QString("信息： 接单时间还剩%1秒").arg(tick));
    tick--;
}
void CallWidget::delPos(){
    Worker *worker = new Worker();
    connect(this, SIGNAL(delPos_sig()), worker, SLOT(delPos()));
    connect(worker, SIGNAL(numret(int)), this, SLOT(neterr(int)));
    emit delPos_sig();
}

void CallWidget::sendState(int state){
    Worker *worker = new Worker();
    connect(this, SIGNAL(sendState_sig(int)), worker, SLOT(sendState(int)));
    connect(worker, SIGNAL(numret(int)), this, SLOT(neterr(int)));
    emit sendState_sig(state);
}

//send用自己的timer计时发给线程发送，get类操作用线程的timer发给自己，发送使用信号和槽
void CallWidget::startSendPos(){
    sendPosWorker = new Worker();
    connect(this, SIGNAL(sendPos_sig(QString,QString)), sendPosWorker, SLOT(sendPos(QString,QString)));
    connect(this, SIGNAL(sendPosWorkerQuit_sig()), sendPosWorker, SLOT(quit()));
    connect(sendPosWorker, SIGNAL(addCli_sig(QString,QString)), this, SLOT(addCli(QString,QString)));
    connect(sendPosWorker, SIGNAL(removeCli_sig()), this, SLOT(removeCli()));
    connect(sendPosWorker, SIGNAL(numret(int)), this, SLOT(neterr(int)));
    connect(timer, SIGNAL(timeout()), this, SLOT(sendPos_slot()));
}
void CallWidget::endSendPos(){
    disconnect(timer, SIGNAL(timeout()), this, SLOT(sendPos_slot()));
    if (sendPosWorker != NULL){
        emit sendPosWorkerQuit_sig();
        sendPosWorker = NULL;
    }
}
void CallWidget::sendPos_slot(){
    emit sendPos_sig(_lng, _lat);
}
void CallWidget::addCli(const QString &lng, const QString &lat){
    emit mapconn->addCli(lng, lat);
}
void CallWidget::removeCli(){
    emit mapconn->removeCli();
}

//SLOT
void CallWidget::getCurPos_slot(){
    emit mapconn->getpos();
}
void CallWidget::setinfo(const QString &info){
    this->ui->label_info->setText(info);
}
void CallWidget::setFare(const QString &fare){
    qDebug()<<"setFare";
    DrvInfo *info = DrvInfo::getDrvInfo();
    strcpy(info->fare, fare.toLocal8Bit().data());
    QString fareinfo = QString("本次行程共计收费：") + fare +QString("元");
    QMessageBox::information(this, QString("订单完成"), fareinfo);
    sendState(3);

    listenWorker = NULL;
    sendPosWorker = NULL;
    state = 0;

    ui->label_info->clear();
    if (haveStarted){
        ui->pushButton_start->setEnabled(false);
        ui->pushButton_start->setStyleSheet("background-color: rgb(aa, aa, aa);");
        ui->pushButton_take->setEnabled(true);
        ui->pushButton_take->setStyleSheet("QPushButton {  background-color: rgb(255, 255, 0);color: rgb(255, 255, 255); border-radius: 3px; border-color: rgb(127, 127, 127); } QPushButton:hover { background-color: rgb(255, 255, 255);color: rgb(255, 255, 0);}");
        ui->pushButton_quit->setEnabled(true);
        ui->pushButton_take->setStyleSheet("QPushButton {  background-color: rgb(255, 255, 0);color: rgb(255, 255, 255); border-radius: 3px; border-color: rgb(127, 127, 127); } QPushButton:hover { background-color: rgb(255, 255, 255);color: rgb(255, 255, 0);}");
        startListen();
    }
    else {
        ui->pushButton_start->setEnabled(true);
        ui->pushButton_start->setStyleSheet("QPushButton {  background-color: rgb(255, 255, 0);color: rgb(255, 255, 255); border-radius: 3px; border-color: rgb(127, 127, 127); } QPushButton:hover { background-color: rgb(255, 255, 255);color: rgb(255, 255, 0);}");
        ui->pushButton_take->setEnabled(false);
        ui->pushButton_take->setStyleSheet("background-color: rgb(aa, aa, aa);");
        ui->pushButton_quit->setEnabled(false);
        ui->pushButton_take->setStyleSheet("background-color: rgb(aa, aa, aa);");

    }
}
void CallWidget::setDrvInfo(const QString &info){
    DrvInfo *drvinfo = DrvInfo::getDrvInfo();
    QString dinfo = "乘客" + QString(drvinfo->clinickname) +"(" +QString(drvinfo->clitel) + ")\n\t正在呼叫快车：";
    QString i = dinfo + info;
    ui->label_info->setText(i);
}

void CallWidget::setCurPos(const QString &lng, const QString &lat){
    _lng = lng;
    _lat = lat;
    //qDebug()<<"cur:"<<lng<<lat;
}

void CallWidget::neterr(int ret){
    if (isConnected){
        if (ret == DD_INTERNETERR){
            QMessageBox errBox(this);
            errBox.setText("网络出错！");
            errBox.setInformativeText("是否重新连接？");
            errBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            errBox.setDefaultButton(QMessageBox::Yes);
            errBox.setButtonText(QMessageBox::Yes, "是");
            errBox.setButtonText(QMessageBox::No, "否");

            if (errBox.exec() == QMessageBox::Yes) {
                //reconnect 关闭功能，并刷新所有变量就好了showinit
            } else {
                isConnected = false;
            }
        }
        else if (ret == DD_INTERNETTIMEOUT){
            QMessageBox timeoutBox(this);
            timeoutBox.setText("网络连接超时！");
            timeoutBox.setInformativeText("是否重新连接？");
            timeoutBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            timeoutBox.setDefaultButton(QMessageBox::Yes);
            timeoutBox.setButtonText(QMessageBox::Yes, "是");
            timeoutBox.setButtonText(QMessageBox::No, "否");

            if (timeoutBox.exec() == QMessageBox::Yes) {
                //reconnect
            } else {
                isConnected = false;
            }
        }
    }
    else if (ret == 0){
        isConnected = true;
    }
}

//pushbutton SLOT
void CallWidget::on_pushButton_start_clicked()
{
    state = 0;
    haveStarted = true;
    ui->pushButton_take->setEnabled(true);
    ui->pushButton_take->setStyleSheet("QPushButton {  background-color: rgb(255, 255, 0);color: rgb(255, 255, 255); border-radius: 3px; border-color: rgb(127, 127, 127); } QPushButton:hover { background-color: rgb(255, 255, 255);color: rgb(255, 255, 0);}");
    ui->pushButton_quit->setEnabled(true);
    ui->pushButton_quit->setStyleSheet("QPushButton {  background-color: rgb(255, 255, 0);color: rgb(255, 255, 255); border-radius: 3px; border-color: rgb(127, 127, 127); } QPushButton:hover { background-color: rgb(255, 255, 255);color: rgb(255, 255, 0);}");
    ui->pushButton_start->setEnabled(false);
    ui->pushButton_start->setStyleSheet("background-color: rgb(aa, aa, aa);");
    startListen();
}

void CallWidget::on_pushButton_take_clicked()
{
    if(ui->pushButton_take->text() == "接单" && state == 1){
        ui->pushButton_quit->setEnabled(false);
        ui->pushButton_quit->setStyleSheet("background-color: rgb(aa, aa, aa);");
        endListen();
        sendState(1);
        startSendPos();
        ui->pushButton_take->setText("开始计费");
    }
    else if(ui->pushButton_take->text() == "开始计费"){
        sendState(2);
        endSendPos();
        emit mapconn->sendStart(_lng, _lat);
        ui->pushButton_take->setText("结束计费");
    }
    else if(ui->pushButton_take->text() == "结束计费"){
        qDebug()<<"sendEnd";
        emit mapconn->sendEnd(_lng, _lat);//给地图结束点算出费用发送
    }
}

void CallWidget::on_pushButton_quit_clicked()
{
    ui->pushButton_take->setEnabled(false);
    ui->pushButton_take->setStyleSheet("background-color: rgb(aa, aa, aa);");
    ui->pushButton_quit->setEnabled(false);
    ui->pushButton_quit->setStyleSheet("background-color: rgb(aa, aa, aa);");
    ui->pushButton_start->setEnabled(true);
    ui->pushButton_start->setStyleSheet("QPushButton {  background-color: rgb(255, 255, 0);color: rgb(255, 255, 255); border-radius: 3px; border-color: rgb(127, 127, 127); } QPushButton:hover { background-color: rgb(255, 255, 255);color: rgb(255, 255, 0);}");
    ui->label_info->setText("");
    endListen();
}

void CallWidget::on_pushButton_info_clicked()
{
    emit myinfo();
}
