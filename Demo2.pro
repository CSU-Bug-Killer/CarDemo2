#-------------------------------------------------
#
# Project created by QtCreator 2017-07-03T14:29:08
#
#-------------------------------------------------

!include( ./myCharts/examples.pri ) {
 error( "Couldn't find the examples.pri file!" )
}

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = Demo2
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    map.cpp \
    welcomepage.cpp \
    lightcontrollboard.cpp \
    carcontrollboard.cpp \
    carmap.cpp \
    autonavigation.cpp \
    navigationcontrollboard.cpp \
    setting.cpp \
    about.cpp \
    communicawidget.cpp \
    singlemap.cpp \
    flowcount.cpp \
    database.cpp \
    flowcontrolboard.cpp


HEADERS  += widget.h \
    map.h \
    welcomepage.h \
    lightcontrollboard.h \
    carcontrollboard.h \
    carmap.h \
    autonavigation.h \
    navigationcontrollboard.h \
    setting.h \
    about.h \
    communicawidget.h \
    singlemap.h \
    flowcount.h \
    initdb.h \
    database.h \
    flowcontrolboard.h

FORMS    += widget.ui \
    welcomepage.ui \
    map.ui \
    lightcontrollboard.ui \
    carcontrollboard.ui \
    carmap.ui \
    autonavigation.ui \
    navigationControllBoard.ui \
    about.ui \
    setting.ui \
    flowcount.ui \
    flowcontrolboard.ui

RESOURCES += \
    icons.qrc \
    qss.qrc \
    src.qrc

DISTFILES += \
    widget.qss \
    myCharts/examples.pri
