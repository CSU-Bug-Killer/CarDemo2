#-------------------------------------------------
#
# Project created by QtCreator 2017-07-03T14:29:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Demo2
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    map.cpp \
    welcomepage.cpp \
    lightcontrollboard.cpp \
    carcontrollboard.cpp \
    carmap.cpp

HEADERS  += widget.h \
    map.h \
    welcomepage.h \
    lightcontrollboard.h \
    carcontrollboard.h \
    carmap.h

FORMS    += widget.ui \
    welcomepage.ui \
    map.ui \
    lightcontrollboard.ui \
    carcontrollboard.ui \
    carmap.ui

RESOURCES += \
    icons.qrc \
    qss.qrc

DISTFILES += \
    widget.qss
