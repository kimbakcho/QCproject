#include "serversetwidget.h"
#include "ui_serversetwidget.h"

Serversetwidget::Serversetwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Serversetwidget)
{
    ui->setupUi(this);
}

Serversetwidget::~Serversetwidget()
{
    delete ui;
}
