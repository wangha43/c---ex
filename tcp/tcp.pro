QT += core network
QT -= gui

TARGET = tcp
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    tcpserver.cpp

HEADERS += tcpserver.h\

