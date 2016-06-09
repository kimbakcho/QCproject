#ifndef TEMP_MONITER1_H
#define TEMP_MONITER1_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
namespace Ui {
class Temp_moniter1;
}

class Temp_moniter1 : public QWidget
{
    Q_OBJECT

public:
    explicit Temp_moniter1(QWidget *parent = 0);
     Ui::Temp_moniter1 *Temp_moniter1ui;
     bool on_comboBox_currentIndexChanged_flag;
     int id;
    ~Temp_moniter1();

private slots:
     void on_up_btn_clicked();

     void on_setting_btn_clicked();

     void on_down_btn_clicked();

     void on_comboBox_currentIndexChanged(int index);

private:

};

#endif // TEMP_MONITER1_H
