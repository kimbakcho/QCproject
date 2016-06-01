#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tab1_setting.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    MainWindowui(new Ui::MainWindow)
{
    MainWindowui->setupUi(this);
    Tab1_setting *t1_setting;
    t1_setting = new Tab1_setting(this);



}



MainWindow::~MainWindow()
{
    delete MainWindowui;
}
