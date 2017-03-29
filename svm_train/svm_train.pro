QT += core
QT -= gui

TARGET = svm_train
CONFIG += console link_pkgconfig
CONFIG -= app_bundle
PKGCONFIG+=opencv

TEMPLATE = app

SOURCES += main.cpp

