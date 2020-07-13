#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include <ctime>

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
    int year,month, date;
    time_t timer;
    time(&timer);
    tm* ti;
    gmtime_s(ti, &timer);

//    ui->dateEdit->date().getDate(&year, &month, &date);
    uint t = ui->dateEdit->dateTime().toTime_t();
    qDebug() << ti->tm_min << " " << ti->tm_sec << " " << (ti->tm_hour + 8) % 24 << endl;
}
