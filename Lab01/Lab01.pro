#-------------------------------------------------
#
# Project created by QtCreator 2018-02-25T13:47:16
#
#-------------------------------------------------

QT       += core gui xml sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab01
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    Parsers/gpxparser.cpp \
    dbmanager.cpp \
    Commands/command.cpp \
    Commands/import.cpp \
    commandmanager.cpp \
    commandfactory.cpp \
    Commands/createroute.cpp \
    Commands/reset.cpp \
    Commands/removeroute.cpp \
    Commands/createpoint.cpp \
    Commands/removepoint.cpp \
    ../../GooglePolylineCoder/GooglePolylineCoder/googlepolylinecoder.cpp \
    Commands/renameroute.cpp \
    Commands/changelongitude.cpp \
    Commands/changelatitude.cpp \
    pointssaver.cpp \
    model.cpp \
    presenter.cpp \
    Commands/importpolyline.cpp

HEADERS  += mainwindow.h \
    Parsers/gpxparser.h \
    dbmanager.h \
    Commands/command.h \
    Commands/import.h \
    commandmanager.h \
    commandfactory.h \
    Commands/createroute.h \
    Commands/reset.h \
    Commands/removeroute.h \
    Commands/createpoint.h \
    Commands/removepoint.h \
    ../../GooglePolylineCoder/GooglePolylineCoder/googlepolylinecoder.h \
    Commands/renameroute.h \
    Commands/changelongitude.h \
    Commands/changelatitude.h \
    pointssaver.h \
    model.h \
    presenter.h \
    errorlevel.h \
    Commands/importpolyline.h

FORMS    += mainwindow.ui
