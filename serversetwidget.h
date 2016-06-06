#ifndef SERVERSETWIDGET_H
#define SERVERSETWIDGET_H

#include <QWidget>

namespace Ui {
class Serversetwidget;
}

class Serversetwidget : public QWidget
{
    Q_OBJECT

public:
    explicit Serversetwidget(QWidget *parent = 0);
    ~Serversetwidget();

private:
    Ui::Serversetwidget *ui;
};

#endif // SERVERSETWIDGET_H
