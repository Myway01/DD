#ifndef CALLWIDGET_H
#define CALLWIDGET_H

#include <QWidget>
#include <QWebEngineView>
#include <QTimer>

#include "MapConn.h"
#include "Worker.h"

namespace Ui {
class CallWidget;
}

class CallWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CallWidget(QWidget *parent = 0);
    ~CallWidget();

    void showinit();

    void startPaintCars();
    void endPaintCars();

    void startSendPos();
    void endSendPos();

    void sendStartPos();
    void delStartPos();

    void startCheckOrd();
    void endCheckOrd();

protected:

private:
    Ui::CallWidget *ui;
    QWebEngineView *map_view;
    MapConn *mapconn;
    QTimer *timer;
    Worker *carsPaintWorker;
    Worker *sendPosWorker;
    Worker *checkWorker;
    bool isConnected;   //获取连接状态，判断断网提示框是否要弹出
    bool havePermission;
    QString _lng;
    QString _lat;
    QString startlng;
    QString startlat;
    QString _start;
    QString _end;
    int state;  //用于保存当前订单状态

signals:
    void getCurPos_sig();
    void carsPaint_sig(const QString &lng, const QString &lat);
    void sendPos_sig(const QString &lng, const QString &lat);
    void sendStartPos_sig(const QString &lng, const QString &lat, const QString &start, const QString &end);
    void delStartPos_sig();
    void check_sig(int state);
    void sendPosWorkerQuit_sig();
    void carsPaintWorkerQuit_sig();
    void checkWorkerQuit_sig();
    void myinfo();
    void pay();

public slots:
    void getCurPos_slot();
    void setinfo(const QString &info);
    void setStartPos(const QString &lng, const QString &lat);
    void setCurPos(const QString &lng, const QString &lat);
    void setStartPosStr(const QString &start);
    void setEndPosStr(const QString &end);
    void neterr(int);

    void addCar(const QString &lng, const QString &lat);
    void removeCars();
    void carsPaint_slot();
    void sendPos_slot();
    void check_slot();
    void haveDriver();//有司机接单的槽函数 1
    void startOrd();//行程开始的槽函数 2
    void endOrd();//行程结束的槽函数 3

private slots:
    void on_pushButton_call_clicked();
    void on_pushButton_loc_clicked();
    void on_pushButton_cancel_clicked();
    void on_pushButton_info_clicked();
};

#endif // CALLWIDGET_H
