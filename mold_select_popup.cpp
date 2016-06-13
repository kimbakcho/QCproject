#include "mold_select_popup.h"
#include "ui_mold_select_popup.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

mold_select_popup::mold_select_popup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mold_select_popup)
{
    ui->setupUi(this);
    remotedb = QSqlDatabase::database("remotedb");
    sqlmodel = new QSqlTableModel(this,remotedb);
    ui->tableView->setModel(sqlmodel);
    sqlmodel->setTable("mold_info");

    sqlmodel->select();
    sqlmodel->setHeaderData(0,Qt::Horizontal,QVariant(tr("금형이름")));
    sqlmodel->setHeaderData(1,Qt::Horizontal,QVariant(tr("아이템이름")));
    sqlmodel->setHeaderData(2,Qt::Horizontal,QVariant(tr("아이템코드")));
    //브런치
}

mold_select_popup::~mold_select_popup()
{
    delete ui;
}

void mold_select_popup::on_buttonBox_accepted()
{
    MainWindow *mw1 = (MainWindow *)parentWidget();
    QSqlQuery query(remotedb);
    QSqlRecord select_recode = sqlmodel->record(selectmodel.row());
    mw1->MainWindowui->mold_name_box->setText(select_recode.value("mold_name").toString());
    mw1->MainWindowui->item_code_label->setText(select_recode.value("item_code").toString());
    mw1->MainWindowui->item_name_label->setText(select_recode.value("item_name").toString());
    QString querystr = QString("update Systeminfo set mold_name = \'%1\',"
                               "item_code = \'%2\',"
                               "item_name = \'%3\' "
                               "where machine_name = \'%4\'")
                                .arg(select_recode.value("mold_name").toString())
                                .arg(select_recode.value("item_code").toString())
                                .arg(select_recode.value("item_name").toString())
                                .arg(mw1->MainWindowui->machinenamelistbox->currentText());
    query.exec(querystr);

    sqlmodel->submit();
}

void mold_select_popup::on_mold_addbtn_clicked()
{
    sqlmodel->insertRow(sqlmodel->rowCount());
    QSqlRecord recode = sqlmodel->record(sqlmodel->rowCount()-1);
    recode.setValue("mold_name","noname");
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

void mold_select_popup::on_search_btn_clicked()
{
    sqlmodel->setFilter(QString("mold_name like \'%1%\'").arg(ui->search_edit->text()));
    sqlmodel->select();
}
