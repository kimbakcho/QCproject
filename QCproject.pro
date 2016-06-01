#-------------------------------------------------
#
# Project created by QtCreator 2016-05-29T17:37:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QCproject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tab1_setting.cpp \
    temp_moniter1.cpp \
    tab2_setting.cpp

HEADERS  += mainwindow.h \
    tab1_setting.h \
    temp_moniter1.h \
    tab2_setting.h

FORMS    += mainwindow.ui \
    temp_moniter1.ui

RESOURCES += \
    Res.qrc
