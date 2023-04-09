#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QString"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Banker's Algorithm");
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    num_process = -1;
    num_instance = -1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Init(){                                                //banker 초기값 설정
    for(int i = 0; i <num_process; i++){
        for(int j = 0; j < num_instance; j++){
            banker.max[i][j] = 0;
            banker.allocation[i][j] = 0;
            banker.need[i][j] = 0;
        }
    }

    for(int i = 0; i < num_process; i++){
        banker.available[i] = 0;
        banker.work[i] = 0;
    }
}

void MainWindow::SetTable(){
    ui->Needtable->setRowCount(num_process);
    ui->Needtable->setColumnCount(num_instance);
    ui->Availabletable->setRowCount(1);
    ui->Availabletable->setColumnCount(num_instance);
    ui->Requesttable->setRowCount(1);
    ui->Requesttable->setColumnCount(num_instance + 1);

    for(int i = 0; i < num_process; i++){
        QTableWidgetItem* head = new QTableWidgetItem;
        head->setText(banker.process[i]);
        ui->Needtable->setVerticalHeaderItem(i, head);
    }
    for(int i = 0; i < num_instance; i++){
        QTableWidgetItem* head = new QTableWidgetItem;
        head->setText(banker.instance[i]);
        ui->Needtable->setHorizontalHeaderItem(i, head);
    }

    QTableWidgetItem* headavail = new QTableWidgetItem;
    headavail->setText("P");
    ui->Availabletable->setVerticalHeaderItem(0, headavail);

    for(int i = 0; i < num_instance; i++){
        QTableWidgetItem* head = new QTableWidgetItem;
        head->setText(banker.instance[i]);
        ui->Availabletable->setHorizontalHeaderItem(i, head);
    }

    QTableWidgetItem* headreq = new QTableWidgetItem;
    headreq->setText("Pin");
    ui->Requesttable->setHorizontalHeaderItem(0, headreq);
    for(int i = 0; i < num_instance; i++){
        QTableWidgetItem* head = new QTableWidgetItem;
        head->setText(banker.instance[i]);
        ui->Requesttable->setHorizontalHeaderItem(i + 1, head);
    }
}

void MainWindow::Setallocation(){                                           //banker 자료구조에 따른 allocation table 설정
    for(int i = 0; i < num_process; i++){
        for(int j = 0; j < num_instance; j++){
            QTableWidgetItem* content = new QTableWidgetItem;
            content->setText(QString::number(banker.allocation[i][j]));
            ui->Allocationtable->setItem(i, j, content);
        }
    }
}

void MainWindow::SetNeed(){                                                 //banker 자료구조에 따른 need table 설정
    for(int i = 0; i < num_process; i++){
        for(int j = 0; j < num_instance; j++){
            QTableWidgetItem* content = new QTableWidgetItem;
            content->setText(QString::number(banker.need[i][j]));
            ui->Needtable->setItem(i, j, content);
        }
    }
}

void MainWindow::SetAvailable(){                                            //banker 자료구조에 따른 available table 설정
    for(int i = 0; i < num_instance; i++){
        QTableWidgetItem* content = new QTableWidgetItem;
        content->setText(QString::number(banker.available[i]));
        ui->Availabletable->setItem(0, i, content);
    }
}

bool MainWindow::safety(){                                                  //safety algorithm
    bool check = true;
    int count = 0;

    for(int i = 0; i < num_process; i++){
        for(int j = 0; j < num_process; j++){
            if(banker.finish[j] == false){                              //이미 할당이 끝난 process인지 확인
                for(int k = 0; k < num_instance; k++){
                   if(banker.work[k] < banker.need[j][k]){
                       check = false;
                       break;
                   }
                }
                if(check == true){                                      //work보다 need가 작다면
                    banker.finish[j] = true;                            //할당 상태를 true 해주고
                    for(int k = 0; k < num_instance; k++){              //자원 반환
                        banker.work[k] += banker.allocation[j][k];
                    }
                    banker.request_flag[count] = banker.process[j];     //이름 추가
                    count++;
                    break;
                }else {
                    check = true;
                }
            }
        }
    }

    for(int i = 0; i < num_process; i++){                               //다음 사용을 위한 초기화
        banker.finish[i] = false;
    }

    if(count == num_process){                                           //safety 성공 여부 확인
        return true;
    }

    return false;
}





void MainWindow::on_SettingpushButton_clicked()
{
    QString temp1 = ui->ProcesslineEdit->text();
    num_process = temp1.toInt();
    if(num_process < 1 || num_process > 10){
        QMessageBox::question(this,"Error","Error: Process_Out_of_Range!",QMessageBox::Yes | QMessageBox::No);
        num_process = -1;
    }else {
        QString tex = ui->InstancelineEdit->text();
        while(tex.endsWith(' ') || tex.endsWith('\n')) tex.chop(1);             //Delete unnessesary part
        while(tex.startsWith(' ') || tex.startsWith('\n')) tex.remove(0, 1);
        QStringList inst = tex.split(' ');
        num_instance = inst.size();

        if(num_instance < 2 || num_instance > 5){
            QMessageBox::question(this,"Error","Error: Instance_Out_of_Range!",QMessageBox::Yes | QMessageBox::No);
            num_process = -1;
            num_instance= - 1;
        }else{
            ui->Maxtable->clear();
            ui->Allocationtable->clear();
            ui->Needtable->clear();
            ui->Availabletable->clear();
            ui->Requesttable->clear();
            ui->Safe_State_textBrowser->clear();

            ui->Maxtable->setRowCount(num_process);
            ui->Maxtable->setColumnCount(num_instance);
            for(int i = 0; i < num_process; i++){
                banker.process[i] = "P" + QString::number(i);
                QTableWidgetItem* head = new QTableWidgetItem;
                head->setText(banker.process[i]);
                ui->Maxtable->setVerticalHeaderItem(i, head);
            }
            for(int i = 0; i < num_instance; i++){
                banker.instance[i] = QChar::fromLatin1('A' + i);
                QTableWidgetItem* head = new QTableWidgetItem;
                head->setText(banker.instance[i]);
                ui->Maxtable->setHorizontalHeaderItem(i, head);
            }

            ui->Allocationtable->setRowCount(num_process);
            ui->Allocationtable->setColumnCount(num_instance);

            for(int i = 0; i < num_process; i++){
                QTableWidgetItem* head = new QTableWidgetItem;
                head->setText(banker.process[i]);
                ui->Allocationtable->setVerticalHeaderItem(i, head);
            }
            for(int i = 0; i < num_instance; i++){
                QTableWidgetItem* head = new QTableWidgetItem;
                head->setText(banker.instance[i]);
                ui->Allocationtable->setHorizontalHeaderItem(i, head);
            }

            for(int i = 0; i < num_instance; i++){
                banker.instMax[i] = inst.at(i).toInt();
            }

        }
    }



}

void MainWindow::on_InitialpushButton_clicked()
{
    Init();
    ui->Needtable->clear();
    ui->Availabletable->clear();
    ui->Requesttable->clear();
    ui->Safe_State_textBrowser->clear();
    for(int i = 0; i < num_process; i++){
        for(int j = 0; j < num_instance; j++){
            QTableWidgetItem* itemMax = new QTableWidgetItem;
            QTableWidgetItem* itemallo = new QTableWidgetItem;
            itemMax = ui->Maxtable->item(i, j);
            banker.max[i][j] = itemMax->text().toInt();
            itemallo = ui->Allocationtable->item(i, j);
            banker.allocation[i][j] = itemallo->text().toInt();
        }
    }
    SetTable();

    for(int i = 0; i < num_process; i++){
        for(int j = 0; j < num_instance; j++){
            banker.need[i][j] = banker.max[i][j] - banker.allocation[i][j];
            banker.available[j] += banker.allocation[i][j];
        }
    }

    for(int i = 0; i < num_instance; i++){
        banker.available[i] = banker.instMax[i] - banker.available[i];
    }
    SetNeed();
    SetAvailable();
}

void MainWindow::on_RequestpushButton_clicked()
{
    QString pro_name = ui->Requesttable->item(0, 0)->text();
    bool ok = true;
    int pro_num = -1;
    for(int i = 0; i < num_process; i++){
        if(banker.process[i] == pro_name){
            pro_num = i;
            break;
        }
    }

    if(pro_num != -1){
        for(int i = 0; i < num_instance; i++){
            banker.request[i] = ui->Requesttable->item(0, i + 1)->text().toInt();
        }
        for(int i = 0; i < num_instance; i++){
            if(banker.request[i] > banker.need[pro_num][i] || banker.request[i] > banker.available[i]){
                ok = false;
                break;
            }
        }

        if(ok == true){
            for(int i = 0; i < num_instance; i++){
                banker.allocation[pro_num][i] += banker.request[i];
                banker.available[i] = banker.available[i] - banker.request[i];
                banker.work[i] = banker.available[i];
                banker.need[pro_num][i] = banker.max[pro_num][i] - banker.allocation[pro_num][i];
            }

            if(safety()){
                Setallocation();
                SetNeed();
                SetAvailable();
                QString state;
                for(int i = 0; i < num_process; i++){
                    state += banker.request_flag[i] + " ";
                }
                ui->Safe_State_textBrowser->setText(state);


            }else{
                for(int i = 0; i < num_instance; i++){
                    banker.allocation[pro_num][i] -= banker.request[i];
                    banker.available[i] = banker.available[i] + banker.request[i];
                    banker.need[pro_num][i] = banker.max[pro_num][i] - banker.allocation[pro_num][i];
                }
                ui->Safe_State_textBrowser->setText("It is not safe state!");
            }

        }else{
            ui->Safe_State_textBrowser->setText("Can't allocate request!");
        }


    }else{
        ui->Safe_State_textBrowser->setText("Error: Check process name!");
    }
}
