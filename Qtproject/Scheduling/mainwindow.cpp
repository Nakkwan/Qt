#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "QTextBlock"
#include "QTableWidgetItem"
#include "QTableWidget"
#include "QColor"

MainWindow::MainWindow(QWidget *parent)             //constructor
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Scheduling");
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    average = 0;
    A_length = 0;
    P_length = 0;
    Hyper = 0;
}

MainWindow::~MainWindow()                           //destructor
{
    delete ui;
}

void MainWindow::AddPeriodic(){
    QString tex = ui->PeriodicTextEdit->toPlainText();                      //Get data of periodic task from PlainText
    while(tex.endsWith(' ') || tex.endsWith('\n')) tex.chop(1);             //Delete unnessesary part
    while(tex.startsWith(' ') || tex.startsWith('\n')) tex.remove(0, 1);
    if(tex.isEmpty()){
        P_length = 0;
    }else{
        QStringList phara = tex.split('\n');                                //split string to task
        for(int i = 0; i < phara.size(); i++){
            QStringList line = phara.at(i).split(" ");                      //split string to data(computation, period)
            Task data;
            QString name =  "P" + QString::number(i + 1);                       //set task
            data.SetName(name);
            data.SetIndex(i+1);
            data.SetComputation(line.at(0).toInt());
            data.SetPeriod(line.at(1).toInt());
            Periodic_List.Add(data);
        }
        P_length = phara.size();
    }
}

void MainWindow::AddAperiodic(){
    QString tex = ui->AperiodicTextEdit->toPlainText();                     //Get data of aperiodic task from PlainText
    while(tex.endsWith(' ') || tex.endsWith('\n')) tex.chop(1);             //Delete unnessesary part
    while(tex.startsWith(' ') || tex.startsWith('\n')) tex.remove(0, 1);
    if(tex.isEmpty()){
        A_length = 0;
    }
    else {
        QStringList phara = tex.split('\n');                                //split string to task
        for(int i = 0; i < phara.size(); i++){
            QStringList line = phara.at(i).split(" ");                      //split string to data(computation, arrival time)
            Task data;
            QString name =  "AP" + QString::number(i + 1);                      //set task
            data.SetName(name);
            data.SetIndex(P_length + i + 1);
            data.SetComputation(line.at(0).toInt());
            data.SetPeriod(line.at(1).toInt());
            Aperiodic_List.Add(data);
        }
        A_length = phara.size();
    }
}

void MainWindow::SetPollingServer(){                                        //set polling server task
    QString capacity = ui->capacityText->toPlainText();
    QString period = ui->periodText->toPlainText();
    while(capacity.endsWith(' ') || capacity.endsWith('\n')) capacity.chop(1);          //Delete unnessesary part
    while(capacity.startsWith(' ') || capacity.startsWith('\n')) capacity.remove(0, 1);
    while(period.endsWith(' ') || period.endsWith('\n')) period.chop(1);
    while(period.startsWith(' ') || period.startsWith('\n')) period.remove(0, 1);
    PollingServer.SetName("P");
    PollingServer.SetPeriod(period.toInt());
    PollingServer.SetComputation(capacity.toInt());
}

void MainWindow::SetGantt(){                                                //set GanttChart
    ui->GanttChart->clear();
    ui->GanttChart->setRowCount(P_length + A_length + 1);                   //set Row num
    ui->GanttChart->setColumnCount(Hyper + 1);                              //set col num
    SortedIterator<Task> itor(Periodic_List);
    SortedIterator<Task> aitor(Aperiodic_List);
    Task data;
    Task adata;
    data = itor.Next();
    adata = aitor.Next();
    for(int i = 1; i <= ui->GanttChart->rowCount(); i++){                   //set row Head of GanttChart by name of tasks
        QTableWidgetItem* head = new QTableWidgetItem;
        if(itor.NextNotNull()){
            head->setText(data.GetName());
            ui->GanttChart->setItem(i,0, head);
            data = itor.Next();
            continue;
        }
        if(aitor.NextNotNull()){
            head->setText(adata.GetName());
            ui->GanttChart->setItem(i,0, head);
            adata = aitor.Next();
            continue;
        }
    }
    for(int i = 1; i < Hyper + 1; i++){                                     //set col Head of GanttChart(Quantum time)
        QTableWidgetItem* head = new QTableWidgetItem;
        head->setText(QString::number(i - 1));
        ui->GanttChart->setItem(0, i, head);
    }
}

int MainWindow::GetHyperPeriod(){                                           //Get HyperPeriod
    int count = 0;
    int* peri = new int[P_length];
    SortedIterator<Task> itor(Periodic_List);
    Task data;
    data = itor.Next();
    while (itor.NextNotNull()) {
        peri[count] = data.GetPeriod();
        data = itor.Next();
        count++;
    }
    count = 0;
    bool hy = true;
    while (1) {
        count++;
        for (int i = 0; i < P_length; i++) {
            if (count % peri[i] != 0) {
                hy = false;
                break;
            }
        }
        if (hy == false) {                                                  //Check if HyperPeriod
            hy = true;
            continue;
        }
        delete [] peri;
        return count;
    }
}

int MainWindow::SetPeriodic(Chart *chrt){                                   //scheduling of periodic tasks
    SortedIterator<Task> itor(Periodic_List);
        Task data;
        QString T_name;
        QBrush brush;
        brush = QColor(156,194,229);
        int peri, com, count = 0;
        int n;
        itor.Next();
        while (itor.NextNotNull()) {
            n = 0;
            data = itor.GetCurrentNode().value;
            peri = data.GetPeriod();
            com = data.GetComputation();
            count = peri * n;
            while (count < Hyper) {                                         //until hyper period
                for (int i = 0; i < com; i++) {                             //for computation
                    while (1) {
                        if (count < peri * (n + 1)) {                       //check if scheduling is missed
                            if (chrt[count].In == false) {                  //Any task is not running, allocate current task
                                chrt[count].name = data.GetName();
                                chrt[count].In = true;
                                QTableWidgetItem* head = new QTableWidgetItem;      //set GanttChart
                                head->setBackground(brush);
                                head->setText(data.GetName());
                                ui->GanttChart->setItem(data.GetIndex(), count + 1, head);
                                break;
                            }
                            else {                                          //when any task is already allocated
                                count++;
                            }
                        }
                        else {                                              //when scheduling is missed
                            return 0;
                        }
                    }
                }
                n++;                                                        //next time
                count = peri * n;
            }
            itor.Next();                                                    //next task
        }
        return 1;
}

int MainWindow::SetAperiodic(Chart *chrt){                                   //scheduling of aperiodic tasks in background
    SortedIterator<Task> aitor(Aperiodic_List);
    Task adata;
    QBrush brush;
    brush = QColor(156,194,229);
    int count;
    QString a_name;
    int aperi, acom;
    adata = aitor.Next();
    while (aitor.NextNotNull()) {
        adata = aitor.GetCurrentNode().value;
        aperi = adata.GetPeriod();
        acom = adata.GetComputation();
        count = aperi;
        for (int i = 0; i < acom; i++) {                                    //for computation time
            while (1) {
                if (chrt[count].In == false) {                              //Any task is not running, allocate current task
                    chrt[count].name = adata.GetName();
                    chrt[count].In = true;
                    QTableWidgetItem* head = new QTableWidgetItem;
                    head->setBackground(brush);
                    head->setText(adata.GetName());
                    ui->GanttChart->setItem(adata.GetIndex(), count + 1, head);
                    break;
                }
                else {
                    count++;
                }
            }
        }
        average += count - aperi;                                           //caculate average delay time
        adata = aitor.Next();                                               //next aperiodic task
    }

    average = average / (float)A_length;

    return 1;
}

void MainWindow::SetPolling(Chart *chrt){                                   //scheduling of aperiodic tasks in polling server APS
    int count;
    QBrush brush;
    brush = QColor(156,194,229);
    int n = 1;
    int p_peri = PollingServer.GetPeriod();
    int p_com = PollingServer.GetComputation();
    count = p_peri * n;
    SortedIterator<Task> aitor(Aperiodic_List);
    Task adata;
    QString a_name;
    int arrival, acom;
    adata = aitor.Next();
    while (aitor.NextNotNull()) {
        arrival = adata.GetPeriod();
        acom = adata.GetComputation();
        a_name = adata.GetName();
        for (int i = 0; i < acom; i++) {                                    //for computation time
            arrival = arrival + i;
            while (count < arrival) {                                       //while aperiodic task arrive
                if (count % p_peri < p_com - 1) {                           //for capacity is not 1
                    count++;
                }
                else {
                    n++;
                    count = p_peri * n;
                }
            }
            chrt[count].name = a_name;                                      //allocate task because polling server task is periority task
            chrt[count].In = true;
            QTableWidgetItem* head = new QTableWidgetItem;                  //set GanttChart
            head->setBackground(brush);
            head->setText(adata.GetName());
            ui->GanttChart->setItem(adata.GetIndex(), count + 1, head);
            if (i == acom - 1) {                                            //when last
                average += count - adata.GetPeriod();
            }
            if (count % p_peri < p_com - 1) {                               //next polling server time
                count++;
            }
            else {
                n++;
                count = p_peri * n;
            }
        }
        adata = aitor.Next();
    }
    average = average / (float)A_length;                                    //calculate average
}

void MainWindow::on_BackgroundButton_clicked()                              //Background APS
{
    average = 0;
    Periodic_List.MakeEmpty();
    Aperiodic_List.MakeEmpty();
    AddPeriodic();
    AddAperiodic();
    Hyper = GetHyperPeriod();
    SetGantt();
    Chart *chrt = new Chart[Hyper];                                         //dynamic allocate for scheduling
    if(SetPeriodic(chrt)){
        SetAperiodic(chrt);
        ui->DelayTime->setText(QString::number(average));
    }else{                                                                  //when missed scheduling
        ui->DelayTime->setText("Failed Scheduling");
        ui->GanttChart->clear();
    }
}

void MainWindow::on_PollingButton_clicked()                                 //Polling server APS
{
    average = 0;
    Periodic_List.MakeEmpty();
    Aperiodic_List.MakeEmpty();
    AddPeriodic();
    AddAperiodic();
    Hyper = GetHyperPeriod();
    SetGantt();
    SetPollingServer();
    Chart *chrt = new Chart[Hyper];                                          //dynamic allocate for scheduling
    SetPolling(chrt);
    if(SetPeriodic(chrt)){
        ui->DelayTime->setText(QString::number(average));
    }else{
        ui->DelayTime->setText("Failed Scheduling");
        ui->GanttChart->clear();
    }
}
