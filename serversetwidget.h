#ifndef SERVERSETWIDGET_H
#define SERVERSETWIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

namespace Ui {
class Serversetwidget;
}

class Serversetwidget : public QWidget
{
    Q_OBJECT

public:
    explicit Serversetwidget(QWidget *parent = 0);
    QSqlDatabase litedb;
    ~Serversetwidget();

private slots:
    void on_applybtn_clicked();

private:
    Ui::Serversetwidget *ui;
};

#endif // SERVERSETWIDGET_H
