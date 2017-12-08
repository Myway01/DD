/********************************************************************************
** Form generated from reading UI file 'ordWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDWIDGET_H
#define UI_ORDWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ordWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QTextBrowser *textBrowser_ord;
    QPushButton *pushButton_ret;

    void setupUi(QWidget *ordWidget)
    {
        if (ordWidget->objectName().isEmpty())
            ordWidget->setObjectName(QStringLiteral("ordWidget"));
        ordWidget->resize(240, 400);
        ordWidget->setMinimumSize(QSize(240, 400));
        ordWidget->setMaximumSize(QSize(240, 400));
        ordWidget->setAutoFillBackground(true);
        ordWidget->setStyleSheet(QStringLiteral("background-color: rgb(207, 255, 242);"));
        gridLayout = new QGridLayout(ordWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(ordWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\350\241\214\346\245\267"));
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setLayoutDirection(Qt::LeftToRight);
        label->setStyleSheet(QStringLiteral("color: rgb(108, 108, 108);"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        textBrowser_ord = new QTextBrowser(ordWidget);
        textBrowser_ord->setObjectName(QStringLiteral("textBrowser_ord"));

        gridLayout->addWidget(textBrowser_ord, 1, 0, 1, 1);

        pushButton_ret = new QPushButton(ordWidget);
        pushButton_ret->setObjectName(QStringLiteral("pushButton_ret"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        pushButton_ret->setFont(font1);
        pushButton_ret->setStyleSheet(QLatin1String("QPushButton {  background-color: rgb(255, 255, 0);color: rgb(255, 255, 255); border-radius: 3px; border-color: rgb(127, 127, 127); } QPushButton:hover { background-color: rgb(255, 255, 255);color: rgb(255, 255, 0);}\n"
""));

        gridLayout->addWidget(pushButton_ret, 2, 0, 1, 1);


        retranslateUi(ordWidget);

        QMetaObject::connectSlotsByName(ordWidget);
    } // setupUi

    void retranslateUi(QWidget *ordWidget)
    {
        ordWidget->setWindowTitle(QApplication::translate("ordWidget", "Form", 0));
        label->setText(QApplication::translate("ordWidget", "\346\210\221\347\232\204\350\256\242\345\215\225", 0));
        pushButton_ret->setText(QApplication::translate("ordWidget", "\350\277\224\345\233\236", 0));
    } // retranslateUi

};

namespace Ui {
    class ordWidget: public Ui_ordWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDWIDGET_H
