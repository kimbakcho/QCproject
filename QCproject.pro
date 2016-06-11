#-------------------------------------------------
#
# Project created by QtCreator 2016-05-29T17:37:20
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QCproject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tab1_setting.cpp \
    temp_moniter1.cpp \
    tab2_setting.cpp \
    serversetwidget.cpp \
    mold_select_popup.cpp \
    workmen_select_popup.cpp

HEADERS  += mainwindow.h \
    tab1_setting.h \
    temp_moniter1.h \
    tab2_setting.h \
    serversetwidget.h \
    mold_select_popup.h \
    workmen_select_popup.h

FORMS    += mainwindow.ui \
    temp_moniter1.ui \
    serversetwidget.ui \
    mold_select_popup.ui \
    workmen_select_popup.ui

RESOURCES += \
    Res.qrc
