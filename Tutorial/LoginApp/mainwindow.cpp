#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include <QMessageBox>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/cvvc1/Pictures/Saved Pictures/ship.jpg");
    int w = ui->label_pic->width();
    int h = ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Login_clicked()
{
    QString username = ui->Username->text();
    QString password = ui->Password->text();
    if(username == "test" && password == "test"){
        QMessageBox::information(this, "Login", "Username and password is correct");
        hide();
        secDialog = new SecDialog(this);
        secDialog->show();
    }else {
        QMessageBox::warning(this, "Login", "Username and password isn't correct");
    }
}
