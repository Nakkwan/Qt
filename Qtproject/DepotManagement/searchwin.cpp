#include "pch.h"
#include "searchwin.h"
#include "ui_searchwin.h"
#include <QWindow>
#include <QPainter>
#include <QStyleOption>
#include "Windows.h"

SearchWin::SearchWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchWin)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromLocal8Bit("검색"));
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    connect(this, SIGNAL(ObjectLabel(int)), SearchWin::parent(), SLOT(GetObjectLabel(int)));
    connect(this, SIGNAL(ObjectName(QString)), SearchWin::parent(), SLOT(GetObjectName(QString)));
    connect(this, SIGNAL(ObjectDate(int, int)), SearchWin::parent(), SLOT(GetObjectDate(int, int)));
    connect(this, SIGNAL(ObjectDueDate(int)), SearchWin::parent(), SLOT(GetObjectDueDate(int)));
    connect(this, SIGNAL(StorageLabel(int)), SearchWin::parent(), SLOT(GetStorageLabel(int)));
    connect(this, SIGNAL(FloorLabel(int, int)), SearchWin::parent(), SLOT(GetFloorLabel(int, int)));
    connect(this, SIGNAL(PicturePath(QString)), SearchWin::parent(), SLOT(GetPicturePath(QString)));
    connect(this, SIGNAL(PictureLabel(int)), SearchWin::parent(), SLOT(GetPictureLabel(int)));
    connect(this, SIGNAL(ObjectType(QString)), SearchWin::parent(), SLOT(GetObjectType(QString)));
}



SearchWin::~SearchWin()
{
    delete ui;
}

void SearchWin::on_Object_Label_pushButton_clicked()
{
    int label = ui->Object_Label_plainTextEdit->toPlainText().toInt();
    emit ObjectLabel(label);
}

void SearchWin::on_Object_Name_pushButton_clicked()
{
    QString name = ui->Object_Name_plainTextEdit->toPlainText();
    emit ObjectName(name);
}

bool CheckD(int year, int month, int day) {					//날짜의 유효성 확인
    if ((month % 2 == 1)) //odd month
    {
        if (month <= 7){
            if (day <= 0 || day > 31) {
                return false;
            }
        }
        else{ // month > 7
            if (day <= 0 || day > 30) {
                return false;
            }
        }
    }
    else //even month
    {
        if (month <= 6) {
            if (month == 2)
            {
                if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) // leap year
                {
                    if (day <= 0 || day > 30) return false;
                }
                else if (day <= 0 || day > 28) return false;

            }
            if (day <= 0 || day > 30) return false;
        }
        else { // month > 6

            if (day <= 0 || day > 31) return false;
        }
    }
    return true;
}

void SearchWin::on_Object_Date_pushButton_clicked()
{
    int from = ui->Object_Date_From_plainText->toPlainText().toInt();
    if(!CheckD(from / 10000, from % 10000 / 100, from % 100) || !(from > 10000 && from < 99999999)){
        QMessageBox::warning(this, "Input Error", "Error: Invalid Date");
        return ;
    }
    int to = ui->Object_Date_To_plainText->toPlainText().toInt();
    if(!CheckD(to / 10000, to % 10000 / 100, to % 100) || !(to > 10000 && to < 99999999)){
        QMessageBox::warning(this, "Input Error", "Error: Invalid Date");
        return ;
    }
    emit ObjectDate(from, to);
}

void SearchWin::on_Object_DueDate_pushButton_clicked()
{
    int duedate = ui->Object_DueDate_plainTextEdit->toPlainText().toInt();
    if(!CheckD(duedate / 10000, duedate % 10000 / 100, duedate % 100) || !(duedate > 10000 && duedate < 99999999)){
        QMessageBox::warning(this, "Input Error", "Error: Invalid Date");
        return ;
    }
    emit ObjectDueDate(duedate);
}

void SearchWin::on_Storage_pushButton_clicked()
{
    int sto = ui->Storage_plainTextEdit->toPlainText().toInt();
    emit StorageLabel(sto);
}

void SearchWin::on_Floor_pushButton_clicked()
{
    int sto = ui->Storage_plainTextEdit->toPlainText().toInt();
    int flo = ui->Floor_plainTextEdit->toPlainText().toInt();
    emit FloorLabel(sto, flo);
}

void SearchWin::on_Picture_Path_pushButton_clicked()
{
    QString Path = ui->Picture_Path_plainTextEdit->toPlainText();
    emit PicturePath(Path);
}

void SearchWin::on_Picture_Label_pushButton_clicked()
{
    int label = ui->Picture_Label_plainTextEdit->toPlainText().toInt();
    emit PictureLabel(label);
}


void SearchWin::on_Object_Type_pushButton_clicked()
{
    QString type = ui->Object_Type_plainTextEdit->toPlainText();
    emit ObjectType(type);
}
