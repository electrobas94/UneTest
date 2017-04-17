#-------------------------------------------------
#
# Project created by QtCreator 2014-07-08T18:13:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += sql
TARGET = Rezult
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myfiles.cpp \
    mysubd.cpp \
    grafikzdraw.cpp

HEADERS  += mainwindow.h \
    myprintrezult.h \
    myfiles.h \
    mylistlink.h \
    mysubd.h \
    grafikzdraw.h

FORMS    += mainwindow.ui \
    grafikzdraw.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/conect/lib/ -llibmysql
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/conect/lib/ -llibmysql

INCLUDEPATH += $$PWD/conect/include
DEPENDPATH += $$PWD/conect/include
