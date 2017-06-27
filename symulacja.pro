#-------------------------------------------------
#
# Project created by QtCreator 2015-12-24T23:02:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = symulacja
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    config.cpp

HEADERS  += mainwindow.h \
    types.h \
    config.h

include(Database/Database.pri)
include(Editor/Editor.pri)
include(Map/Map.pri)
include(Traffic/Traffic.pri)
