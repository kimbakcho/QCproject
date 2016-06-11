#include "workmen_select_popup.h"
#include "ui_workmen_select_popup.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

workmen_select_popup::workmen_select_popup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::workmen_select_popup)
{
    ui->setupUi(this);
    remotedb = QSqlDatabase::database("remotedb");
    sqlmodel = new QSqlTableModel(this,remotedb);
    ui->tableView->setModel(sqlmodel);
    sqlmodel->setTable("works");
    sqlmodel->select();
    sqlmodel->setHeaderData(0,Qt::Horizontal,QVariant(tr("사번")));
    sqlmodel->setHeaderData(1,Qt::Horizontal,QVariant(tr("이름")));
    sqlmodel->setHeaderData(2,Qt::Horizontal,QVariant(tr("시간")));
}
workmen_select_popup::~workmen_select_popup()
{
    delete ui;
}

void workmen_select_popup::on_add_btn_clicked()
{
    sqlmodel->insertRow(sqlmodel->rowCount());
    QSqlRecord recode = sqlmodel->record(sqlmodel->rowCount()-1);
    recode.setValue("number","0");
    sqlmodel->setRecord(sqlmodel->rowCount()-1,recode);
}

void workmen_select_popup::on_delete_btn_clicked()
{
    sqlmodel->removeRow(selectmodel.row());
}

void workmen_select_popup::on_tableView_clicked(const QModelIndex &index)
{
    selectmodel = index;
}


void workmen_select_popup::on_search_btn_clicked()
{
    sqlmodel->setFilter(QString("name like \'%1%\'").arg(ui->search_edit->text()));
    sqlmodel->select();
}

void workmen_select_popup::on_workmen_select_popup_accepted()
{
    MainWindow *mw1 = (MainWindow *)parentWidget();
    QSqlQuery query(remotedb);
    QSqlRecord select_recode = sqlmodel->record(selectmodel.row());
    mw1->MainWindowui->works_name_label->setText(select_recode.value("name").toString());
    QString querystr  = QString("update Systeminfo set worker = \'%1\'"
                                "where machine_name = \'%2\'")
                                .arg(select_recode.value("name").toString())
                                .arg(mw1->MainWindowui->machinenamelistbox->currentText());
    query.exec(querystr);
    sqlmodel->submit();
}
