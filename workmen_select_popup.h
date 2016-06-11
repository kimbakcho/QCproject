#ifndef WORKMEN_SELECT_POPUP_H
#define WORKMEN_SELECT_POPUP_H

#include <QDialog>
#include <QStandardItemModel>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlDatabase>

namespace Ui {
class workmen_select_popup;
}

class workmen_select_popup : public QDialog
{
    Q_OBJECT

public:
    explicit workmen_select_popup(QWidget *parent = 0);
    QSqlTableModel *sqlmodel;
    QModelIndex selectmodel;
    QSqlDatabase remotedb;
    ~workmen_select_popup();

private slots:
    void on_add_btn_clicked();

    void on_delete_btn_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_search_btn_clicked();

    void on_workmen_select_popup_accepted();

private:
    Ui::workmen_select_popup *ui;
};

#endif // WORKMEN_SELECT_POPUP_H
