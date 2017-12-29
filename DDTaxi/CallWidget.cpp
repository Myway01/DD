#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "CallWidget.h"
#include "ui_CallWidget.h"

#include <QMessageBox>
#include "CliInfo.h"

CallWidget::CallWidget(QWidget *parent) :
    QWidget(parent),
  ui(new Ui::CallWidget)
{
  ui->setupUi(this);
  map_view = new QWebEngineView(this);
  mapconn = new MapConn(map_view);
  this->ui->gridLayout_map->addWidget(map_view);
  connect(mapconn, SIGNAL(mapinfo(QString)), this, SLOT(setinfo(QString)));
  connect(mapconn, SIGNAL(setStartPos_sig(QString,QString)), this, SLOT(setStartPos(QString,QString)));
  connect(mapconn, SIGNAL(setCurPos_sig(QString,QString)), this, SLOT(setCurPos(QString,QString)));
  connect(mapconn, SIGNAL(setStartPosStr_sig(QString)), this, SLOT(setStartPosStr(QString)));
  connect(mapconn, SIGNAL(setEndPosStr_sig(QString)), this, SLOT(setEndPosStr(QString)));
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(getCurPos_slot()));
  havePermission = false;
  isConnected = true;
  timer->start(3000);
}

CallWidget::~CallWidget()
{
    delete ui;
    if (carsPaintWorker)
        emit carsPaintWorkerQuit_sig();
    if (sendPosWorker)
        emit sendPosWorkerQuit_sig();
    if (checkWorker)
        emit checkWorkerQuit_sig();
}

void CallWidget::showinit(){
    carsPaintWorker = NULL;
    sendPosWorker = NULL;
    checkWorker = NULL;
    state = 0;

    ui->label_info->clear();
    ui->pushButton_call->setEnabled(true);
    ui->pushButton_call->setStyleSheet("QPushButton {  background-color: rgb(255, 255, 0);color: rgb(255, 255, 255); border-radius: 3px; border-color: rgb(127, 127, 127); } QPushButton:hover { background-color: rgb(255, 255, 255);color: rgb(255, 255, 0);}");
    ui->pushButton_cancel->setEnabled(false);
    ui->pushButton_cancel->setStyleSheet("background-color: rgb(aa, aa, aa);");
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
                startPaintCars();
            } else {
                page->setFeaturePermission(
                            securityOrigin, feature, QWebEnginePage::PermissionDeniedByUser);
            }
        });
    }
    page->load(QUrl(QStringLiteral("qrc:/new/map/rsc/map.html")));
}

void CallWidget::startPaintCars(){
    carsPaintWorker = new Worker();
    connect(this, SIGNAL(carsPaint_sig(QString,QString)), carsPaintWorker, SLOT(carsPaint(QString,QString)));
    connect(this, SIGNAL(carsPaintWorkerQuit_sig()), carsPaintWorker, SLOT(quit()));
    connect(carsPaintWorker, SIGNAL(addCar_sig(QString,QString)), this, SLOT(addCar(QString,QString)));
    connect(carsPaintWorker, SIGNAL(removeCars_sig()), this, SLOT(removeCars()));
    connect(carsPaintWorker, SIGNAL(numret(int)), this, SLOT(neterr(int)));
    connect(timer, SIGNAL(timeout()), this, SLOT(carsPaint_slot()));
}
void CallWidget::endPaintCars(){
    disconnect(timer, SIGNAL(timeout()), this, SLOT(carsPaint_slot()));
    if (carsPaintWorker != NULL){
        emit carsPaintWorkerQuit_sig();
        carsPaintWorker = NULL;
    }
    emit removeCars();
}
void CallWidget::carsPaint_slot(){
    emit carsPaint_sig(startlng, startlat);
}
void CallWidget::addCar(const QString &lng, const QString &lat){
    emit mapconn->addcar(lng, lat);
    //qDebug()<<"addcar";
}
void CallWidget::removeCars(){
    emit mapconn->removecars();
    //qDebug()<<"removecars";
}

void CallWidget::sendStartPos(){
    Worker *worker = new Worker();
    connect(this, SIGNAL(sendStartPos_sig(QString,QString,QString,QString)), worker, SLOT(sendStartPos(QString,QString,QString,QString)));
    connect(worker, SIGNAL(numret(int)), this, SLOT(neterr(int)));
    emit sendStartPos_sig(startlng, startlat, _start, _end);
}
void CallWidget::delStartPos(){
    Worker *worker = new Worker();
    connect(this, SIGNAL(delStartPos_sig()), worker, SLOT(delStartPos()));
    connect(worker, SIGNAL(numret(int)), this, SLOT(neterr(int)));
    emit delStartPos_sig();
}

//send用自己的timer计时发给线程发送，get类操作用线程的timer发给自己，发送使用信号和槽
void CallWidget::startSendPos(){
    sendPosWorker = new Worker();
    connect(this, SIGNAL(sendPos_sig(QString,QString)), sendPosWorker, SLOT(sendPos(QString,QString)));
    connect(this, SIGNAL(sendPosWorkerQuit_sig()), sendPosWorker, SLOT(delOrdPos()));
    connect(sendPosWorker, SIGNAL(addCar_sig(QString,QString)), this, SLOT(addCar(QString,QString)));
    connect(sendPosWorker, SIGNAL(removeCars_sig()), this, SLOT(removeCars()));
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

void CallWidget::startCheckOrd(){
    checkWorker = new Worker();
    connect(this, SIGNAL(check_sig(int)), checkWorker, SLOT(checkOrd(int)));
    connect(this, SIGNAL(checkWorkerQuit_sig()), checkWorker, SLOT(quit()));
    connect(checkWorker, SIGNAL(haveDriver()), this, SLOT(haveDriver()));
    connect(checkWorker, SIGNAL(startOrd()), this, SLOT(startOrd()));
    connect(checkWorker, SIGNAL(endOrd()), this, SLOT(endOrd()));
    connect(checkWorker, SIGNAL(numret(int)), this, SLOT(neterr(int)));
    connect(timer, SIGNAL(timeout()), this, SLOT(check_slot()));
}
void CallWidget::endCheckOrd(){
    disconnect(timer, SIGNAL(timeout()), this, SLOT(check_slot()));
    if (checkWorker !=NULL){
        emit checkWorkerQuit_sig();
        checkWorker = NULL;
    }
}
void CallWidget::check_slot(){
    emit check_sig(state);
}
void CallWidget::haveDriver(){
    qDebug()<<"haveDriver";
    ui->pushButton_cancel->setEnabled(false);
    ui->pushButton_cancel->setStyleSheet("background-color: rgb(aa, aa, aa);");
    CliInfo *cliinfo = CliInfo::getCliInfo();
    QString info;
    //qDebug()<<cliinfo->drvnickname;
    //qDebug()<< QString(cliinfo->drvnickname);
    info = "司机" + QString(cliinfo->drvnickname) + "已接单：\n手机号码：" + QString(cliinfo->drvtel) + "\n车牌号：" + QString(cliinfo->drvcard);
    ui->label_info->setText(info);
    state = 1;
    endPaintCars();
    startSendPos();
}
void CallWidget::startOrd(){
    qDebug()<<"startOrd";
    ui->label_info->setText("行程已开始...");
    endSendPos();
    emit removeCars();
    state = 2;
}
void CallWidget::endOrd(){
    qDebug()<<"endOrd";
    CliInfo *cliinfo = CliInfo::getCliInfo();
    QString info;
    info = "本次行程已结束，\n\t出行费用共计：" + QString(cliinfo->fare) + "元";
    ui->label_info->setText(info);

    endCheckOrd();
    emit pay();
    state = 3;
}

//SLOT
void CallWidget::getCurPos_slot(){
    emit mapconn->getpos();
}
void CallWidget::setinfo(const QString &info){
    this->ui->label_info->setText(info);
}
void CallWidget::setStartPos(const QString &lng, const QString &lat){
    startlng = lng;
    startlat = lat;
    //qDebug()<<"start:"<<lng<<lat;
}
void CallWidget::setCurPos(const QString &lng, const QString &lat){
    _lng = lng;
    _lat = lat;
    //qDebug()<<"cur:"<<lng<<lat;
}
void CallWidget::setStartPosStr(const QString &start){
    _start = start;
    //qDebug()<<"startpos:"<<start;
}
void CallWidget::setEndPosStr(const QString &end){
    _end = end;
    //qDebug()<<"endpos"<<end;
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
void CallWidget::on_pushButton_loc_clicked()
{
    emit mapconn->geoinfo();
}

void CallWidget::on_pushButton_call_clicked()
{
    if (_start != "" && _end != NULL){
        sendStartPos();
        startCheckOrd();
        ui->label_info->setText("正在等待司机接单...");
        ui->pushButton_cancel->setEnabled(true);
        ui->pushButton_cancel->setStyleSheet("QPushButton {  background-color: rgb(255, 255, 0);color: rgb(255, 255, 255); border-radius: 3px; border-color: rgb(127, 127, 127); } QPushButton:hover { background-color: rgb(255, 255, 255);color: rgb(255, 255, 0);}");
        ui->pushButton_call->setEnabled(false);
        ui->pushButton_call->setStyleSheet("background-color: rgb(aa, aa, aa);");
    }
}

void CallWidget::on_pushButton_cancel_clicked()
{
    delStartPos();
    endCheckOrd();
    ui->label_info->setText("呼叫已取消...");
    ui->pushButton_call->setEnabled(true);
    ui->pushButton_call->setStyleSheet("QPushButton {  background-color: rgb(255, 255, 0);color: rgb(255, 255, 255); border-radius: 3px; border-color: rgb(127, 127, 127); } QPushButton:hover { background-color: rgb(255, 255, 255);color: rgb(255, 255, 0);}");
    ui->pushButton_cancel->setEnabled(false);
    ui->pushButton_cancel->setStyleSheet("background-color: rgb(aa, aa, aa);");
}

void CallWidget::on_pushButton_info_clicked()
{
    emit myinfo();
}
