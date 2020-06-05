#include "searchwin.h"
#include "ui_searchwin.h"

Searchwin::Searchwin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Searchwin)
{
    ui->setupUi(this);
}

Searchwin::~Searchwin()
{
    delete ui;
}
