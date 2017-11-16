/********************************************************************************
** Form generated from reading UI file 'LoginWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWIDGET_H
#define UI_LOGINWIDGET_H

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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWidget
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_icon;
    QLabel *label_DD;
    QSpacerItem *horizontalSpacer;
    QLabel *label_error;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_lineEdits;
    QLineEdit *lineEdit_username;
    QLineEdit *lineEdit_password;
    QHBoxLayout *horizontalLayout_buttons;
    QPushButton *pushButton_signup;
    QPushButton *pushButton_signin;

    void setupUi(QWidget *LoginWidget)
    {
        if (LoginWidget->objectName().isEmpty())
            LoginWidget->setObjectName(QStringLiteral("LoginWidget"));
        LoginWidget->setWindowModality(Qt::ApplicationModal);
        LoginWidget->setEnabled(true);
        LoginWidget->resize(240, 400);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LoginWidget->sizePolicy().hasHeightForWidth());
        LoginWidget->setSizePolicy(sizePolicy);
        LoginWidget->setMinimumSize(QSize(240, 400));
        LoginWidget->setMaximumSize(QSize(240, 400));
        LoginWidget->setSizeIncrement(QSize(0, 0));
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
        LoginWidget->setPalette(palette);
        LoginWidget->setFocusPolicy(Qt::NoFocus);
        LoginWidget->setAutoFillBackground(true);
        gridLayout = new QGridLayout(LoginWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 6, 0, 1, 3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        label_icon = new QLabel(LoginWidget);
        label_icon->setObjectName(QStringLiteral("label_icon"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_icon->sizePolicy().hasHeightForWidth());
        label_icon->setSizePolicy(sizePolicy1);
        label_icon->setStyleSheet(QStringLiteral("border-image: url(:/new/icon/car.png);"));

        gridLayout->addWidget(label_icon, 1, 1, 1, 1);

        label_DD = new QLabel(LoginWidget);
        label_DD->setObjectName(QStringLiteral("label_DD"));
        sizePolicy1.setHeightForWidth(label_DD->sizePolicy().hasHeightForWidth());
        label_DD->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\350\241\214\346\245\267"));
        font.setPointSize(18);
        label_DD->setFont(font);
        label_DD->setStyleSheet(QStringLiteral("color: rgb(84, 84, 84);"));
        label_DD->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_DD, 2, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        label_error = new QLabel(LoginWidget);
        label_error->setObjectName(QStringLiteral("label_error"));
        sizePolicy1.setHeightForWidth(label_error->sizePolicy().hasHeightForWidth());
        label_error->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(9);
        label_error->setFont(font1);
        label_error->setStyleSheet(QStringLiteral("color: rgb(84, 84, 84);"));
        label_error->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_error, 4, 0, 1, 3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 0, 1, 1, 1);

        verticalLayout_lineEdits = new QVBoxLayout();
        verticalLayout_lineEdits->setSpacing(6);
        verticalLayout_lineEdits->setObjectName(QStringLiteral("verticalLayout_lineEdits"));
        lineEdit_username = new QLineEdit(LoginWidget);
        lineEdit_username->setObjectName(QStringLiteral("lineEdit_username"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit_username->sizePolicy().hasHeightForWidth());
        lineEdit_username->setSizePolicy(sizePolicy2);
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        lineEdit_username->setFont(font2);
        lineEdit_username->setCursor(QCursor(Qt::IBeamCursor));
        lineEdit_username->setEchoMode(QLineEdit::Normal);
        lineEdit_username->setDragEnabled(false);
        lineEdit_username->setClearButtonEnabled(true);

        verticalLayout_lineEdits->addWidget(lineEdit_username);

        lineEdit_password = new QLineEdit(LoginWidget);
        lineEdit_password->setObjectName(QStringLiteral("lineEdit_password"));
        sizePolicy2.setHeightForWidth(lineEdit_password->sizePolicy().hasHeightForWidth());
        lineEdit_password->setSizePolicy(sizePolicy2);
        lineEdit_password->setFont(font2);
        lineEdit_password->setEchoMode(QLineEdit::Password);
        lineEdit_password->setClearButtonEnabled(false);

        verticalLayout_lineEdits->addWidget(lineEdit_password);


        gridLayout->addLayout(verticalLayout_lineEdits, 3, 0, 1, 3);

        horizontalLayout_buttons = new QHBoxLayout();
        horizontalLayout_buttons->setSpacing(6);
        horizontalLayout_buttons->setObjectName(QStringLiteral("horizontalLayout_buttons"));
        horizontalLayout_buttons->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_buttons->setContentsMargins(5, 5, 5, 5);
        pushButton_signup = new QPushButton(LoginWidget);
        pushButton_signup->setObjectName(QStringLiteral("pushButton_signup"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pushButton_signup->sizePolicy().hasHeightForWidth());
        pushButton_signup->setSizePolicy(sizePolicy3);
        QPalette palette1;
        QBrush brush7(QColor(255, 255, 0, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush7);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush7);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush7);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush7);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush7);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush7);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush2);
        pushButton_signup->setPalette(palette1);
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setWeight(75);
        pushButton_signup->setFont(font3);
        pushButton_signup->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_signup->setAutoFillBackground(false);
        pushButton_signup->setStyleSheet(QLatin1String("QPushButton { background-color: rgb(255, 255, 255); border-radius: 3px; color: rgb(255, 255, 0);border-color: rgb(127, 127, 127); } QPushButton:hover { background-color: rgb(255, 255, 0);color: rgb(255, 255, 255); }\n"
""));

        horizontalLayout_buttons->addWidget(pushButton_signup);

        pushButton_signin = new QPushButton(LoginWidget);
        pushButton_signin->setObjectName(QStringLiteral("pushButton_signin"));
        sizePolicy3.setHeightForWidth(pushButton_signin->sizePolicy().hasHeightForWidth());
        pushButton_signin->setSizePolicy(sizePolicy3);
        pushButton_signin->setFont(font3);
        pushButton_signin->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_signin->setAutoFillBackground(false);
        pushButton_signin->setStyleSheet(QLatin1String("QPushButton {  background-color: rgb(255, 255, 0);color: rgb(255, 255, 255); border-radius: 3px; border-color: rgb(127, 127, 127); } QPushButton:hover { background-color: rgb(255, 255, 255);color: rgb(255, 255, 0);}\n"
""));
        pushButton_signin->setDefault(true);

        horizontalLayout_buttons->addWidget(pushButton_signin);


        gridLayout->addLayout(horizontalLayout_buttons, 5, 0, 1, 3);

        gridLayout->setRowStretch(0, 2);
        gridLayout->setRowStretch(1, 6);
        gridLayout->setRowStretch(2, 2);
        gridLayout->setRowStretch(3, 4);
        gridLayout->setRowStretch(4, 2);
        gridLayout->setRowStretch(5, 3);
        gridLayout->setRowStretch(6, 9);
        gridLayout->setColumnStretch(0, 4);
        gridLayout->setColumnStretch(1, 7);
        gridLayout->setColumnStretch(2, 4);

        retranslateUi(LoginWidget);

        QMetaObject::connectSlotsByName(LoginWidget);
    } // setupUi

    void retranslateUi(QWidget *LoginWidget)
    {
        LoginWidget->setWindowTitle(QApplication::translate("LoginWidget", "DDTaxi", 0));
        label_icon->setText(QString());
        label_DD->setText(QApplication::translate("LoginWidget", "DD\346\211\223\350\275\246", 0));
        label_error->setText(QString());
#ifndef QT_NO_ACCESSIBILITY
        lineEdit_username->setAccessibleDescription(QApplication::translate("LoginWidget", "123", 0));
#endif // QT_NO_ACCESSIBILITY
        lineEdit_username->setPlaceholderText(QApplication::translate("LoginWidget", "\350\257\267\350\276\223\345\205\245\346\211\213\346\234\272\345\217\267\347\240\201", 0));
        lineEdit_password->setInputMask(QString());
        lineEdit_password->setText(QString());
        lineEdit_password->setPlaceholderText(QApplication::translate("LoginWidget", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", 0));
        pushButton_signup->setText(QApplication::translate("LoginWidget", "\346\263\250\345\206\214", 0));
        pushButton_signin->setText(QApplication::translate("LoginWidget", "\347\231\273\345\275\225", 0));
    } // retranslateUi

};

namespace Ui {
    class LoginWidget: public Ui_LoginWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWIDGET_H
