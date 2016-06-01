#ifndef TEMP_MONITER1_H
#define TEMP_MONITER1_H

#include <QWidget>

namespace Ui {
class Temp_moniter1;
}

class Temp_moniter1 : public QWidget
{
    Q_OBJECT

public:
    explicit Temp_moniter1(QWidget *parent = 0);
     Ui::Temp_moniter1 *Temp_moniter1ui;
    ~Temp_moniter1();

private:

};

#endif // TEMP_MONITER1_H
