#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tab1_setting.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    MainWindowui(new Ui::MainWindow)
{
    MainWindowui->setupUi(this);

    machinenamelistbox_currentIndexChanged = true;
    mold_name_box_currentIndexChanged = false;
    litesql_init();
    serverwidget = new Serversetwidget();
    remotesql_connect();

    Tab1_setting *t1_setting;
    t1_setting = new Tab1_setting(this);

    //초반 데이터 생성
    QSqlQuery loccalquery(litedb);
    loccalquery.exec("select current_macine_name from systemset");
    loccalquery.next();
    MainWindowui->machinenamelistbox->setCurrentText(loccalquery.value("current_macine_name").toString());


    mold_name_box_currentIndexChanged = true;
}



MainWindow::~MainWindow()
{
    delete MainWindowui;
}

void MainWindow::litesql_init(){
    litedb = QSqlDatabase::addDatabase("QSQLITE","localdb");
    litedb.setDatabaseName("local.db");
    if(!litedb.open()){
        qDebug()<<"localdb open fail";
        //ui->logtext->append("localdb open fail");
    }else {
       // ui->logtext->append("localdb open");
    }
    QSqlQuery litequery1(litedb);
    litequery1.exec("CREATE TABLE  IF NOT EXISTS systemset (remoteserverip TEXT,"
                    "remoteserverport TEXT,"
                    "remoteserverdbname TEXT,"
                    "version INTEGER,"
                    "remoteserverusername TEXT,"
                    "remoteserveruserpassword TEXT,"
                    "current_macine_name TEXT"
                    ");");
    //만약조건이없다면 업데이트
    litequery1.exec("insert into systemset(remoteserverip,"
                    "remoteserverport,"
                    "remoteserverdbname,"
                    "version,"
                    "remoteserverusername,"
                    "remoteserveruserpassword,"
                    "current_macine_name) "
                    "select \'127.0.0.1\',"
                    "\'3306\',"
                    "\'QCproject\',"
                    "1,"
                    "\'QCmen\',"
                    "\'1234\', "
                    "\'select\'"
                    "where not exists(select * from systemset);");
}
void MainWindow::remotesql_connect(){
    QSqlQuery litequery1(litedb);
    litequery1.exec("select * from systemset;");
    litequery1.next();
    mdb =QSqlDatabase::addDatabase("QMYSQL","remotedb");
    mdb.setHostName(litequery1.value("remoteserverip").toString());
    mdb.setDatabaseName(litequery1.value("remoteserverdbname").toString());
    mdb.setPort(litequery1.value("remoteserverport").toInt());
    mdb.setUserName(litequery1.value("remoteserverusername").toString());
    mdb.setPassword(litequery1.value("remoteserveruserpassword").toString());

    if(!mdb.open()){
        qDebug()<<"DB not open";
        //ui->logtext->append("DB not open");
    }else {
        //ui->logtext->append("remtoe DB open");
    }
}


void MainWindow::on_serverset_triggered()
{
    serverwidget->show();
}

void MainWindow::on_machinenamelistbox_currentIndexChanged(const QString &arg1)
{
    if(!machinenamelistbox_currentIndexChanged){
        return;
    }
    QSqlQuery litequery1(litedb);
    QString querystr = QString("update systemset set current_macine_name = \'%1\'").arg(arg1);
    litequery1.exec(querystr);
    machine_change_init(arg1);

}

//사출기 교체후 인터페이스 초기화 작업
void MainWindow::machine_change_init(QString machinename){
    QSqlQuery litequery1(mdb);
    QString querystr = QString("select * from Systeminfo where machine_name = \'%1\'").arg(machinename);
    litequery1.exec(querystr);
    litequery1.next();
    MainWindowui->mold_name_box->setText(litequery1.value("mold_name").toString());
    MainWindowui->machine_name_btn->setText(machinename);
    MainWindowui->item_name_label->setText(litequery1.value("item_name").toString());
    MainWindowui->item_code_label->setText(litequery1.value("item_code").toString());
    MainWindowui->works_name_label->setText(litequery1.value("worker").toString());
    MainWindowui->orders_count_LE->setText(litequery1.value("orders_count").toString());
    MainWindowui->cycle_time_label->setText(litequery1.value("cycle_time").toString());
    MainWindowui->cabit_count->setText(litequery1.value("cabity").toString());
    MainWindowui->object_count_led->display(litequery1.value("object_count").toInt());
    MainWindowui->production_count_lcd->display(litequery1.value("production_count").toInt());
    MainWindowui->achievemen_rate_lcd->display(litequery1.value("achievemen_rate").toDouble());
    MainWindowui->good_count_lcd->display(litequery1.value("good_count").toInt());
    MainWindowui->poor_count_lcd->display(litequery1.value("poor_count").toInt());
    MainWindowui->weight_lcd->display(litequery1.value("weight").toDouble());

}
