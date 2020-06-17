#include "searchwin.h"
#include "ui_searchwin.h"

SearchWin::SearchWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchWin)
{
    ui->setupUi(this);
}

SearchWin::~SearchWin()
{
    delete ui;
}
