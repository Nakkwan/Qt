#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    QDir dir("C:/Users/cvvc1/Desktop/Qt/Tutorial/QDirDemo");
    QDir dir;
    foreach (QFileInfo var, dir.drives()) {
        ui->comboBox->addItem(var.absoluteFilePath());
    }

    QDir dir_2("C:/Users/cvvc1/Desktop/Qt/Tutorial/QDirDemo");
    foreach (QFileInfo var, dir_2.entryInfoList()) {
        if(var.isDir()){
            ui->listWidget->addItem("Dir: " + var.absoluteFilePath());
        } else if(var.isFile()){
            ui->listWidget->addItem("File: " + var.absoluteFilePath());
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QDir dir_3("C:/Users/cvvc1/Desktop/Qt/Tutorial/QDirDemo/img");
    if(dir_3.exists()){
        QMessageBox::information(this, "title", "Dir exist");
    } else{
        dir_3.mkpath("C:/Users/cvvc1/Desktop/Qt/Tutorial/QDirDemo/img");
        dir_3.mkdir("yyy");
    }
}
