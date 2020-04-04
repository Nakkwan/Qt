#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(myfunction()));
    timer->start(1000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myfunction()
{
//    static int count = 0;
//    qDebug() << "update...";
//    count++;
//    if(count == 5){
//    timer->stop();
//    qDebug() << "finish...";
//    }

    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm : ss");
    if(time.second() % 2 == 0){
        time_text[3] = ' ';
        time_text[8] = ' ';
    }
    ui->label_dateTime->setText(time_text);
}

