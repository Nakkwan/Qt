#include "picturewin.h"
#include "ui_picturewin.h"

PictureWin::PictureWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PictureWin)
{
    ui->setupUi(this);
}

PictureWin::~PictureWin()
{
    delete ui;
}
