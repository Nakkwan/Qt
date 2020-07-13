#include "picturewin.h"
#include "ui_picturewin.h"

PictureWin::PictureWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PictureWin)
{
    ui->setupUi(this);
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    setWindowTitle(QString::fromLocal8Bit("»çÁø"));

}

PictureWin::~PictureWin()
{
    delete ui;
}


void PictureWin::GetPicturePathFromMain(QString path){
    QPixmap pix(path);
    int w = ui->pic_label->width();
    int h = ui->pic_label->height();
    ui->pic_label->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
    ui->pic_path_label->setText(path);
    if(pix.isNull()){
        this->hide();
        QMessageBox::warning(this, "Invaild path", "Error: Cannot Show Picture");
    }
}
