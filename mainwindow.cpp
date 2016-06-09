#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tab1_setting.h"
#include "tab2_setting.h"
#include "ui_temp_moniter1.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    MainWindowui(new Ui::MainWindow)
{
    MainWindowui->setupUi(this);

    machinenamelistbox_currentIndexChanged = false;
    mold_name_box_currentIndexChanged = false;
    litesql_init();
    serverwidget = new Serversetwidget();
    remotesql_connect();

    QSqlQuery query(mdb);
    query.exec("select machine_name from Systeminfo");
    while(query.next()){
          MainWindowui->machinenamelistbox->addItem(query.value("machine_name").toString());
    }

    //초반 데이터 생성
    QSqlQuery loccalquery(litedb);
    loccalquery.exec("select current_macine_name from systemset");
    loccalquery.next();
    MainWindowui->machinenamelistbox->setCurrentText(loccalquery.value("current_macine_name").toString());


    machine_change_init(loccalquery.value("current_macine_name").toString());



    workstarttimer.setInterval(1000);
    connect(&workstarttimer,SIGNAL(timeout()),this,SLOT(workstarttimer_loop()));



    Tab1_setting *t1_setting;
    t1_setting = new Tab1_setting(this);
    Tab2_setting *t2_setting;
    t2_setting = new Tab2_setting(this);


    mold_name_box_currentIndexChanged = true;
    machinenamelistbox_currentIndexChanged=true;
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
    QSqlQuery remotequery(mdb);
    QString querystr = QString("select * from Systeminfo where machine_name = \'%1\'").arg(machinename);
    remotequery.exec(querystr);
    remotequery.next();
    MainWindowui->mold_name_box->setText(remotequery.value("mold_name").toString());
    MainWindowui->machine_name_btn->setText(machinename);
    MainWindowui->item_name_label->setText(remotequery.value("item_name").toString());
    MainWindowui->item_code_label->setText(remotequery.value("item_code").toString());
    MainWindowui->works_name_label->setText(remotequery.value("worker").toString());
    MainWindowui->orders_count_LE->setText(remotequery.value("orders_count").toString());
    MainWindowui->cycle_time_label->setText(remotequery.value("cycle_time").toString());
    MainWindowui->cabit_count->setText(remotequery.value("cabity").toString());
    MainWindowui->object_count_led->display(remotequery.value("object_count").toInt());
    MainWindowui->production_count_lcd->display(remotequery.value("production_count").toInt());
    MainWindowui->achievemen_rate_lcd->display(remotequery.value("achievemen_rate").toDouble());
    MainWindowui->good_count_lcd->display(remotequery.value("good_count").toInt());
    MainWindowui->poor_count_lcd->display(remotequery.value("poor_count").toInt());
    MainWindowui->weight_lcd->display(remotequery.value("weight").toDouble());
    tab2_tempnameinit(MainWindowui->Tab2_temp1->Temp_moniter1ui->comboBox);
    tab2_tempnameinit(MainWindowui->Tab2_temp2->Temp_moniter1ui->comboBox);
    tab2_tempnameinit(MainWindowui->Tab2_temp3->Temp_moniter1ui->comboBox);
    tab2_tempnameinit(MainWindowui->Tab2_temp4->Temp_moniter1ui->comboBox);
    tab2_tempnameinit(MainWindowui->Tab2_temp5->Temp_moniter1ui->comboBox);
    tab2_tempnameinit(MainWindowui->Tab2_temp6->Temp_moniter1ui->comboBox);
    tab2_tempnameinit(MainWindowui->Tab2_temp7->Temp_moniter1ui->comboBox);
    tab2_tempnameinit(MainWindowui->Tab2_temp8->Temp_moniter1ui->comboBox);
    tab2_tempnameinit(MainWindowui->Tab2_temp9->Temp_moniter1ui->comboBox);
    tab2_tempnameinit(MainWindowui->Tab2_temp10->Temp_moniter1ui->comboBox);
    tab2_tempnameinit(MainWindowui->Tab2_temp11->Temp_moniter1ui->comboBox);
    tab2_tempnameinit(MainWindowui->Tab2_temp12->Temp_moniter1ui->comboBox);
    tab2_tempnameinit(MainWindowui->Tab2_temp13->Temp_moniter1ui->comboBox);
    tab2_tempnameinit(MainWindowui->Tab2_temp14->Temp_moniter1ui->comboBox);
    tab2_tempnameinit(MainWindowui->Tab2_temp15->Temp_moniter1ui->comboBox);

}
void MainWindow::tab2_tempnameinit(QComboBox * box){
    box->clear();
    QSqlQuery remotequery(mdb);
    QString querystr = QString("select * from temp_table where machine_name = \'%1\'").arg(MainWindowui->machinenamelistbox->currentText());
    remotequery.exec(querystr);
    remotequery.next();
    box->addItem(QIcon(":/icon/icon/thermometer.png"),remotequery.value("temp1_name").toString());
    box->addItem(QIcon(":/icon/icon/thermometer.png"),remotequery.value("temp2_name").toString());
    box->addItem(QIcon(":/icon/icon/thermometer.png"),remotequery.value("temp3_name").toString());
    box->addItem(QIcon(":/icon/icon/thermometer.png"),remotequery.value("temp4_name").toString());
    box->addItem(QIcon(":/icon/icon/thermometer.png"),remotequery.value("temp5_name").toString());
    box->addItem(QIcon(":/icon/icon/thermometer.png"),remotequery.value("temp6_name").toString());
    box->addItem(QIcon(":/icon/icon/thermometer.png"),remotequery.value("temp7_name").toString());
    box->addItem(QIcon(":/icon/icon/thermometer.png"),remotequery.value("temp8_name").toString());
    box->addItem(QIcon(":/icon/icon/thermometer.png"),remotequery.value("temp9_name").toString());
    box->addItem(QIcon(":/icon/icon/thermometer.png"),remotequery.value("temp10_name").toString());
    box->addItem(QIcon(":/icon/icon/thermometer.png"),remotequery.value("temp11_name").toString());
    box->addItem(QIcon(":/icon/icon/thermometer.png"),remotequery.value("temp12_name").toString());
    box->addItem(QIcon(":/icon/icon/thermometer.png"),remotequery.value("temp13_name").toString());
    box->addItem(QIcon(":/icon/icon/thermometer.png"),remotequery.value("temp14_name").toString());
    box->addItem(QIcon(":/icon/icon/thermometer.png"),remotequery.value("temp15_name").toString());
    box->addItem(QIcon(":/icon/icon/thermometer.png"),remotequery.value("temp16_name").toString());
    box->addItem(QIcon(":/icon/icon/thermometer.png"),remotequery.value("temp17_name").toString());
    box->addItem(QIcon(":/icon/icon/thermometer.png"),remotequery.value("temp18_name").toString());
    box->addItem(QIcon(":/icon/icon/thermometer.png"),remotequery.value("temp19_name").toString());
    box->addItem(QIcon(":/icon/icon/thermometer.png"),remotequery.value("temp20_name").toString());
    box->addItem(QIcon(":/icon/icon/thermometer.png"),remotequery.value("temp21_name").toString());
}

void MainWindow::on_workstart_btn_clicked()
{
    workstarttimer.start();
}

void MainWindow::workstarttimer_loop(){
    if(MainWindowui->tabWidget->currentIndex()== WORKPLANTAB){
        workplantab_loop();
    }else if(MainWindowui->tabWidget->currentIndex() == TEMPMONITERNTAB){
        tempmonitertab_loop();
    }
}
void MainWindow::workplantab_loop(){

}
void MainWindow::tempmonitertab_loop(){

    QSqlQuery remotequery(mdb);
    QString querystr = QString("select * from temp_table where machine_name = \'%1\'")
                                .arg(MainWindowui->machinenamelistbox->currentText());
    remotequery.exec(querystr);
    tab2_tempdataup(MainWindowui->Tab2_temp1->Temp_moniter1ui);

}
void MainWindow::tab2_tempdataup(Ui_Temp_moniter1 *temp_moniter){
    QString temp_set_name = QString("temp%1_set").arg(temp_moniter->comboBox->currentIndex()+1);
    QString temp_up_name = QString("temp%1_up").arg(temp_moniter->comboBox->currentIndex()+1);
    QString temp_down_name = QString("temp%1_down").arg(temp_moniter->comboBox->currentIndex()+1);
    QString temp_real_name = QString("temp%1_real").arg(temp_moniter->comboBox->currentIndex()+1);
    QSqlQuery remotequery(mdb);
    QString query = QString("select %1,%2,%3,%4 from temp_table where machine_name = \'%5\'")
                                .arg(temp_set_name).arg(temp_up_name).arg(temp_down_name).arg(temp_real_name).arg(MainWindowui->machinenamelistbox->currentText());
    qDebug()<<query;
    qDebug()<<remotequery.value(3).toInt();
    remotequery.exec(query);
    //temp_moniter->real_lcd_number->display(;

}

