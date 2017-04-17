#-------------------------------------------------
#
# Project created by QtCreator 2014-01-19T15:26:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += sql
TARGET = Adminka
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mycrypto.cpp \
    myfiles.cpp \
    mysubd.cpp \
    form.cpp

HEADERS  += mainwindow.h \
    mylistlink.h \
    mycrypto.h \
    KeyKripto.h \
    myfiles.h \
    myotwet.h \
    myvopros.h \
    mytest.h \
    myadmin.h \
    mytestsavlod.h \
    mysubd.h \
    form.h \
    optionotwet.h \
    otwetkey.h

FORMS    += mainwindow.ui \
    form.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/conect/lib/ -llibmysql
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/conect/lib/ -llibmysql

INCLUDEPATH += $$PWD/conect/include
DEPENDPATH += $$PWD/conect/include


RESOURCES += \
    resours.qrc

