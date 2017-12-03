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
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CallWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label_DD;
    QPushButton *pushButton_loc;
    QLabel *label;
    QLineEdit *lineEdit_epos;
    QLabel *label_state;
    QLabel *label_2;
    QLineEdit *lineEdit_spos;
    QPushButton *pushButton_call;
    QPushButton *pushButton_cancel;
    QPushButton *pushButton_order;
    QSpacerItem *verticalSpacer;
    QWebView *webView_map;

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
        CallWidget->setMaximumSize(QSize(576, 390));
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

        gridLayout->addWidget(label_DD, 0, 0, 1, 1);

        pushButton_loc = new QPushButton(CallWidget);
        pushButton_loc->setObjectName(QStringLiteral("pushButton_loc"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_loc->sizePolicy().hasHeightForWidth());
        pushButton_loc->setSizePolicy(sizePolicy2);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        pushButton_loc->setFont(font1);
        pushButton_loc->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_loc->setStyleSheet(QLatin1String("QPushButton {  background-color: rgb(255, 255, 0);color: rgb(255, 255, 255); border-radius: 3px; border-color: rgb(127, 127, 127); } QPushButton:hover { background-color: rgb(255, 255, 255);color: rgb(255, 255, 0);}\n"
""));

        gridLayout->addWidget(pushButton_loc, 1, 0, 1, 1);

        label = new QLabel(CallWidget);
        label->setObjectName(QStringLiteral("label"));
        QPalette palette1;
        QBrush brush2(QColor(108, 108, 108, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        QBrush brush3(QColor(120, 120, 120, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        label->setPalette(palette1);
        label->setFont(font1);

        gridLayout->addWidget(label, 2, 0, 1, 1);

        lineEdit_epos = new QLineEdit(CallWidget);
        lineEdit_epos->setObjectName(QStringLiteral("lineEdit_epos"));

        gridLayout->addWidget(lineEdit_epos, 5, 0, 1, 1);

        label_state = new QLabel(CallWidget);
        label_state->setObjectName(QStringLiteral("label_state"));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        label_state->setPalette(palette2);
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        label_state->setFont(font2);

        gridLayout->addWidget(label_state, 6, 0, 1, 1);

        label_2 = new QLabel(CallWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        label_2->setPalette(palette3);
        label_2->setFont(font1);

        gridLayout->addWidget(label_2, 4, 0, 1, 1);

        lineEdit_spos = new QLineEdit(CallWidget);
        lineEdit_spos->setObjectName(QStringLiteral("lineEdit_spos"));

        gridLayout->addWidget(lineEdit_spos, 3, 0, 1, 1);

        pushButton_call = new QPushButton(CallWidget);
        pushButton_call->setObjectName(QStringLiteral("pushButton_call"));
        pushButton_call->setFont(font1);
        pushButton_call->setStyleSheet(QLatin1String("QPushButton {  background-color: rgb(255, 255, 0);color: rgb(255, 255, 255); border-radius: 3px; border-color: rgb(127, 127, 127); } QPushButton:hover { background-color: rgb(255, 255, 255);color: rgb(255, 255, 0);}\n"
""));

        gridLayout->addWidget(pushButton_call, 7, 0, 1, 1);

        pushButton_cancel = new QPushButton(CallWidget);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setFont(font1);
        pushButton_cancel->setStyleSheet(QLatin1String("QPushButton {  background-color: rgb(255, 255, 0);color: rgb(255, 255, 255); border-radius: 3px; border-color: rgb(127, 127, 127); } QPushButton:hover { background-color: rgb(255, 255, 255);color: rgb(255, 255, 0);}\n"
""));

        gridLayout->addWidget(pushButton_cancel, 8, 0, 1, 1);

        pushButton_order = new QPushButton(CallWidget);
        pushButton_order->setObjectName(QStringLiteral("pushButton_order"));
        pushButton_order->setFont(font1);
        pushButton_order->setStyleSheet(QLatin1String("QPushButton {  background-color: rgb(255, 255, 0);color: rgb(255, 255, 255); border-radius: 3px; border-color: rgb(127, 127, 127); } QPushButton:hover { background-color: rgb(255, 255, 255);color: rgb(255, 255, 0);}\n"
""));

        gridLayout->addWidget(pushButton_order, 9, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 10, 0, 1, 1);

        webView_map = new QWebView(CallWidget);
        webView_map->setObjectName(QStringLiteral("webView_map"));
        webView_map->setAutoFillBackground(true);
        webView_map->setUrl(QUrl(QStringLiteral("qrc:/new/map/test-4.html")));

        gridLayout->addWidget(webView_map, 0, 1, 11, 1);

        gridLayout->setRowStretch(0, 2);
        gridLayout->setRowStretch(1, 1);
        gridLayout->setRowStretch(2, 1);
        gridLayout->setRowStretch(3, 1);
        gridLayout->setRowStretch(4, 1);
        gridLayout->setRowStretch(5, 1);
        gridLayout->setRowStretch(6, 1);
        gridLayout->setRowStretch(7, 1);
        gridLayout->setRowStretch(8, 1);
        gridLayout->setRowStretch(9, 1);
        gridLayout->setRowStretch(10, 2);
        gridLayout->setColumnStretch(0, 3);
        gridLayout->setColumnStretch(1, 5);

        retranslateUi(CallWidget);

        QMetaObject::connectSlotsByName(CallWidget);
    } // setupUi

    void retranslateUi(QWidget *CallWidget)
    {
        CallWidget->setWindowTitle(QApplication::translate("CallWidget", "Form", 0));
        label_DD->setText(QApplication::translate("CallWidget", "DD\346\211\223\350\275\246", 0));
        pushButton_loc->setText(QApplication::translate("CallWidget", "\345\256\232\344\275\215", 0));
        label->setText(QApplication::translate("CallWidget", "\350\265\267\347\202\271", 0));
        label_state->setText(QString());
        label_2->setText(QApplication::translate("CallWidget", "\347\273\210\347\202\271", 0));
        pushButton_call->setText(QApplication::translate("CallWidget", "\345\221\274\345\217\253", 0));
        pushButton_cancel->setText(QApplication::translate("CallWidget", "\345\217\226\346\266\210", 0));
        pushButton_order->setText(QApplication::translate("CallWidget", "\346\237\245\347\234\213\350\256\242\345\215\225", 0));
    } // retranslateUi

};

namespace Ui {
    class CallWidget: public Ui_CallWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALLWIDGET_H
