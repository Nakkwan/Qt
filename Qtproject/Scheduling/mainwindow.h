#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "SortedLinkedList.h"
#include "SortedIterator.h"
#include "Task.h"
#include <stdlib.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Chart {                                  //struct for check if correspond time is scheduling
    QString name = "";
    bool In = false;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /*
     * @brief: Add Periodic task to List
     * @pre: set periodic plaintextedit
     * @post: periodic tasks are add to List
    */
    void AddPeriodic();

    /*
     * @brief: Add Aperiodic task to List
     * @pre: set Aperiodic plaintextedit
     * @post: Aperiodic tasks are add to List
    */
    void AddAperiodic();

    /*
     * @brief: Set Polling serer for polling scheduling
     * @pre: set textedit for capacity and period of polling server
     * @post: set pollingserver
    */
    void SetPollingServer();

    /*
     * @brief: Get HyperPeriod by periodic tasks
     * @pre: set periodic tasks
     * @post: HyperPeriod is caculated
     * @return: HyperPeriod
    */
    int GetHyperPeriod();

    /*
     * @brief: scheduling periodic tasks
     * @pre: set periodic tasks and caculate HyperPeriod
     * @post: periodic tasks are scheduled and set GanttChart
    */
    int SetPeriodic(Chart *chrt);

    /*
     * @brief: scheduling Aperiodic tasks
     * @pre: set Aperiodic tasks and caculate HyperPeriod
     * @post: Aperiodic tasks are scheduled and set GanttChart
    */
    int SetAperiodic(Chart *chrt);

    /*
     * @brief: scheduling Aperiodic tasks according to polling server
     * @pre: set Aperiodic tasks and polling server
     * @post: Aperiodic tasks are scheduled and set GanttChart
    */
    void SetPolling(Chart *chrt);

    /*
     * @brief: initialize GanttChart according to tasks
     * @pre: set tasks
     * @post: frame of GanttChart are complete
    */
    void SetGantt();

private slots:
    void on_BackgroundButton_clicked();

    void on_PollingButton_clicked();

private:
    Ui::MainWindow *ui;                             //MainWindow
    SortedLinkedList<Task> Periodic_List;           //List of Periodic tasks
    SortedLinkedList<Task> Aperiodic_List;          //List of Aperiodic tasks
    Task PollingServer;                             //Polling server task
    int P_length;                                   //Number of Periodic Tasks
    int A_length;                                   //Number of Aperiodic Tasks
    int Hyper;                                      //HyperPeriod
    float average;                                  //Average delay time
};
#endif // MAINWINDOW_H
