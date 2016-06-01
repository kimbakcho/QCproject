#include "tab1_setting.h"
#include "ui_mainwindow.h"



Tab1_setting::Tab1_setting(MainWindow *mw, QObject *parent) :
    QObject(parent)
{

   this->mw = mw;
    mw->MainWindowui->T1_funtion1->setVisible(false);
    mw->MainWindowui->T1_funtion2->setVisible(false);
    mw->MainWindowui->T1_funtion3->setVisible(false);
    mw->MainWindowui->T1_funtion4->setVisible(false);
    mw->MainWindowui->T1_funtion5->setVisible(false);
    mw->MainWindowui->T1_funtion6->setVisible(false);
    mw->MainWindowui->mold_name_box->addItem("mold_name1");
    mw->MainWindowui->mold_name_box->addItem("mold_name2");
    mw->MainWindowui->mold_name_box->addItem("mold_name3");
}

