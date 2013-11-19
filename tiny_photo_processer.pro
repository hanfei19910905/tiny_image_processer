QT       += core gui

QT += widgets

TARGET = tiny_photo_processer
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    imgEditor.hpp \
    awb.hpp \
    IWarp.hpp

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -Werror
