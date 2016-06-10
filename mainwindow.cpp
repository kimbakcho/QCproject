#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tab1_setting.h"
#include "tab2_setting.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    MainWindowui(new Ui::MainWindow)
{
    MainWindowui->setupUi(this);

    disconnect(MainWindowui->machinenamelistbox,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_machinenamelistbox_currentIndexChanged(QString)));
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

    connect(MainWindowui->machinenamelistbox,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_machinenamelistbox_currentIndexChanged(QString)));


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
    litequery1.exec("CREATE TABLE IF NOT EXISTS [temp_setindex]("
                    "[ID] INT NOT NULL DEFAULT 1, "
                    "[temp1] INT NOT NULL DEFAULT 0, "
                    "[temp2] INT NOT NULL DEFAULT 0, "
                    "[temp3] INT NOT NULL DEFAULT 0, "
                    "[temp4] INT NOT NULL DEFAULT 0, "
                    "[temp5] INT NOT NULL DEFAULT 0, "
                    "[temp6] INT NOT NULL DEFAULT 0, "
                    "[temp7] INT NOT NULL DEFAULT 0, "
                    "[temp8] INT NOT NULL DEFAULT 0, "
                    "[temp9] INT NOT NULL DEFAULT 0, "
                    "[temp10] INT NOT NULL DEFAULT 0, "
                    "[temp11] INT NOT NULL DEFAULT 0, "
                    "[temp12] INT NOT NULL DEFAULT 0, "
                    "[temp13] INT NOT NULL DEFAULT 0, "
                    "[temp14] INT NOT NULL DEFAULT 0, "
                    "[temp15] INT NOT NULL DEFAULT 0);"
                );
    litequery1.exec("insert into temp_setindex(temp1) select 0 where not exists(select * from temp_setindex);");

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
    tab2_tempnameinit(MainWindowui->Tab2_temp1,1);
    tab2_tempnameinit(MainWindowui->Tab2_temp2,2);
    tab2_tempnameinit(MainWindowui->Tab2_temp3,3);
    tab2_tempnameinit(MainWindowui->Tab2_temp4,4);
    tab2_tempnameinit(MainWindowui->Tab2_temp5,5);
    tab2_tempnameinit(MainWindowui->Tab2_temp6,6);
    tab2_tempnameinit(MainWindowui->Tab2_temp7,7);
    tab2_tempnameinit(MainWindowui->Tab2_temp8,8);
    tab2_tempnameinit(MainWindowui->Tab2_temp9,9);
    tab2_tempnameinit(MainWindowui->Tab2_temp10,10);
    tab2_tempnameinit(MainWindowui->Tab2_temp11,11);
    tab2_tempnameinit(MainWindowui->Tab2_temp12,12);
    tab2_tempnameinit(MainWindowui->Tab2_temp13,13);
    tab2_tempnameinit(MainWindowui->Tab2_temp14,14);
    tab2_tempnameinit(MainWindowui->Tab2_temp15,15);

}
void MainWindow::tab2_tempnameinit(Temp_moniter1 * temp_data,int number){
    QSqlQuery remotequery(mdb);
    QString querystr = QString("select * from temp_table where machine_name = \'%1\'").arg(MainWindowui->machinenamelistbox->currentText());
    remotequery.exec(querystr);
    remotequery.next();

    if(temp_data->Temp_moniter1ui->comboBox->count() == 0){
        for(int i=1;i<=15;i++){
            QString temp_str = QString("temp%1_name").arg(i);
            temp_data->Temp_moniter1ui->comboBox->addItem(QIcon(":/icon/icon/thermometer.png"),remotequery.value(temp_str).toString());
        }
    }else {
         for(int i=0;i<=15;i++){
             QString temp_str = QString("temp%1_name").arg(i);
             temp_data->Temp_moniter1ui->comboBox->setItemText(i-1,remotequery.value(temp_str).toString());
         }
    }

    temp_data->id = number;
    QSqlQuery litequery1(litedb);
    querystr = QString("select temp%1 from temp_setindex;").arg(number);
    QString coldata1 = QString("temp%1").arg(number);
    litequery1.exec(querystr);
    litequery1.next();
    temp_data->Temp_moniter1ui->comboBox->setCurrentIndex(litequery1.value(coldata1).toInt());

    connect(temp_data->Temp_moniter1ui->comboBox,SIGNAL(currentIndexChanged(int)),temp_data,SLOT(on_comboBox_currentIndexChanged(int)));

}

void MainWindow::on_workstart_btn_clicked()
{
    workstarttimer.start();
    workstarttimer_loop();
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
    tab2_tempdataup(MainWindowui->Tab2_temp2->Temp_moniter1ui);
    tab2_tempdataup(MainWindowui->Tab2_temp3->Temp_moniter1ui);
    tab2_tempdataup(MainWindowui->Tab2_temp4->Temp_moniter1ui);
    tab2_tempdataup(MainWindowui->Tab2_temp5->Temp_moniter1ui);
    tab2_tempdataup(MainWindowui->Tab2_temp6->Temp_moniter1ui);
    tab2_tempdataup(MainWindowui->Tab2_temp7->Temp_moniter1ui);
    tab2_tempdataup(MainWindowui->Tab2_temp8->Temp_moniter1ui);
    tab2_tempdataup(MainWindowui->Tab2_temp9->Temp_moniter1ui);
    tab2_tempdataup(MainWindowui->Tab2_temp10->Temp_moniter1ui);
    tab2_tempdataup(MainWindowui->Tab2_temp11->Temp_moniter1ui);
    tab2_tempdataup(MainWindowui->Tab2_temp12->Temp_moniter1ui);
    tab2_tempdataup(MainWindowui->Tab2_temp13->Temp_moniter1ui);
    tab2_tempdataup(MainWindowui->Tab2_temp14->Temp_moniter1ui);
    tab2_tempdataup(MainWindowui->Tab2_temp15->Temp_moniter1ui);


}
void MainWindow::tab2_tempdataup(Ui_Temp_moniter1 *temp_moniter){
    QString temp_set_name = QString("temp%1_set").arg(temp_moniter->comboBox->currentIndex()+1);
    QString temp_up_name = QString("temp%1_up").arg(temp_moniter->comboBox->currentIndex()+1);
    QString temp_down_name = QString("temp%1_down").arg(temp_moniter->comboBox->currentIndex()+1);
    QString temp_real_name = QString("temp%1_real").arg(temp_moniter->comboBox->currentIndex()+1);
    QSqlQuery remotequery(mdb);
    QString query = QString("select %1,%2,%3,%4 from temp_table where machine_name = \'%5\'")
                                .arg(temp_set_name).arg(temp_up_name).arg(temp_down_name).arg(temp_real_name).arg(MainWindowui->machinenamelistbox->currentText());
    remotequery.exec(query);
    remotequery.next();

    temp_moniter->real_lcd_number->display(remotequery.value(temp_real_name).toDouble()/10.0);
    int real_value = remotequery.value(temp_real_name).toInt()/10;

    int setting_value = remotequery.value(temp_set_name).toInt()/10;
    int up_value =  remotequery.value(temp_up_name).toInt()/10;
    int down_value =  remotequery.value(temp_down_name).toInt()/10;
    up_value = setting_value + up_value;
    down_value = setting_value-down_value;
    temp_moniter->setting_btn->setText(QString("%1").arg(setting_value));

    temp_moniter->up_btn->setText(QString("%1").arg(up_value));
    temp_moniter->down_btn->setText(QString("%1").arg(down_value));
    temp_moniter->tempSlider->setMinimum(down_value);
    temp_moniter->tempSlider->setMaximum(up_value);
    temp_moniter->tempSlider->setValue(real_value);

}

