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
    loccalquery.exec("select current_macine_name from systemset");
    loccalquery.next();
    mw->MainWindowui->machinenamelistbox->setCurrentText(loccalquery.value("current_macine_name").toString());

    mw->MainWindowui->T1_funtion1 ->setVisible(false);
    mw->MainWindowui->T1_funtion2->setVisible(false);
    mw->MainWindowui->T1_funtion3->setVisible(false);
    mw->MainWindowui->T1_funtion4->setVisible(false);
    mw->MainWindowui->T1_funtion5->setVisible(false);
    mw->MainWindowui->T1_funtion6->setVisible(false);
    query.exec("select mold_name from mold_info");
    while(query.next()){
          mw->MainWindowui->mold_name_box->addItem(query.value("mold_name").toString());
    }
    QString quertstr = QString("select mold_name from Systeminfo where machine_name = \'%1\'")
            .arg(mw->MainWindowui->machinenamelistbox->currentText());
    query.exec(quertstr);
    query.next();
    mw->MainWindowui->mold_name_box->setCurrentText(query.value("mold_name").toString());



}

