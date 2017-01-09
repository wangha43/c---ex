QT += core
QT -= gui

TARGET = ffex-1
CONFIG += console
CONFIG -= app_bundle
CONFIG   += link_pkgconfig

PKGCONFIG += libavformat libavcodec libavfilter libavutil

TEMPLATE = app

SOURCES += main.cpp

