#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

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
    QFile ofile("C:/Users/cvvc1/Desktop/Qt/Tutorial/QFileDemo/myfile.txt");
    if(!ofile.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "title", "File is not open");
    }
    else {
        QTextStream out(&ofile);
        QString text = ui->plainTextEdit->toPlainText();
        out << text;
        ofile.flush();
        ofile.close();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QFile ifile("C:/Users/cvvc1/Desktop/Qt/Tutorial/QFileDemo/myfile.txt");
    if(!ifile.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "title", "File is not open");
    }
    else {
        QTextStream in(&ifile);
        QString text = in.readAll();
        ui->plainTextEdit->setPlainText(text);
        ifile.close();
    }
}
