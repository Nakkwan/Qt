#include "mainwindow.h"
#include <QApplication>

//운영체제 HW
//Scheduling
//최낙관 2016101124

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
