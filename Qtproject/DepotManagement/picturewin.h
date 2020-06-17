#ifndef PICTUREWIN_H
#define PICTUREWIN_H

#include <QDialog>

namespace Ui {
class PictureWin;
}

class PictureWin : public QDialog
{
    Q_OBJECT

public:
    explicit PictureWin(QWidget *parent = nullptr);
    ~PictureWin();

private:
    Ui::PictureWin *ui;
};

#endif // PICTUREWIN_H
