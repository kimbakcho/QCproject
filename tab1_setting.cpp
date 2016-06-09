#include "tab1_setting.h"

Tab1_setting::Tab1_setting(MainWindow *mw, QObject *parent) :
    QObject(parent)
{
   this->mw = mw;
    remotedb = QSqlDatabase::database("remotedb");
    litedb = QSqlDatabase::database("localdb");


    mw->MainWindowui->T1_funtion1 ->setVisible(false);
    mw->MainWindowui->T1_funtion2->setVisible(false);
    mw->MainWindowui->T1_funtion3->setVisible(false);
    mw->MainWindowui->T1_funtion4->setVisible(false);
    mw->MainWindowui->T1_funtion5->setVisible(false);
    mw->MainWindowui->T1_funtion6->setVisible(false);

}

