#include "mold_select_popup.h"
#include "ui_mold_select_popup.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

mold_select_popup::mold_select_popup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mold_select_popup)
{
    ui->setupUi(this);
    QSqlDatabase remotedb = QSqlDatabase::database("remotedb");
    QSqlQuery query(remotedb);
    query.exec("select * from mold_info");
    sqlmodel = new QSqlTableModel(this,remotedb);
    ui->tableView->setModel(sqlmodel);
    sqlmodel->setTable("mold_info");
    sqlmodel->select();
    sqlmodel->setHeaderData(0,Qt::Horizontal,QVariant(tr("금형이름")));
    sqlmodel->setHeaderData(1,Qt::Horizontal,QVariant(tr("캐비티")));
    sqlmodel->setHeaderData(2,Qt::Horizontal,QVariant(tr("아이템이름")));
    sqlmodel->setHeaderData(3,Qt::Horizontal,QVariant(tr("아이템코드")));
}

mold_select_popup::~mold_select_popup()
{
    delete ui;
}

void mold_select_popup::on_buttonBox_accepted()
{
    MainWindow *mw1 = (MainWindow *)parentWidget();
    sqlmodel->submit();
}

void mold_select_popup::on_mold_addbtn_clicked()
{
    sqlmodel->insertRow(sqlmodel->rowCount());
    QSqlRecord recode = sqlmodel->record(sqlmodel->rowCount()-1);
    recode.setValue("mold_name","noname");
    recode.setValue("cabity_count",0);
    sqlmodel->setRecord(sqlmodel->rowCount()-1,recode);

}

void mold_select_popup::on_mold_deletebtn_clicked()
{
    sqlmodel->removeRow(selectmodel.row());
}



void mold_select_popup::on_tableView_clicked(const QModelIndex &index)
{
    selectmodel = index;
}
