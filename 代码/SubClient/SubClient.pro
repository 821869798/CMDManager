#-------------------------------------------------
#
# Project created by QtCreator 2015-10-02T13:19:54
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SubClient
TEMPLATE = app


SOURCES += main.cpp \
    maindialog.cpp \
    tool.cpp \
    logindialog.cpp \
    historylistdialog.cpp \
    clockthread.cpp

HEADERS  += \
    maindialog.h \
    tool.h \
    logindialog.h \
    historylistdialog.h \
    clockthread.h

FORMS += \
    maindialog.ui \
    logindialog.ui \
    historylistdialog.ui

RESOURCES += \
    images.qrc

RC_FILE = app.rc
