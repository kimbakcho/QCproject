#include "tab1_setting.h"

Tab1_setting::Tab1_setting(MainWindow *mw, QObject *parent) :
    QObject(parent)
{
   this->mw = mw;
    remotedb = QSqlDatabase::database("remotedb");
    litedb = QSqlDatabase::database("localdb");
    QSqlQuery query(remotedb);
    QSqlQuery loccalquery(litedb);

    query.exec("select machine_name from Systeminfo");
    while(query.next()){
          mw->MainWindowui->machinenamelistbox->addItem(query.value("machine_name").toString());
    }

    mw->MainWindowui->T1_funtion1 ->setVisible(false);
    mw->MainWindowui->T1_funtion2->setVisible(false);
    mw->MainWindowui->T1_funtion3->setVisible(false);
    mw->MainWindowui->T1_funtion4->setVisible(false);
    mw->MainWindowui->T1_funtion5->setVisible(false);
    mw->MainWindowui->T1_funtion6->setVisible(false);

}

