#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cur_Memory_size = MAXMEMORY;
    Max_memory_size = MAXMEMORY;
    memState.push_back({0, 1000});
    result_idx = 9999999;
    resultview = "";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Coalescing(){
    int big;
    for(int i = 0; i < memState.size() - 1; i++){
        if(memState.at(i).at(0) == memState.at(i).at(1)){       //size가 0인 memory 공간 삭제
            memState.remove(i);
            i--;
            continue;
        }
        if(memState.at(i).at(1) == memState.at(i+1).at(0)){     //연속된 공간 삭제
            big = memState.at(i+1).at(1);
            memState.replace(i, {memState.at(i).at(0), big});
            memState.remove(i+1);
            i--;
        }
    }
}

void MainWindow::Rearrange(QVector<Memory> &d, int n){      //memory 시작 위치 설정, n은 memory 끝에 붙은 process 수
    int t = 0;
    for(int i = 0; i < d.size() - n; i++){
        Memory tem = d.at(i);
        tem.start = t;
        t += d.at(i).size;
        d.replace(i, tem);
    }
    t = Max_memory_size;
    for(int i = d.size() - 1; i > d.size() - n - 1; i--){
        Memory tem = d.at(i);
        tem.start = t - tem.size;
        t -= tem.size;
        d.replace(i, tem);
    }
}

int MainWindow::ComparewithList(QVector<Memory> c){             //memList와 비교해서 compaction 효율 확인
    int num = 0;
    for(int i = 0; i < c.size(); i++){
        for(int j = 0; j < c.size(); j++){
            if(c.at(i).index == memList.at(j).index){
                if(c.at(i).start != memList.at(j).start){
                    num += c.at(i).size;
                }
                continue;
            }
        }
    }
    return num;
}

void MainWindow::SetMemory(QVector<Memory> in, QVector<Memory> get, int n){     //BFS를 위한 code. n은 남은 할당해야하는 PROCESS수
    QVector<Memory> g = get;
    QVector<Memory> i = in;
    if(n == 0){
        for(int j = 0; j <= i.size(); j++){
            Rearrange(i, j);
            int num = ComparewithList(i);
            if(num < result_idx){
                result_idx = num;
                result = i;
            }
        }
    }else{
        for(int j = 0; j < n; j++){
            i.push_back(g.at(j));
            g.removeAt(j);
            SetMemory(i, g ,n - 1);
        }
    }
}

void MainWindow::Compact(){
    SortList();
    Coalescing();
    data = memList;
    SetMemory(temp, data, memList.size());
    memList = result;
    memState.clear();
    if(memList.at(0).start == 0){
        int i , start_mem, finish_mem;
        bool check = false;
        for(i = 0; i < memList.size() - 1; i++){
            if(memList.at(i).start + memList.at(i).size != memList.at(i + 1).start){
                start_mem = memList.at(i + 1).start + memList.at(i + 1).size;
                check = true;
                break;
            }
        }
        if(check == true){
            finish_mem = memList.at(i + 2).start;
            memState.push_back({start_mem, finish_mem});
        }else{
            start_mem = memList.last().start + memList.last().size;
            finish_mem = MAXMEMORY;
        }
        memState.push_back({start_mem, finish_mem});
    }else{              //모든 process가 memory끝에 붙었을 경우
        memState.push_back({0, memList.last().start});
    }
}

int MainWindow::Allocate(){
    Memory mem = memList.last();
    if(mem.size == 0){                  //Free request
        for(int i = 0; i < memList.size() - 1; i++){
            if(memList.at(i).index == mem.index){
                memState.push_back({memList.at(i).start, (memList.at(i).start + memList.at(i).size)});
                cur_Memory_size += memList.at(i).size;
                SortList();
                Coalescing();
                memList.removeLast();
                QString RequestInfo = "FREE REQUEST " + QString::number(memList.at(i).index) + " (" + QString::number(memList.at(i).size) + "K)\n";
                QString Free_add = "Freed at address " + QString::number(memList.at(i).start) + "K\n";
                QString StateInfo = QString::number(cur_Memory_size) + "K free, " + QString::number(memState.size())
                        + " block(s), average size = " + QString::number(cur_Memory_size / memState.size()) + "K\n\n";
                memList.remove(i);
                resultview.append(RequestInfo);
                resultview.append(Free_add);
                resultview.append(StateInfo);
                break;
            }
        }
    }else{
        SortList();
        Coalescing();
        int idx = -1;
        int mem_size = 999999;
        if(cur_Memory_size < memList.last().size){          //남은 memory 자체가 더 작을때
            QString RequestInfo = "REQUEST " + QString::number(memList.last().index) + " (" + QString::number(memList.last().size) + "K)\n";
            QString Info = "Cannot allocate Request: Not Enough size\n";
            QString StateInfo = QString::number(cur_Memory_size) + "K free, " + QString::number(memState.size())
                    + " block(s), average size = " + QString::number(cur_Memory_size / memState.size()) + "K\n\n";
            memList.removeLast();
            resultview.append(RequestInfo);
            resultview.append(Info);
            resultview.append(StateInfo);

            return 0;
        }
        for(int i = 0; i < memState.size(); i++){                       //best fit을 위한 code
            int temp = memState.at(i).at(1) - memState.at(i).at(0);
            if(temp >= memList.last().size){
                if(temp < mem_size){
                    mem_size = temp;
                    idx = i;
                }
            }
        }
        if(idx == -1){          //compact가 필요할 때
            Memory tem = memList.last();
            memList.removeLast();
            Compact();
            tem.start = memState.at(0).at(0);
            memState.replace(0, {memState.at(0).at(0) + tem.size, memState.at(0).at(1)});
            cur_Memory_size -= tem.size;
            memList.push_back(tem);
            SortList();
            Coalescing();

            QString RequestInfo = "REQUEST " + QString::number(memList.last().index) + " (" + QString::number(memList.last().size) + "K)\n";
            QString Info = "Allocate at address " + QString::number(memList.last().start) + "k\n";
            QString StateInfo = QString::number(cur_Memory_size) + "K free, " + QString::number(memState.size())
                    + " block(s), average size = " + QString::number(cur_Memory_size / memState.size()) + "K\n\n";
            resultview.append(RequestInfo);
            resultview.append(Info);
            resultview.append(StateInfo);
        }else {                     //compaction이 필요없이 할당이 가능할 때
            Memory m = memList.last();
            m.start = memState.at(idx).at(0);
            memList.replace(memList.size() - 1, m);
            memState.replace(idx, {m.start + m.size, memState.at(idx).at(1)});
            cur_Memory_size -= m.size;
            SortList();
            Coalescing();
            QString RequestInfo = "REQUEST " + QString::number(memList.last().index) + " (" + QString::number(memList.last().size) + "K)\n";
            QString Info = "Allocate at address " + QString::number(memList.last().start) + "k\n";
            QString StateInfo = QString::number(cur_Memory_size) + "K free, " + QString::number(memState.size())
                    + " block(s), average size = " + QString::number(cur_Memory_size / memState.size()) + "K\n\n";
            resultview.append(RequestInfo);
            resultview.append(Info);
            resultview.append(StateInfo);
        }

    }
    return 1;
}

void MainWindow::SortList(){
    for(int i = 0; i < memState.size() - 1; i++){
        for(int j = 0; j < memState.size() - 1; j++){
            if(memState.at(j).at(0) > memState.at(j+1).at(0)){
                memState.swapItemsAt(j, j+1);
            }
        }
    }
}

void MainWindow::on_Input_pushButton_clicked()
{
    QString tex = ui->Input_plainTextEdit->toPlainText();
    while(tex.endsWith(' ') || tex.endsWith('\n')) tex.chop(1);             //Delete unnessesary part
    while(tex.startsWith(' ') || tex.startsWith('\n')) tex.remove(0, 1);
    if(!tex.isEmpty()){
        QStringList phara = tex.split(' ');
        if(phara.size()%2 == 1){
            QMessageBox::warning(this,"Invaild input", "Input format is not matched!\n Check format again", QMessageBox::Ok);
        }else{
            for(int i = 0; i < phara.size(); i+=2){
                Memory temp;
                temp.index = phara.at(i).toInt();
                temp.size = phara.at(i + 1).toInt();

                memList.push_back(temp);
                Allocate();
            }
        }
    }else{
        QMessageBox::warning(this,"Invaild input", "Input format is not matched!\n Check format again", QMessageBox::Ok);
    }

    ui->Output_textBrowser->setPlainText(resultview);
}

void MainWindow::on_size_pushButton_clicked()
{
    int size = ui->size_plainTextEdit->toPlainText().toInt();
   if(size > MAXMEMORY){
        QMessageBox::warning(this,"Error", "Error: Size is smaller than 1000K", QMessageBox::Ok);
   }else{
        Max_memory_size = size;
        cur_Memory_size = Max_memory_size;
        ui->Info_label->setText("Memory set Success!");
   }
}
