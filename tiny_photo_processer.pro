QT       += core gui

QT += widgets

TARGET = tiny_photo_processer
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    awb.cpp \
    imgEditor.cpp \
    IWarp.cpp \

HEADERS += \
    mainwindow.h \
    imgEditor.h \
    awb.h \
    IWarp.h \

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -Werror
