#ifndef SEARCHWIN_H
#define SEARCHWIN_H

#include <QWidget>

namespace Ui {
class Searchwin;
}

class Searchwin : public QWidget
{
    Q_OBJECT

public:
    explicit Searchwin(QWidget *parent = nullptr);
    ~Searchwin();

private:
    Ui::Searchwin *ui;
};

#endif // SEARCHWIN_H
