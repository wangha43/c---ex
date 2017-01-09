QT += core
QT -= gui

TARGET = opencv-ex1
CONFIG += console
CONFIG += link_pkgconfig
CONFIG -= app_bundle

PKGCONFIG+=opencv

TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

HEADERS +=bgfg_cb.h
SOURCES +=main.cpp \
    bgfg_cb.cpp

