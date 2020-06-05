#ifndef ADDWIN_H
#define ADDWIN_H

#include <QWidget>

namespace Ui {
class Addwin;
}

class Addwin : public QWidget
{
    Q_OBJECT

public:
    explicit Addwin(QWidget *parent = nullptr);
    ~Addwin();

private:
    Ui::Addwin *ui;
};

#endif // ADDWIN_H
