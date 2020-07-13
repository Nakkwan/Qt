#ifndef PICTUREWIN_H
#define PICTUREWIN_H

#include <QDialog>
#include "QPixmap"
#include <QMessageBox>

namespace Ui {
class PictureWin;
}

class PictureWin : public QDialog
{
    Q_OBJECT

public:
    explicit PictureWin(QWidget *parent = nullptr);
    ~PictureWin();

public slots:
    //signal�� ���� ��η� ������ ������ִ� �ڵ�
    void GetPicturePathFromMain(QString path);


private:
    Ui::PictureWin *ui;
};

#endif // PICTUREWIN_H
