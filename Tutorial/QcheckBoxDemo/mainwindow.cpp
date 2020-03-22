#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->checkBox->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if(ui->checkBox->isChecked()){
        ui->checkBox->setCheckState(Qt::CheckState::Unchecked);
        ui->pushButton->setText("Check");
    } else{
        ui->checkBox->setCheckState(Qt::CheckState::Checked);
        ui->pushButton->setText("Uncheck");
    }
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1){
        QMessageBox::information(this, "title", "Yes User likes apples");
    } else {
        QMessageBox::information(this, "title", "No User don't likes apples");
    }
}
