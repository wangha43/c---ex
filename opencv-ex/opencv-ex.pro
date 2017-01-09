QT += core
QT -= gui

TARGET = opencv-ex
CONFIG += console link_pkgconfig
PKGCONFIG +=opencv libavformat libavcodec libavfilter libavutil
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    gmm.cpp

HEADERS += \
    gmm.h

