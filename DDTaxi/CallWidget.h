#ifndef CALLWIDGET_H
#define CALLWIDGET_H

#include <QWidget>

namespace Ui {
class CallWidget;
}

class CallWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CallWidget(QWidget *parent = 0);
    ~CallWidget();
private:
    Ui::CallWidget *ui;

signals:

public slots:

private slots:
    void on_pushButton_call_clicked();
};

#endif // CALLWIDGET_H
