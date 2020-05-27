#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#define MAXPROCESS 10
#define MAXINSTANCE 5


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Banker{
    QString process[MAXPROCESS];
    QString instance[MAXINSTANCE];
    int instMax[MAXINSTANCE];
    int allocation[MAXPROCESS][MAXINSTANCE];
    int max[MAXPROCESS][MAXINSTANCE];
    int available[MAXINSTANCE];
    int need[MAXPROCESS][MAXINSTANCE];
    int work[MAXINSTANCE];
    int finish[MAXPROCESS];
    int request[MAXINSTANCE];
    QString request_flag[MAXPROCESS];
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SetTable();
    void Init();
    void Setallocation();
    void SetNeed();
    void SetAvailable();
    bool safety();

private slots:
    void on_SettingpushButton_clicked();

    void on_InitialpushButton_clicked();

    void on_RequestpushButton_clicked();

private:
    Ui::MainWindow *ui;
    Banker banker;
    int num_process;
    int num_instance;
};
#endif // MAINWINDOW_H
