#ifndef TAB2_SETTING_H
#define TAB2_SETTING_H

#include <QObject>
#include "mainwindow.h"
/*
 *
 *   Tab1 init setting calss
 *
 */
class Tab2_setting : public QObject
{
    Q_OBJECT
public:
    explicit Tab2_setting(MainWindow *mw,QObject *parent = 0);
    MainWindow *mw;

signals:

public slots:

};

#endif // TAB2_SETTING_H
