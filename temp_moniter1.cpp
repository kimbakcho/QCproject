#include "temp_moniter1.h"
#include "ui_temp_moniter1.h"

Temp_moniter1::Temp_moniter1(QWidget *parent) :
    QWidget(parent),
    Temp_moniter1ui(new Ui::Temp_moniter1)
{
    Temp_moniter1ui->setupUi(this);
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
