#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "secwin.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
//    //if secWindow opened, I can't approach mainWindow until secWindow closed1
//    //Because it will created by stack object
//    SecWin secWindow;
//    secWindow.setModal(true);
//    secWindow.exec();

    //hide();         //hide mainwindow when pushbutton clicked

    //create pointer in mainwindow.h for create object by heap
    delete secWindow;
    secWindow = new SecWin(this);
    secWindow->show();

}
