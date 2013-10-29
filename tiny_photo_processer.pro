#-------------------------------------------------
#
# Project created by QtCreator 2013-10-23T15:46:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tiny_photo_processer
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv2/
LIBS += /usr/local/lib/*.so

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    DisplayImage.hpp \
    algo.hpp

FORMS    += mainwindow.ui
