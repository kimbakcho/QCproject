#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define WORKPLANTAB 0
#define TEMPMONITERNTAB 1

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <serversetwidget.h>
#include <QTimer>
#include <QComboBox>
#include "ui_temp_moniter1.h"
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
    QTimer workstarttimer;
    void litesql_init();
    void remotesql_connect();
    void remotesql_init();
    void remote_init_read_machineinfo();
    void machine_change_init(QString machinename);
    void workplantab_loop();
    void tempmonitertab_loop();
    void tab2_tempnameinit(QComboBox *box);
    void tab2_tempdataup(Ui_Temp_moniter1 *temp_moniter);
    ~MainWindow();

private slots:



    void on_serverset_triggered();

    void on_machinenamelistbox_currentIndexChanged(const QString &arg1);


    void on_workstart_btn_clicked();

    void workstarttimer_loop();

private:


};

#endif // MAINWINDOW_H
