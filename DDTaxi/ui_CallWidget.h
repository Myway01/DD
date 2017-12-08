/********************************************************************************
** Form generated from reading UI file 'CallWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALLWIDGET_H
#define UI_CALLWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CallWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label_DD;
    QLabel *label_2;
    QLabel *label_info;
    QPushButton *pushButton_loc;
    QPushButton *pushButton_call;
    QLabel *label_state;
    QPushButton *pushButton_cancel;
    QPushButton *pushButton_order;
    QPushButton *pushButton_info;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *CallWidget)
    {
        if (CallWidget->objectName().isEmpty())
            CallWidget->setObjectName(QStringLiteral("CallWidget"));
        CallWidget->resize(576, 390);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CallWidget->sizePolicy().hasHeightForWidth());
        CallWidget->setSizePolicy(sizePolicy);
        CallWidget->setMinimumSize(QSize(576, 390));
        CallWidget->setMaximumSize(QSize(1000, 1000));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(207, 255, 242, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        CallWidget->setPalette(palette);
        CallWidget->setAutoFillBackground(true);
        gridLayout = new QGridLayout(CallWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_DD = new QLabel(CallWidget);
        label_DD->setObjectName(QStringLiteral("label_DD"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_DD->sizePolicy().hasHeightForWidth());
        label_DD->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\350\241\214\346\245\267"));
        font.setPointSize(18);
        label_DD->setFont(font);
        label_DD->setStyleSheet(QStringLiteral("color: rgb(84, 84, 84);"));
        label_DD->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_DD, 0, 0, 1, 2);

        label_2 = new QLabel(CallWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QPalette palette1;
        QBrush brush2(QColor(108, 108, 108, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        QBrush brush3(QColor(120, 120, 120, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        label_2->setPalette(palette1);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        label_info = new QLabel(CallWidget);
        label_info->setObjectName(QStringLiteral("label_info"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setWeight(50);
        label_info->setFont(font2);
        label_info->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout->addWidget(label_info, 2, 1, 1, 1);

        pushButton_loc = new QPushButton(CallWidget);
        pushButton_loc->setObjectName(QStringLiteral("pushButton_loc"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_loc->sizePolicy().hasHeightForWidth());
        pushButton_loc->setSizePolicy(sizePolicy2);
        pushButton_loc->setFont(font1);
        pushButton_loc->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_loc->setStyleSheet(QLatin1String("QPushButton {  background-color: rgb(255, 255, 0);color: rgb(255, 255, 255); border-radius: 3px; border-color: rgb(127, 127, 127); } QPushButton:hover { background-color: rgb(255, 255, 255);color: rgb(255, 255, 0);}\n"
""));

        gridLayout->addWidget(pushButton_loc, 3, 1, 1, 1);

        pushButton_call = new QPushButton(CallWidget);
        pushButton_call->setObjectName(QStringLiteral("pushButton_call"));
        pushButton_call->setFont(font1);
        pushButton_call->setStyleSheet(QLatin1String("QPushButton {  background-color: rgb(255, 255, 0);color: rgb(255, 255, 255); border-radius: 3px; border-color: rgb(127, 127, 127); } QPushButton:hover { background-color: rgb(255, 255, 255);color: rgb(255, 255, 0);}\n"
""));

        gridLayout->addWidget(pushButton_call, 4, 1, 1, 1);

        label_state = new QLabel(CallWidget);
        label_state->setObjectName(QStringLiteral("label_state"));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        label_state->setPalette(palette2);
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        label_state->setFont(font3);

        gridLayout->addWidget(label_state, 5, 0, 2, 2);

        pushButton_cancel = new QPushButton(CallWidget);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setFont(font1);
        pushButton_cancel->setStyleSheet(QLatin1String("QPushButton {  background-color: rgb(255, 255, 0);color: rgb(255, 255, 255); border-radius: 3px; border-color: rgb(127, 127, 127); } QPushButton:hover { background-color: rgb(255, 255, 255);color: rgb(255, 255, 0);}\n"
""));

        gridLayout->addWidget(pushButton_cancel, 6, 1, 1, 1);

        pushButton_order = new QPushButton(CallWidget);
        pushButton_order->setObjectName(QStringLiteral("pushButton_order"));
        pushButton_order->setFont(font1);
        pushButton_order->setStyleSheet(QLatin1String("QPushButton {  background-color: rgb(255, 255, 0);color: rgb(255, 255, 255); border-radius: 3px; border-color: rgb(127, 127, 127); } QPushButton:hover { background-color: rgb(255, 255, 255);color: rgb(255, 255, 0);}\n"
""));

        gridLayout->addWidget(pushButton_order, 7, 1, 1, 1);

        pushButton_info = new QPushButton(CallWidget);
        pushButton_info->setObjectName(QStringLiteral("pushButton_info"));
        pushButton_info->setFont(font1);
        pushButton_info->setStyleSheet(QLatin1String("QPushButton {  background-color: rgb(255, 255, 0);color: rgb(255, 255, 255); border-radius: 3px; border-color: rgb(127, 127, 127); } QPushButton:hover { background-color: rgb(255, 255, 255);color: rgb(255, 255, 0);}\n"
""));

        gridLayout->addWidget(pushButton_info, 8, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 9, 0, 1, 2);


        retranslateUi(CallWidget);

        QMetaObject::connectSlotsByName(CallWidget);
    } // setupUi

    void retranslateUi(QWidget *CallWidget)
    {
        CallWidget->setWindowTitle(QApplication::translate("CallWidget", "Form", 0));
        label_DD->setText(QApplication::translate("CallWidget", "DD\346\211\223\350\275\246", 0));
        label_2->setText(QApplication::translate("CallWidget", "\344\277\241\346\201\257", 0));
        label_info->setText(QString());
        pushButton_loc->setText(QApplication::translate("CallWidget", "\345\256\232\344\275\215", 0));
        pushButton_call->setText(QApplication::translate("CallWidget", "\345\221\274\345\217\253", 0));
        label_state->setText(QString());
        pushButton_cancel->setText(QApplication::translate("CallWidget", "\345\217\226\346\266\210", 0));
        pushButton_order->setText(QApplication::translate("CallWidget", "\346\237\245\347\234\213\350\256\242\345\215\225", 0));
        pushButton_info->setText(QApplication::translate("CallWidget", "\346\210\221\347\232\204\344\277\241\346\201\257", 0));
    } // retranslateUi

};

namespace Ui {
    class CallWidget: public Ui_CallWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALLWIDGET_H
