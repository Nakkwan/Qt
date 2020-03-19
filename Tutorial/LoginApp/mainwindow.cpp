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

    /*set picture from local folder*/
//    QPixmap pix("C:/Users/cvvc1/Pictures/Saved Pictures/ship.jpg");

    /*Set picture from resource file in Qt*/
    QPixmap pix(":/Resource/img/ship.jpg");
    int w = ui->label_pic->width();
    int h = ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->statusbar->addPermanentWidget(ui->label_3, 0);
    ui->statusbar->addPermanentWidget(ui->progressBar, 0);


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
//        QMessageBox::information(this, "Login", "Username and password is correct");
//        hide();
//        secDialog = new SecDialog(this);
//        secDialog->show();
        ui->statusbar->showMessage("Username and password is correct", 5000);
        ui->label_3->setText("Login");
    }else {
//        QMessageBox::warning(this, "Login", "Username and password isn't correct");
        ui->statusbar->showMessage("Username and password is not correct", 5000);
        ui->label_3->setText("Error");
    }
}
