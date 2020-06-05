#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#define MAXPROCESS 10
#define MAXINSTANCE 5


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Banker{
    QString process[MAXPROCESS];                        //프로세스의 이름 P0부터 순차적으로 증가
    QString instance[MAXINSTANCE];                      //각 인스턴스의 이름 A부터 순차적으로 증가
    int instMax[MAXINSTANCE];                           //각 인스턴스의 최대 할당값
    int allocation[MAXPROCESS][MAXINSTANCE];            //현재 할당된 수
    int max[MAXPROCESS][MAXINSTANCE];                   //각 process의 instance당 max
    int available[MAXINSTANCE];                         //available
    int need[MAXPROCESS][MAXINSTANCE];                  //need
    int work[MAXINSTANCE];                              //safety algorithm에서 계산을 위한 work
    int finish[MAXPROCESS];                             //safety algorithm에서 할당 해제가 끝난 건지 여부
    int request[MAXINSTANCE];                           //요청한 process에 관한 instance의 개수
    QString request_flag[MAXPROCESS];                   //safety algorithm에서 우선 할당되는 process 순으로 입력을 위함
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
