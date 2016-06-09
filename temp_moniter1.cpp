#include "temp_moniter1.h"
#include "ui_temp_moniter1.h"

Temp_moniter1::Temp_moniter1(QWidget *parent) :
    QWidget(parent),
    Temp_moniter1ui(new Ui::Temp_moniter1)
{
    Temp_moniter1ui->setupUi(this);
    disconnect(Temp_moniter1ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(on_comboBox_currentIndexChanged(int)));

    id = 0;
//    Temp_moniter1ui->comboBox->addItem(QIcon(":/icon/icon/thermometer.png"),tr("온도1"));
//    Temp_moniter1ui->comboBox->addItem(QIcon(":/icon/icon/thermometer.png"),tr("온도2"));
//    Temp_moniter1ui->comboBox->addItem(QIcon(":/icon/icon/thermometer.png"),tr("온도3"));
//    Temp_moniter1ui->comboBox->addItem(QIcon(":/icon/icon/thermometer.png"),tr("온도4"));
//    Temp_moniter1ui->comboBox->addItem(QIcon(":/icon/icon/thermometer.png"),tr("온도5"));
//    Temp_moniter1ui->comboBox->addItem(QIcon(":/icon/icon/thermometer.png"),tr("온도6"));
//    Temp_moniter1ui->comboBox->addItem(QIcon(":/icon/icon/thermometer.png"),tr("온도7"));
//    Temp_moniter1ui->comboBox->addItem(QIcon(":/icon/icon/thermometer.png"),tr("온도8"));
//    Temp_moniter1ui->comboBox->addItem(QIcon(":/icon/icon/thermometer.png"),tr("금형온도1"));
//    Temp_moniter1ui->comboBox->addItem(QIcon(":/icon/icon/thermometer.png"),tr("금형온도2"));
//    Temp_moniter1ui->comboBox->addItem(QIcon(":/icon/icon/thermometer.png"),tr("금형온도3"));
//    Temp_moniter1ui->comboBox->addItem(QIcon(":/icon/icon/thermometer.png"),tr("금형온도4"));
//    Temp_moniter1ui->comboBox->addItem(QIcon(":/icon/icon/thermometer.png"),tr("금형온도5"));
//    Temp_moniter1ui->comboBox->addItem(QIcon(":/icon/icon/thermometer.png"),tr("금형온도6"));
//    Temp_moniter1ui->comboBox->addItem(QIcon(":/icon/icon/thermometer.png"),tr("금형온도7"));
//    Temp_moniter1ui->comboBox->addItem(QIcon(":/icon/icon/thermometer.png"),tr("금형온도8"));

}

Temp_moniter1::~Temp_moniter1()
{
    delete Temp_moniter1ui;
}

void Temp_moniter1::on_up_btn_clicked()
{
    //추후 자신의 콤보 박스를 보고 업데이트 하기 DB에 요청 쿼리 날리기 직접 하기 않기
}

void Temp_moniter1::on_setting_btn_clicked()
{
    //추후 자신의 콤보 박스를 보고 업데이트 하기 DB에 요청 쿼리 날리기 직접 하기 않기
}

void Temp_moniter1::on_down_btn_clicked()
{
    //추후 자신의 콤보 박스를 보고 업데이트 하기 DB에 요청 쿼리 날리기 직접 하기 않기
}

void Temp_moniter1::on_comboBox_currentIndexChanged(int index)
{

    QSqlDatabase localdb = QSqlDatabase::database("localdb");
    QSqlQuery query(localdb);
    QString querystr = QString("update temp_setindex set temp%1 = %2").arg(id).arg(index);
    query.exec(querystr);
}
