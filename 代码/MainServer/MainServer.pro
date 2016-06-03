#-------------------------------------------------
#
# Project created by QtCreator 2015-10-03T14:25:35
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MainServer
TEMPLATE = app


SOURCES += main.cpp \
    tool.cpp \
    tcpserver.cpp \
    tcpsocket.cpp \
    sendthread.cpp \
    historylistdialog.cpp \
    readysenddialog.cpp \
    maindialog.cpp \
    clientconfigdialog.cpp \
    addsenddatadialog.cpp \
    itemform.cpp

HEADERS  += \
    tool.h \
    tcpserver.h \
    tcpsocket.h \
    sendthread.h \
    historylistdialog.h \
    readysenddialog.h \
    maindialog.h \
    clientconfigdialog.h \
    addsenddatadialog.h \
    itemform.h

FORMS += \
    historylistdialog.ui \
    readysenddialog.ui \
    maindialog.ui \
    clientconfigdialog.ui \
    addsenddatadialog.ui \
    itemform.ui

RESOURCES += \
    images.qrc

RC_FILE = app.rc
