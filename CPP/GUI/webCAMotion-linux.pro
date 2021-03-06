#-------------------------------------------------
#
# Project created by QtCreator 2015-03-20T14:47:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CPP-QtCreator
TEMPLATE = app

CONFIG += link_pkgconfig
PKGCONFIG += x11 xtst opencv

SOURCES += main.cpp\
           mainwindow.cpp \
           about.cpp \
           notimplemented.cpp \
           selectsomething.cpp \
           rocvl.cpp \
           rlgpl.cpp \
           core/core.cpp \
    errormsgafterfailure.cpp \
    core/core.os.cpp \
    core/disp.x11.cpp \
    core/disp.win32.cpp

HEADERS  += mainwindow.h \
            about.h \
            notimplemented.h \
            selectsomething.h \
            rocvl.h \
            rlgpl.h \
    errormsgafterfailure.h \
    core/core.h

FORMS    += mainwindow.ui \
            about.ui \
            notimplemented.ui \
            selectsomething.ui \
            rocvl.ui \
            rlgpl.ui \
    errormsgafterfailure.ui

OTHER_FILES +=
