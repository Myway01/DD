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
};

#endif // CALLWIDGET_H
