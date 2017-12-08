/********************************************************************************
** Form generated from reading UI file 'SignupWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUPWIDGET_H
#define UI_SIGNUPWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignupWidget
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QLabel *label_error;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEdit_tel;
    QLineEdit *lineEdit_psw;
    QLabel *label_tel;
    QLineEdit *lineEdit_nickname;
    QLabel *label_psw;
    QLabel *label_nickname;
    QLabel *label_cpsw;
    QLineEdit *lineEdit_cpsw;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_signup;
    QPushButton *pushButton_ret;

    void setupUi(QWidget *SignupWidget)
    {
        if (SignupWidget->objectName().isEmpty())
            SignupWidget->setObjectName(QStringLiteral("SignupWidget"));
        SignupWidget->resize(240, 400);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SignupWidget->sizePolicy().hasHeightForWidth());
        SignupWidget->setSizePolicy(sizePolicy);
        SignupWidget->setMinimumSize(QSize(240, 400));
        SignupWidget->setMaximumSize(QSize(240, 400));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(207, 255, 242, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(231, 255, 248, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(103, 127, 121, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(138, 170, 161, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush3);
        QBrush brush6(QColor(255, 255, 220, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        SignupWidget->setPalette(palette);
        SignupWidget->setAutoFillBackground(true);
        gridLayout = new QGridLayout(SignupWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 0, 1, 1);

        label_error = new QLabel(SignupWidget);
        label_error->setObjectName(QStringLiteral("label_error"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        label_error->setFont(font);
        label_error->setStyleSheet(QStringLiteral("color: rgb(84, 84, 84);"));
        label_error->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_error, 2, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        lineEdit_tel = new QLineEdit(SignupWidget);
        lineEdit_tel->setObjectName(QStringLiteral("lineEdit_tel"));
        lineEdit_tel->setFont(font);

        gridLayout_2->addWidget(lineEdit_tel, 0, 1, 1, 1);

        lineEdit_psw = new QLineEdit(SignupWidget);
        lineEdit_psw->setObjectName(QStringLiteral("lineEdit_psw"));
        lineEdit_psw->setFont(font);
        lineEdit_psw->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(lineEdit_psw, 2, 1, 1, 1);

        label_tel = new QLabel(SignupWidget);
        label_tel->setObjectName(QStringLiteral("label_tel"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        label_tel->setFont(font1);
        label_tel->setStyleSheet(QStringLiteral("color: rgb(84, 84, 84);"));
        label_tel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_tel, 0, 0, 1, 1);

        lineEdit_nickname = new QLineEdit(SignupWidget);
        lineEdit_nickname->setObjectName(QStringLiteral("lineEdit_nickname"));
        lineEdit_nickname->setFont(font);

        gridLayout_2->addWidget(lineEdit_nickname, 1, 1, 1, 1);

        label_psw = new QLabel(SignupWidget);
        label_psw->setObjectName(QStringLiteral("label_psw"));
        label_psw->setFont(font1);
        label_psw->setStyleSheet(QStringLiteral("color: rgb(84, 84, 84);"));
        label_psw->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_psw, 2, 0, 1, 1);

        label_nickname = new QLabel(SignupWidget);
        label_nickname->setObjectName(QStringLiteral("label_nickname"));
        label_nickname->setFont(font1);
        label_nickname->setLayoutDirection(Qt::LeftToRight);
        label_nickname->setStyleSheet(QStringLiteral("color: rgb(84, 84, 84);"));
        label_nickname->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_nickname, 1, 0, 1, 1);

        label_cpsw = new QLabel(SignupWidget);
        label_cpsw->setObjectName(QStringLiteral("label_cpsw"));
        label_cpsw->setFont(font1);
        label_cpsw->setStyleSheet(QStringLiteral("color: rgb(84, 84, 84);"));
        label_cpsw->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_cpsw, 3, 0, 1, 1);

        lineEdit_cpsw = new QLineEdit(SignupWidget);
        lineEdit_cpsw->setObjectName(QStringLiteral("lineEdit_cpsw"));
        lineEdit_cpsw->setFont(font);
        lineEdit_cpsw->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(lineEdit_cpsw, 3, 1, 1, 1);


        gridLayout->addLayout(gridLayout_2, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 4, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(6, 5, 5, 5);
        pushButton_signup = new QPushButton(SignupWidget);
        pushButton_signup->setObjectName(QStringLiteral("pushButton_signup"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_signup->sizePolicy().hasHeightForWidth());
        pushButton_signup->setSizePolicy(sizePolicy1);
        pushButton_signup->setFont(font1);
        pushButton_signup->setStyleSheet(QLatin1String("QPushButton { background-color: rgb(255, 255, 255); border-radius: 3px; color: rgb(255, 255, 0);border-color: rgb(127, 127, 127); } QPushButton:hover { background-color: rgb(255, 255, 0);color: rgb(255, 255, 255); }\n"
""));

        horizontalLayout->addWidget(pushButton_signup);

        pushButton_ret = new QPushButton(SignupWidget);
        pushButton_ret->setObjectName(QStringLiteral("pushButton_ret"));
        sizePolicy1.setHeightForWidth(pushButton_ret->sizePolicy().hasHeightForWidth());
        pushButton_ret->setSizePolicy(sizePolicy1);
        pushButton_ret->setFont(font1);
        pushButton_ret->setStyleSheet(QLatin1String("QPushButton {  background-color: rgb(255, 255, 0);color: rgb(255, 255, 255); border-radius: 3px; border-color: rgb(127, 127, 127); } QPushButton:hover { background-color: rgb(255, 255, 255);color: rgb(255, 255, 0);}\n"
""));

        horizontalLayout->addWidget(pushButton_ret);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);

        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 1);

        gridLayout->setRowStretch(0, 2);
        gridLayout->setRowStretch(1, 3);
        gridLayout->setRowStretch(2, 1);
        gridLayout->setRowStretch(3, 1);
        gridLayout->setRowStretch(4, 3);

        retranslateUi(SignupWidget);

        QMetaObject::connectSlotsByName(SignupWidget);
    } // setupUi

    void retranslateUi(QWidget *SignupWidget)
    {
        SignupWidget->setWindowTitle(QApplication::translate("SignupWidget", "Form", 0));
        label_error->setText(QString());
        label_tel->setText(QApplication::translate("SignupWidget", "\346\211\213\346\234\272\345\217\267\347\240\201", 0));
        label_psw->setText(QApplication::translate("SignupWidget", "\347\231\273\345\275\225\345\257\206\347\240\201", 0));
        label_nickname->setText(QApplication::translate("SignupWidget", "\345\247\223\345\220\215", 0));
        label_cpsw->setText(QApplication::translate("SignupWidget", "\347\241\256\350\256\244\345\257\206\347\240\201", 0));
        pushButton_signup->setText(QApplication::translate("SignupWidget", "\346\263\250\345\206\214", 0));
        pushButton_ret->setText(QApplication::translate("SignupWidget", "\350\277\224\345\233\236", 0));
    } // retranslateUi

};

namespace Ui {
    class SignupWidget: public Ui_SignupWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUPWIDGET_H
