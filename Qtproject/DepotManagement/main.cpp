#include "pch.h"
#include <QApplication>
#include <QTimer>
#include <QSplashScreen>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap("images/LoadingImage.png");                  //�ε�ȭ�� ����
    QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);
    splash.show();
    QTimer::singleShot(2000, &splash, SLOT(close()));
    MainWindow w;
    QTimer::singleShot(2000, &w, SLOT(show()));
    return a.exec();
}
