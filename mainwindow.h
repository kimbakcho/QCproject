#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <serversetwidget.h>




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    Ui::MainWindow *MainWindowui;
    QSqlDatabase mdb;
    QSqlDatabase litedb;
    Serversetwidget *serverwidget;
    bool machinenamelistbox_currentIndexChanged;
    bool mold_name_box_currentIndexChanged;
    void litesql_init();
    void remotesql_connect();
    void remotesql_init();
    void remote_init_read_machineinfo();
    void machine_change_init(QString machinename);
    ~MainWindow();

private slots:



    void on_serverset_triggered();

    void on_machinenamelistbox_currentIndexChanged(const QString &arg1);


private:


};

#endif // MAINWINDOW_H
