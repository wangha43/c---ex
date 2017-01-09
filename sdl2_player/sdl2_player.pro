QT += core
QT -= gui

TARGET = sdl2_player
CONFIG += console link_pkgconfig
CONFIG -= app_bundle

PKGCONFIG+=libavcodec libavfilter libavutil libavdevice libavformat libswscale libpostproc sdl2

TEMPLATE = app

SOURCES += main.cpp

