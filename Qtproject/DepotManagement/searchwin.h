#ifndef SEARCHWIN_H
#define SEARCHWIN_H

#include <QDialog>

namespace Ui {
class SearchWin;
}

class SearchWin : public QDialog
{
    Q_OBJECT

public:
    explicit SearchWin(QWidget *parent = nullptr);
    ~SearchWin();

private:
    Ui::SearchWin *ui;
};

#endif // SEARCHWIN_H
