#-------------------------------------------------
#
# Project created by QtCreator 2017-12-27T13:58:46
#
#-------------------------------------------------

QT       += core gui webenginewidgets texttospeech

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DDDriver
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        MainWidget.cpp \
    CallWidget.cpp \
    LoginWidget.cpp \
    MapConn.cpp \
    OrderWidget.cpp \
    SignupWidget.cpp \
    socketapi.cpp \
    TcpClient.cpp \
    Worker.cpp \
    DrvInfo.cpp \
    InfoWidget.cpp

HEADERS += \
        MainWidget.h \
    CallWidget.h \
    DDstructs.h \
    LoginWidget.h \
    MapConn.h \
    OrderWidget.h \
    SignupWidget.h \
    socketapi.h \
    TcpClient.h \
    Worker.h \
    DrvInfo.h \
    InfoWidget.h

FORMS += \
    CallWidget.ui \
    LoginWidget.ui \
    OrderWidget.ui \
    SignupWidget.ui \
    InfoWidget.ui

RESOURCES += \
    ddrsc.qrc
