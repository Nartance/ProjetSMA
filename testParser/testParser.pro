#-------------------------------------------------
#
# Project created by QtCreator 2015-01-22T18:40:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testParser
TEMPLATE = app


SOURCES += main.cpp\
        parser.cpp \
    Mur.cpp \
    parserfactory.cpp

HEADERS  += parser.h \
    Mur.hpp \
    main.hpp \
    parserfactory.h

FORMS    += parser.ui
