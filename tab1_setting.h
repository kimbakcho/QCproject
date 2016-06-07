#ifndef TAB1_SETTING_H
#define TAB1_SETTING_H

#include <QObject>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
/*
 *
 *   Tab1 init setting calss
 *
 */

class Tab1_setting : public QObject
{
    Q_OBJECT
public:
    explicit Tab1_setting(MainWindow *mw, QObject *parent = 0);
    MainWindow *mw;
    QStringList COMitem1_list;
    QSqlDatabase remotedb;
    QSqlDatabase litedb;


signals:

public slots:



};

#endif // TAB1_SETTING_H
