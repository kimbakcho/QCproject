#ifndef MOLD_SELECT_POPUP_H
#define MOLD_SELECT_POPUP_H

#include <QDialog>
#include <QDebug>
#include <QStandardItemModel>
#include <QSqlTableModel>
#include <QSqlRecord>

namespace Ui {
class mold_select_popup;
}

class mold_select_popup : public QDialog
{
    Q_OBJECT

public:
    explicit mold_select_popup(QWidget *parent = 0);
    QStandardItemModel *modal;
    QSqlTableModel *sqlmodel;
    QModelIndex selectmodel;

    ~mold_select_popup();

private slots:

    void on_buttonBox_accepted();

    void on_mold_addbtn_clicked();

    void on_mold_deletebtn_clicked();



    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::mold_select_popup *ui;
};

#endif // MOLD_SELECT_POPUP_H
