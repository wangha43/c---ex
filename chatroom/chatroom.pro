QT += core network widgets gui

TARGET = chatroom
CONFIG += console
CONFIG +=qt
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    myserver.cpp \
    mythread.cpp \
    dialog.cpp

HEADERS += \
    myserver.h \
    mythread.h \
    dialog.h
