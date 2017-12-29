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

    void startListen();
    void endListen();

    void startSendPos();
    void endSendPos();

    void delPos();
    void sendState(int state);

protected:

private:
    Ui::CallWidget *ui;
    QWebEngineView *map_view;
    MapConn *mapconn;
    QTimer *timer;
    QTimer *listentimer;
    QTimer *ticktimer;
    int tick;
    Worker *listenWorker;
    Worker *sendPosWorker;
    bool isConnected;   //获取连接状态，判断断网提示框是否要弹出
    bool havePermission;
    bool haveStarted;
    QString _lng;
    QString _lat;
    int state;  //用于保存是否听到单

signals:
    void getCurPos_sig();
    void listen_sig(const QString &lng, const QString &lat);
    void sendPos_sig(const QString &lng, const QString &lat);
    void delPos_sig();
    void sendState_sig(int state);
    void sendPosWorkerQuit_sig();
    void listenWorkerQuit_sig();
    void myinfo();

public slots:
    void getCurPos_slot();
    void setinfo(const QString &info);
    void setFare(const QString &fare);
    void setCurPos(const QString &lng, const QString &lat);
    void setDrvInfo(const QString &info);
    void neterr(int);
    void listentick();

    void addCliStart(const QString &lng_start, const QString &lat_start, const QString &startPos, const QString &endPos);
    void removeCliStart();
    void addCli(const QString &lng, const QString &lat);
    void removeCli();
    void listen_slot();
    void sendPos_slot();

private slots:

    void on_pushButton_start_clicked();
    void on_pushButton_take_clicked();
    void on_pushButton_quit_clicked();
    void on_pushButton_info_clicked();
};

#endif // CALLWIDGET_H
