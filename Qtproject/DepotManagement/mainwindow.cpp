#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QStandardItemModel"
#include "QDebug"
#include "QFileDialog"
#include "QImage"
#include "QFile"
#include "QFileDevice"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    searchwin = new SearchWin(this);
    picwin = new PictureWin(this);
    count = 1;
    ui->Item_tabWidget->setCurrentIndex(0);
    ui->Storage_tabWidget->setCurrentIndex(0);
    setFixedSize(1093, 811);
    ui->Item_Add_Date_plainTextEdit->setPlaceholderText("ex) 20151010");
    ui->Food_Add_Date_plainTextEdit->setPlaceholderText("ex) 20200630");
    ui->Food_Add_DueDate_plainTextEdit->setPlaceholderText("ex) 20200720");
//    connect(this, SIGNAL(SendPicturePath(QString)), picwin, SLOT(GetPicturePathFromMain(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSearch_triggered()                    //검색창을 MainWindow옆에 띄움
{
    delete searchwin;
    searchwin = new SearchWin(this);
    searchwin->show();

    int x = this->x() + this->width();
    int y = this->y() + (this->height() - searchwin->height());

    searchwin->move(x, y);                                      //검색창 위치조절
}

bool CheckDate(int year, int month, int day) {					//날짜의 유효성 확인
    if ((month % 2 == 1)) //odd month
    {
        if (month <= 7){
            if (day <= 0 || day > 31) {
                return false;
            }
        }
        else{ // month > 7
            if (day <= 0 || day > 30) {
                return false;
            }
        }
    }
    else //even month
    {
        if (month <= 6) {
            if (month == 2)
            {
                if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) // leap year
                {
                    if (day <= 0 || day > 30) return false;
                }
                else if (day <= 0 || day > 28) return false;

            }
            if (day <= 0 || day > 30) return false;
        }
        else { // month > 6

            if (day <= 0 || day > 31) return false;
        }
    }
    return true;
}

void MainWindow::on_Item_Add_pushButton_clicked()
{
    item = new Object();
    QString name = ui->Item_Add_Name_plainTextEdit->toPlainText();
    QString type = ui->Item_Add_type_plainTextEdit->toPlainText();
    int num = ui->Item_Add_Num_spinBox->text().toInt();
    int BuyDate = ui->Item_Add_Date_plainTextEdit->toPlainText().toInt();
    if(!CheckDate(BuyDate / 10000, BuyDate % 10000 / 100, BuyDate % 100) || !(BuyDate > 10000 && BuyDate < 99999999)){
        QMessageBox::warning(this, "Input Error", "Error: Invalid Date");
        return ;
    }
    int spend;
    if(ui->Item_Add_Yes_radioButton->isChecked()){
        spend = 1;
    }else{
        spend = 0;
    }
    int sto = ui->Item_Add_Storage_plainTextEdit->toPlainText().toInt();
    int flo = ui->Item_Add_Floor_plainTextEdit->toPlainText().toInt();
    time_t lab_time;
    time(&lab_time);
    tm* tim = gmtime(&lab_time);

    int label;
    label = (tim->tm_min + 1) * (tim->tm_sec + 1) * ((MasterList.GetLength() + 1) % 1000);      //item label값 설정(현재 시각으로)
    item->SetLabel(label);
    item->SetName(name.toStdString());
    item->SetType(type.toStdString());
    item->SetVolume(num);
    item->SetBuyDate(BuyDate);
    item->SetAttribute(spend);
    item->SetStorageID(sto);
    item->SetFloorID(flo);
    item->SetPicture(ui->Item_Add_Picture_plainTextEdit->toPlainText().toStdString());
    if(sto == 0 || flo == 0){                                           //날짜가 입력이 되지 않았으면 TempList에 추가가 됨
        if(TempList.Enqueue(item)){
            ui->Main_Info_label->setText("Add to tempList!");
        }else{
            QMessageBox::warning(this, "Insert Error", "Error: Cannot Add Object to TempList");
        }
        return ;
    }
    StorageType st;
    st.SetLabel(sto);
    FloorType fl;
    fl.SetLabel(flo);
    SimpleItemType simple(item);
    if(StorageList.Get(st)){                                        //MasterList와 SimpleList 추가 부분
        if(st.GetFloor(fl)){
            if(fl.AddItem(simple)){
                if(MasterList.Insert(item)){
                    st.UpdateFloor(fl);
                    StorageList.Replace(st);
                    ui->Main_Info_label->setText("Assign label " + QString::number(label));
                    count++;
                }else{
                    ui->Main_Info_label->setText("Add fail!");
                }
            }else{
                QMessageBox::warning(this, "Insert Error", "Error: Cannot Add Object! Floor is Full");
            }
        }else{
            QMessageBox::warning(this, "Retrieve Error", "Error: Cannot Retrieve floor" + QString::number(flo));
        }
    }else{
        QMessageBox::warning(this, "Retrieve Error", "Error: Cannot Retrieve Storage" + QString::number(sto));
    }
}

void MainWindow::on_Display_All_pushButton_clicked()                //MasterList의 모든 Item을 TreeView에 출력
{
    ui->treeView->reset();
    bool finish = false;
    ItemType* data;
    MasterList.ResetTree();
    MasterList.GetNextItem(data, finish);
    int num = 1;
    QStandardItemModel * model = new QStandardItemModel();
    QString dispstring;
    while(finish != true){
        dispstring = QString::fromStdString(data->DisplayItem());
        QStringList phara = dispstring.split("\n");
        QStandardItem *obj = new QStandardItem(QString::number(num));
        model->appendRow(obj);
        for(int i = 0; i <phara.size(); i++){
            obj->appendRow(new QStandardItem(phara[i]));
        }

        ui->treeView->setModel(model);

        MasterList.GetNextItem(data, finish);
        num++;
    }

    QString header_title = QString::number(count - 1) + QString::fromLocal8Bit("개의 물건 존재");
    model->setHeaderData(0, Qt::Horizontal, header_title);
    ui->treeView->expandAll();
}

void MainWindow::on_Clear_pushButton_clicked()
{
    ui->treeView->reset();
}

void MainWindow::on_Storage_Add_pushButton_clicked()
{
    QString type = ui->Storage_Add_Type_plainTextEdit->toPlainText();
    int floor  = ui->Storage_Add_Floor_plainTextEdit->toPlainText().toInt();
    StorageType sto(floor);
    sto.SetType(type.toStdString());
    int label = ui->Storage_Add_Label_plainTextEdit->toPlainText().toInt();
    sto.SetLabel(label);
    if(StorageList.Add(sto)){
        ui->Main_Info_label->setText("Assign Label is " + QString::number(label));
    }else{
        QMessageBox::warning(this, "Insert Error", "Error: Cannot Add Storage! Check Label");
    }
}

void MainWindow::on_Storage_Update_Load_pushButton_clicked()
{
    int label = ui->Storage_Update_Label_plainTextEdit->toPlainText().toInt();
    StorageType temp;
    temp.SetLabel(label);
    if(StorageList.Get(temp)){
        ui->Storage_Update_Type_plainTextEdit->setPlainText(QString::fromStdString(temp.GetType()));
        ui->Storage_Update_Floor_textBrowser->setText(QString::number(temp.GetFloor()));
    }else{
        QMessageBox::warning(this, "Load Error", "Error: Cannot Retrieve Storage! Check Label");
    }
}


void MainWindow::on_Storage_Update_pushButton_clicked()
{
    int label = ui->Storage_Update_Label_plainTextEdit->toPlainText().toInt();
    StorageType temp;
    temp.SetLabel(label);
    if(StorageList.Get(temp)){
        temp.SetType(ui->Storage_Update_Type_plainTextEdit->toPlainText().toStdString());
        StorageList.Replace(temp);
    }else{
        QMessageBox::warning(this, "Load Error", "Error: Cannot Retrieve Storage! Check Label");
    }
}

void MainWindow::on_Storage_Delete_pushButton_clicked()
{
    int label = ui->Storage_Delete_Label_plainTextEdit->toPlainText().toInt();
    StorageType stotemp;
    FloorType flotemp;
    SimpleItemType simtemp;
    stotemp.SetLabel(label);
    if(StorageList.Get(stotemp)){
        int point;
        stotemp.Reset();
        point = stotemp.GetNextFloor(flotemp);
        while(point != -1){
            int p;
            flotemp.Reset();
            p = flotemp.GetNextSimpleItem(simtemp);
            while(p != -1){
                int la = simtemp.GetLabel();
                item->SetLabel(la);
                MasterList.Delete(item);
                p = flotemp.GetNextSimpleItem(simtemp);
            }
            point = stotemp.GetNextFloor(flotemp);
        }
        StorageList.Delete(stotemp);
        ui->Main_Info_label->setText("Delete Success");
    }else{
        QMessageBox::warning(this, "Delete Error", "Error: Cannot Delete Storage! Check Label");
    }
}

void MainWindow::on_Floor_Add_pushButton_clicked()
{
    StorageType temp;
    FloorType flotemp;
    temp.SetLabel(ui->Floor_Add_StorageLabel_plainTextEdit->toPlainText().toInt());
    if(StorageList.Get(temp)){
        flotemp.SetType(ui->Floor_Add_Type_plainTextEdit->toPlainText().toStdString());
        flotemp.SetLabel(temp.GetFloor() + 1);
        temp.AddFloor(flotemp);
        StorageList.Replace(temp);
    }else{
        QMessageBox::warning(this, "Add Error", "Error: Cannot Add Floor");
    }
}

void MainWindow::on_Floor_Update_Load_pushButton_clicked()
{
    StorageType stotemp;
    FloorType flotemp;
    stotemp.SetLabel(ui->Floor_Update_StorageLabel_plainTextEdit->toPlainText().toInt());
    if(StorageList.Get(stotemp)){
        flotemp.SetLabel(ui->Floor_Update_Floor_plainTextEdit->toPlainText().toInt());
        if(stotemp.GetFloor(flotemp)){
            ui->Floor_Update_Type_plainTextEdit->setPlainText(QString::fromStdString(flotemp.GetType()));
        }else{
            QMessageBox::warning(this, "Load Error", "Error: Cannot Load Floor");
        }
    }else{
        QMessageBox::warning(this, "Load Error", "Error: Cannot Load Storage! Check Label");
    }
}

void MainWindow::on_Floor_Update_pushButton_clicked()
{
    StorageType stotemp;
    FloorType flotemp;
    stotemp.SetLabel(ui->Floor_Update_StorageLabel_plainTextEdit->toPlainText().toInt());
    if(StorageList.Get(stotemp)){
        flotemp.SetLabel(ui->Floor_Update_Floor_plainTextEdit->toPlainText().toInt());
        if(stotemp.GetFloor(flotemp)){
            flotemp.SetType(ui->Floor_Update_Type_plainTextEdit->toPlainText().toStdString());
            stotemp.UpdateFloor(flotemp);
            StorageList.Replace(stotemp);
            ui->Main_Info_label->setText("Update Success");
        }else{
            QMessageBox::warning(this, "Load Error", "Error: Cannot Load Floor");
        }
    }else{
        QMessageBox::warning(this, "Load Error", "Error: Cannot Load Storage! Check Label");
    }
}

void MainWindow::on_Floor_Delete_pushButton_clicked()
{
    int stolabel = ui->Floor_Delete_StorageLabel_plainTextEdit->toPlainText().toInt();
    int flolabel = ui->Floor_Delete_Floor_plainTextEdit->toPlainText().toInt();
    StorageType stotemp;
    FloorType flotemp;
    SimpleItemType simtemp;
    stotemp.SetLabel(stolabel);
    if(StorageList.Get(stotemp)){
        flotemp.SetLabel(flolabel);
        if(stotemp.GetFloor(flotemp)){
            flotemp.Reset();
            int point = flotemp.GetNextSimpleItem(simtemp);
            while(point != -1){
                item->SetLabel(simtemp.GetLabel());
                MasterList.Delete(item);
                point = flotemp.GetNextSimpleItem(simtemp);
            }
            stotemp.DeleteFloor(flotemp);
            StorageList.Replace(stotemp);
            ui->Main_Info_label->setText("Delete Success");
        }else{
            QMessageBox::warning(this, "Delete Error", "Error: Cannot Delete Floor! Check Label");
        }
    }else{
        QMessageBox::warning(this, "Delete Error", "Error: Cannot Load Storage! Check Label");
    }
}

void MainWindow::on_Food_Add_pushButton_clicked()
{
    item = new Food();
    QString name = ui->Food_Add_Name_plainTextEdit->toPlainText();
    QString type = ui->Food_Add_Type_plainTextEdit->toPlainText();
    int num = ui->Food_Add_Num_spinBox->text().toInt();
    int BuyDate = ui->Food_Add_Date_plainTextEdit->toPlainText().toInt();
    if(!CheckDate(BuyDate / 10000, BuyDate % 10000 / 100, BuyDate % 100) || !(BuyDate > 10000 && BuyDate < 99999999)){
        QMessageBox::warning(this, "Input Error", "Error: Invalid Date");
        return ;
    }
    int Duedate = ui->Food_Add_DueDate_plainTextEdit->toPlainText().toInt();
    if(!CheckDate(Duedate / 10000, Duedate % 10000 / 100, Duedate % 100) || !(Duedate > 10000 && Duedate < 99999999)){
        QMessageBox::warning(this, "Input Error", "Error: Invalid Date");
        return ;
    }
    int sto = ui->Food_Add_Storage_plainTextEdit->toPlainText().toInt();
    int flo = ui->Food_Add_Floor_plainTextEdit->toPlainText().toInt();

    time_t lab_time;
    time(&lab_time);
    tm* tim = gmtime(&lab_time);

    int label;
    label = (tim->tm_min + 1) * (tim->tm_sec + 1) * ((MasterList.GetLength() + 1) % 1000);          //label 설정

    item->SetLabel(label);
    item->SetName(name.toStdString());
    item->SetType(type.toStdString());
    item->SetVolume(num);
    item->SetBuyDate(BuyDate);
    item->SetAttribute(Duedate);
    item->SetStorageID(sto);
    item->SetFloorID(flo);
    item->SetPicture(ui->Food_Add_Picture_plainTextEdit->toPlainText().toStdString());
    if(sto == 0 || flo == 0){
        if(TempList.Enqueue(item)){
            ui->Main_Info_label->setText("Add to tempList!");
        }else{
            QMessageBox::warning(this, "Insert Error", "Error: Cannot Add Food to TempList");
        }
        return ;
    }
    StorageType st;
    st.SetLabel(sto);
    FloorType fl;
    fl.SetLabel(flo);
    SimpleItemType simple(item);
    if(StorageList.Get(st)){
        if(st.GetFloor(fl)){
            if(fl.AddItem(simple)){
                if(MasterList.Insert(item)){
                    st.UpdateFloor(fl);
                    StorageList.Replace(st);
                    ui->Main_Info_label->setText("Assign Label " + QString::number(label));
                    count++;
                }else{
                    ui->Main_Info_label->setText("Add fail!");
                }
            }else{
                QMessageBox::warning(this, "Insert Error", "Error: Cannot Add Object! Floor is Full");
            }
        }else{
            QMessageBox::warning(this, "Retrieve Error", "Error: Cannot Retrieve floor" + QString::number(flo));
        }
    }else{
        QMessageBox::warning(this, "Retrieve Error", "Error: Cannot Retrieve Storage" + QString::number(sto));
    }
}

void MainWindow::on_Item_Delete_pushButton_clicked()
{
    int label = ui->Item_Delete_plainTextEdit->toPlainText().toInt();
    item->SetLabel(label);
    MasterList.Retrieve(item);
    int flo = item->GetFloorID();
    int sto = item->GetStorageID();
    StorageType stotemp;
    FloorType flotemp;
    SimpleItemType simtemp;
    simtemp.SetLabel(label);
    stotemp.SetLabel(sto);
    if(MasterList.Delete(item)){
        if(StorageList.Get(stotemp)){
            flotemp.SetLabel(flo);
            if(stotemp.GetFloor(flotemp)){
                if(flotemp.DeleteItem(simtemp)){
                    ui->Main_Info_label->setText("Delete Success!");
                    count--;
                }else{
                    QMessageBox::warning(this, "Delete Error", "Error: Cannot Retrieve SimpleItem");
                }
            }else{
                QMessageBox::warning(this, "Delete Error", "Error: Cannot Retrieve Floor");
            }
        }else{
            QMessageBox::warning(this, "Delete Error", "Error: Cannot Retrieve Storage");
        }
    }else{
        QMessageBox::warning(this, "Delete Error", "Error: Cannot Delete Item");
    }
}

void MainWindow::on_Item_Add_Picture_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("사진 경로 탐색"), "C:\\", "Files(*.png || *.jpg)");
    ui->Item_Add_Picture_plainTextEdit->setPlainText(filename);
}

void MainWindow::on_Food_Add_Picture_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("사진 경로 탐색"), "C:\\", "Files(*.png || *.jpg)");
    ui->Food_Add_Picture_plainTextEdit->setPlainText(filename);
}

void MainWindow::on_Item_Update_pushButton_clicked()
{
    int label = ui->Item_Update_Label_plainTextEdit->toPlainText().toInt();
    item->SetLabel(label);
    if(MasterList.Retrieve(item)){
        item->SetName(ui->Item_Update_Name_plainTextEdit->toPlainText().toStdString());
        item->SetType(ui->Item_Update_Type_plainTextEdit->toPlainText().toStdString());
        item->SetVolume(ui->Item_Update_Num_spinBox->value());
        int BuyDate = ui->Item_Update_Date_plainTextEdit->toPlainText().toInt();
        item->SetBuyDate(BuyDate);
        if(!CheckDate(BuyDate / 10000, BuyDate % 10000 / 100, BuyDate % 100) || !(BuyDate > 10000 && BuyDate < 99999999)){
            QMessageBox::warning(this, "Input Error", "Error: Invalid Date");
            return ;
        }
        item->SetPicture(ui->Item_Update_Picture_plainTextEdit->toPlainText().toStdString());
        if(item->GetKey() == 0){
            if(ui->Item_Update_Yes_radioButton->isChecked()){
                item->SetAttribute(1);
            }else{
                item->SetAttribute(0);
            }
        }else{
            item->SetAttribute(ui->Item_Update_DueDate_plainTextEdit->toPlainText().toInt());
        }
        StorageType stotemp;
        stotemp.SetLabel(item->GetStorageID());
        FloorType flotemp;
        SimpleItemType simtemp(item);
        if(StorageList.Get(stotemp)){
            flotemp.SetLabel(item->GetFloorID());
            if(stotemp.GetFloor(flotemp)){
                if(flotemp.UpdateItem(simtemp)){
                    MasterList.Replace(item);
                    stotemp.UpdateFloor(flotemp);
                    StorageList.Replace(stotemp);
                    ui->Main_Info_label->setText("Update Success!");
                }else{
                    QMessageBox::warning(this, "Update Error", "Error: Cannot Retrieve SimpleItem");
                }
            }else{
                QMessageBox::warning(this, "Update Error", "Error: Cannot Retrieve Floor");
            }
        }else{
            QMessageBox::warning(this, "Update Error", "Error: Cannot Retrieve Storage");
        }
    }else{
        QMessageBox::warning(this, "Update Error", "Error: Cannot Retrieve Item");
    }
}


void MainWindow::on_Item_Update_Load_pushButton_clicked()
{
    int label = ui->Item_Update_Label_plainTextEdit->toPlainText().toInt();
    item->SetLabel(label);
    if(MasterList.Retrieve(item)){
        ui->Item_Update_Name_plainTextEdit->setPlainText(QString::fromStdString(item->GetName()));
        ui->Item_Update_Type_plainTextEdit->setPlainText(QString::fromStdString(item->GetType()));
        ui->Item_Update_Num_spinBox->setValue(item->GetVolume());
        ui->Item_Update_Date_plainTextEdit->setPlainText(QString::number(item->GetBuyDate()));
        ui->Item_Update_Picture_plainTextEdit->setPlainText(QString::fromStdString(item->GetPicture()));
        if(item->GetKey() == 0){
            if(item->GetAttribute() == 1){
                ui->Item_Update_Yes_radioButton->setChecked(true);
            }else{
                ui->Item_Update_No_radioButton->setChecked(true);
            }
        }else{
            ui->Item_Update_DueDate_plainTextEdit->setPlainText(QString::number(item->GetAttribute()));
        }

    }else{
        QMessageBox::warning(this, "Load Error", "Error: Cannot Load Item! Check Label");
    }

}


void MainWindow::on_Item_Update_Picture_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("사진 경로 탐색"), "C:\\", "Files(*.png || *.jpg)");
    ui->Item_Update_Picture_plainTextEdit->setPlainText(filename);
}

void MainWindow::on_actionHeirarchical_triggered()
{
    ui->treeView->reset();
    SimpleItemType data;
    QStandardItemModel * model = new QStandardItemModel();
    QString dispstring;
    StorageType stotemp;
    DoublyIterator<StorageType> iter(StorageList);
    FloorType flotemp;
    stotemp = iter.Next();

    while(iter.NextNotNull()){
        dispstring = QString::fromStdString(stotemp.Display());
        QStandardItem *st = new QStandardItem("Storage");
        QStandardItem *stitem = new QStandardItem(QString::fromStdString(stotemp.Display()));
        QStandardItem *stchild = new QStandardItem(QString::number(stotemp.GetFloor()) + " Floor Exist");
        model->appendRow(st);
        st->appendRow(stitem);
        st->appendRow(stchild);
        stotemp.Reset();
        int point = stotemp.GetNextFloor(flotemp);
        while(point != -1){
            QStandardItem *flitem = new QStandardItem(QString::number(flotemp.GetLength()) + " Item Exist");
            QStandardItem *fl = new QStandardItem(QString::fromStdString(flotemp.Display()));
            flotemp.Reset();
            int p = flotemp.GetNextSimpleItem(data);
            while(p != -1){
                QStandardItem *sim = new QStandardItem(QString::fromStdString(data.DisplayItem()));
                flitem->appendRow(sim);
                p = flotemp.GetNextSimpleItem(data);
            }
            stchild->appendRow(fl);
            stchild->appendRow(flitem);
            point = stotemp.GetNextFloor(flotemp);
        }
        stotemp = iter.Next();
    }

    ui->treeView->setModel(model);

    ui->treeView->setWordWrap(true);

    QString header_title = QString::number(StorageList.GetLength()) + QString::fromLocal8Bit("개의 Storage 존재");
    model->setHeaderData(0, Qt::Horizontal, header_title);
    ui->treeView->setHeaderHidden(true);
    ui->treeView->expandToDepth(0);
}

void MainWindow::on_actionTemp_List_triggered()
{
    ui->treeView->reset();
    QStandardItemModel * model = new QStandardItemModel();
    LinkedQueueIterator<ItemType> iter(TempList);
    item = iter.Next();
    int num = 1;
    while(iter.NextNotNull()){
        QStandardItem* obj = new QStandardItem(QString::number(num));
        model->appendRow(obj);
        obj->appendRow(new QStandardItem(QString::fromStdString(item->DisplayItem())));
        item = iter.Next();
    }
    QString header_title = QString::number(TempList.GetSize()) + QString::fromLocal8Bit("개의 Object 존재");
    model->setHeaderData(0, Qt::Horizontal, header_title);
    ui->treeView->setModel(model);
    ui->treeView->expandAll();
}

void MainWindow::on_actionTemp_Dequeue_triggered()          //TempList로 부터 Dequeue 후, 맞는 ITemType에 따라 Load
{
    if(TempList.Dequeue(item)){
        if(item->GetKey()){
            ui->Item_tabWidget->setCurrentIndex(1);
            ui->Food_Add_Name_plainTextEdit->setPlainText(QString::fromStdString(item->GetName()));
            ui->Food_Add_Type_plainTextEdit->setPlainText(QString::fromStdString(item->GetType()));
            ui->Food_Add_Num_spinBox->setValue(item->GetVolume());
            ui->Food_Add_Date_plainTextEdit->setPlainText(QString::number(item->GetBuyDate()));
            ui->Food_Add_DueDate_plainTextEdit->setPlainText(QString::number(item->GetAttribute()));
            ui->Food_Add_Picture_plainTextEdit->setPlainText(QString::fromStdString(item->GetPicture()));
        }else{
            ui->Item_tabWidget->setCurrentIndex(0);
            ui->Item_Add_Name_plainTextEdit->setPlainText(QString::fromStdString(item->GetName()));
            ui->Item_Add_type_plainTextEdit->setPlainText(QString::fromStdString(item->GetType()));
            ui->Item_Add_Num_spinBox->setValue(item->GetVolume());
            ui->Item_Add_Date_plainTextEdit->setPlainText(QString::number(item->GetBuyDate()));
            if(item->GetAttribute()){
                ui->Item_Add_Yes_radioButton->setChecked(true);
            }else{
                ui->Item_Add_No_radioButton->setChecked(true);
            }
            ui->Item_Add_Picture_plainTextEdit->setPlainText(QString::fromStdString(item->GetPicture()));
        }
    }else{
        QMessageBox::warning(this, "Load Error", "Error: Cannot Load Item! TempList is Empty");
    }
}

void MainWindow::GetObjectLabel(int label){
    ui->treeView->reset();
    ItemType* data = new Object();
    data->SetLabel(label);
    QStandardItemModel* model = new QStandardItemModel();
    if(MasterList.Retrieve(data)){
        model->appendRow(new QStandardItem(QString::fromStdString(data->DisplayItem())));
        RecentList.Enqueue(data);
    }else{
        QMessageBox::warning(this, "Search Error", "Error: Cannot Search Item! Invaild Label");
    }
    ui->treeView->setModel(model);
    ui->treeView->setHeaderHidden(true);
}

void MainWindow::GetObjectName(QString name){
    MasterList.ResetTree();
    bool finished = false;
    ItemType* data = new Object;
    MasterList.GetNextItem(data, finished);
    int count = 1;
    QStandardItemModel* model = new QStandardItemModel();
    while(finished != true){
        if(data->GetName() == name.toStdString()){
            QStandardItem* obj = new QStandardItem(QString::number(count++));
            obj->appendRow(new QStandardItem(QString::fromStdString(data->DisplayItem())));
            model->appendRow(obj);
            RecentList.Enqueue(data);
        }
        MasterList.GetNextItem(data, finished);
    }
    if(count != 1){
        QString header_title = QString::number(count - 1) + QString::fromLocal8Bit("개의 Object를 검색");
        model->setHeaderData(0, Qt::Horizontal, header_title);
    }else{
        model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("일치하는 물건이 없음"));
    }
    ui->treeView->setModel(model);
    ui->treeView->expandAll();
}

void MainWindow::GetObjectType(QString type){
    MasterList.ResetTree();
    bool finished = false;
    ItemType* data = new Object;
    MasterList.GetNextItem(data, finished);
    int count = 1;
    QStandardItemModel* model = new QStandardItemModel();
    while(finished != true){
        if(data->GetType() == type.toStdString()){
            QStandardItem* obj = new QStandardItem(QString::number(count++));
            obj->appendRow(new QStandardItem(QString::fromStdString(data->DisplayItem())));
            model->appendRow(obj);
            RecentList.Enqueue(data);
        }
        MasterList.GetNextItem(data, finished);
    }
    if(count != 1){
        QString header_title = QString::number(count - 1) + QString::fromLocal8Bit("개의 Object를 검색");
        model->setHeaderData(0, Qt::Horizontal, header_title);
    }else{
        model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("일치하는 물건이 없음"));
    }
    ui->treeView->setModel(model);
    ui->treeView->expandAll();
}

void MainWindow::GetObjectDate(int from, int to){
    MasterList.ResetTree();
    bool finished = false;
    ItemType* data = new Object;
    MasterList.GetNextItem(data, finished);
    int count = 1;
    QStandardItemModel* model = new QStandardItemModel();
    while(finished != true){
        if(data->GetBuyDate() >= from && data->GetBuyDate() <= to){
            QStandardItem* obj = new QStandardItem(QString::number(count++));
            obj->appendRow(new QStandardItem(QString::fromStdString(data->DisplayItem())));
            model->appendRow(obj);
            RecentList.Enqueue(data);
        }
        MasterList.GetNextItem(data, finished);
    }
    if(count != 1){
        QString header_title = QString::number(count - 1) + QString::fromLocal8Bit("개의 Object를 검색");
        model->setHeaderData(0, Qt::Horizontal, header_title);
    }else{
        model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("일치하는 물건이 없음"));
    }
    ui->treeView->setModel(model);
    ui->treeView->expandAll();
}
void MainWindow::GetObjectDueDate(int date){
    MasterList.ResetTree();
    bool finished = false;
    ItemType* data = new Object;
    MasterList.GetNextItem(data, finished);
    int count = 1;
    QStandardItemModel* model = new QStandardItemModel();
    while(finished != true){
        if(data->GetKey() == 1){
            if(data->GetAttribute() <= date){
                QStandardItem* obj = new QStandardItem(QString::number(count++));
                obj->appendRow(new QStandardItem(QString::fromStdString(data->DisplayItem())));
                model->appendRow(obj);
            }
        }
        MasterList.GetNextItem(data, finished);
    }
    if(count != 1){
        QString header_title = QString::number(count - 1) + QString::fromLocal8Bit("개의 Object를 검색");
        model->setHeaderData(0, Qt::Horizontal, header_title);
    }else{
        QMessageBox::warning(this, "Search Error", "Error: Cannot Search Item! Invaild Name");
    }
    ui->treeView->setModel(model);
    ui->treeView->expandAll();
}

void MainWindow::GetStorageLabel(int label){
    ui->treeView->reset();
    StorageType stotemp;
    FloorType flotemp;
    SimpleItemType data;
    stotemp.SetLabel(label);
    QStandardItemModel* model = new QStandardItemModel();
    if(StorageList.Get(stotemp)){
        QStandardItem *stitem = new QStandardItem(QString::fromStdString(stotemp.Display()));
        QStandardItem *stchild = new QStandardItem(QString::number(stotemp.GetFloor()) + " Floor Exist");
        model->appendRow(stitem);
        model->appendRow(stchild);
        int point = stotemp.GetNextFloor(flotemp);
        while(point != -1){
            QStandardItem *flitem = new QStandardItem(QString::number(flotemp.GetLength()) + " Item Exist");
            QStandardItem *fl = new QStandardItem(QString::fromStdString(flotemp.Display()));
            flotemp.Reset();
            int p = flotemp.GetNextSimpleItem(data);
            while(p != -1){
                QStandardItem *sim = new QStandardItem(QString::fromStdString(data.DisplayItem()));
                flitem->appendRow(sim);
                p = flotemp.GetNextSimpleItem(data);
            }
            stchild->appendRow(fl);
            stchild->appendRow(flitem);
            point = stotemp.GetNextFloor(flotemp);
        }
        model->setHeaderData(0, Qt::Horizontal, "Storage");
    }else{
        QMessageBox::warning(this, "Search Error", "Error: Cannot Search Storage! Invaild Label");
    }
    ui->treeView->setModel(model);
    ui->treeView->expandToDepth(1);

}
void MainWindow::GetFloorLabel(int sto, int flo){                   //검색할 날짜 범위를 받아서 검색
    ui->treeView->reset();
    StorageType stotemp;
    FloorType flotemp;
    flotemp.SetLabel(flo);
    SimpleItemType data;
    stotemp.SetLabel(sto);
    QStandardItemModel* model = new QStandardItemModel();
    if(StorageList.Get(stotemp)){
        if(stotemp.GetFloor(flotemp)){
            QStandardItem *stitem = new QStandardItem(QString::fromStdString(stotemp.Display()));
            QStandardItem *stchild = new QStandardItem(QString::number(flo) + "th Floor");
            model->appendRow(stitem);
            model->appendRow(stchild);
            QStandardItem *flitem = new QStandardItem(QString::number(flotemp.GetLength()) + " Item Exist");
            QStandardItem *fl = new QStandardItem(QString::fromStdString(flotemp.Display()));
            flotemp.Reset();
            int p = flotemp.GetNextSimpleItem(data);
            while(p != -1){
                QStandardItem *sim = new QStandardItem(QString::fromStdString(data.DisplayItem()));
                flitem->appendRow(sim);
                p = flotemp.GetNextSimpleItem(data);
            }
            stchild->appendRow(fl);
            stchild->appendRow(flitem);
            model->setHeaderData(0, Qt::Horizontal, "Floor");
        }else{
            QMessageBox::warning(this, "Search Error", "Error: Cannot Search Floor! Invaild Label");
        }
    }else{
        QMessageBox::warning(this, "Search Error", "Error: Cannot Search Storage! Invaild Label");
    }
    ui->treeView->setModel(model);
    ui->treeView->expandToDepth(1);
}

void MainWindow::GetPicturePath(QString path){
    if(path == "None"){
        QMessageBox::warning(this, "Load Error", "Error: Picture is not Exist");
        return ;
    }
    delete picwin;
    int x = this->x() + this->width();
    int y = this->y();
    picwin = new PictureWin(this);
    picwin->move(x, y);
    picwin->show();
    emit SendPicturePath(path);
}
void MainWindow::GetPictureLabel(int label){                    //사진을 출력할 Item의 Label을 받아서, 검색 후 출력
    ItemType* data = new Object;
    QString temp;
    data->SetLabel(label);
    if(MasterList.Retrieve(data)){
        temp = QString::fromStdString(data->GetPicture());
        if(temp == "None"){
            QMessageBox::warning(this, "Load Error", "Error: Picture is not Exist");
            return ;
        }
        delete picwin;
        int x = this->x() + this->width();
        int y = this->y();
        picwin = new PictureWin(this);
        picwin->move(x, y);
        picwin->show();
        connect(this, SIGNAL(SendPicturePath(QString)), picwin, SLOT(GetPicturePathFromMain(QString)));
        emit SendPicturePath(temp);
    }else{
        QMessageBox::warning(this, "Load Error", "Error: Cannot Load Picture! Invaild Label");
    }
}

void MainWindow::on_actionRecent_List_triggered()               //최근 리스트출력
{
    ui->treeView->reset();
    QStandardItemModel * model = new QStandardItemModel();
    RecentList.ResetQueue();
    ItemType* data;
    int count = 1;
    int point = RecentList.GetNextItem(data);
    while(point != -1){
        QStandardItem* obj = new QStandardItem(QString::number(count++));
        model->appendRow(obj);
        obj->appendRow(new QStandardItem(QString::fromStdString(data->DisplayItem())));
        point = RecentList.GetNextItem(data);
    }
    QString header_title = QString::fromLocal8Bit("최근 ") + QString::number(RecentList.GetSize()) + QString::fromLocal8Bit("개의 Object");
    model->setHeaderData(0, Qt::Horizontal, header_title);
    ui->treeView->setModel(model);
    ui->treeView->setHeaderHidden(false);
    ui->treeView->expandAll();
}

void MainWindow::on_actionLocationSave_triggered()
{
    QFile File("StorageData.ini");
    if(File.open(QIODevice::WriteOnly|QIODevice::Text)){
        QTextStream SaveStream(&File);
        DoublyIterator<StorageType> iter(StorageList);
        StorageType stotemp;
        stotemp = iter.Next();
        while(iter.NextNotNull()){
            SaveStream << QString::fromStdString(stotemp.OutFile());
            stotemp = iter.Next();
        }
        ui->Main_Info_label->setText("Save Success");
        File.close();
    }else{
        QMessageBox::warning(this, "Save Error", "Error: Cannot Open File");
    }
}

void MainWindow::on_actionItemSave_triggered()
{
    QFile File("ObjectData.ini");
    if(File.open(QIODevice::WriteOnly|QIODevice::Text)){
        QTextStream SaveStream(&File);
        MasterList.ResetTree();
        ItemType* data;
        bool finished;
        MasterList.GetNextItem(data, finished);
        while(finished != true){
            SaveStream << QString::fromStdString(data->OutFile());
            MasterList.GetNextItem(data, finished);
        }

        ui->Main_Info_label->setText("Save Success");
        File.close();
    }else{
        QMessageBox::warning(this, "Save Error", "Error: Cannot Open File");
    }
}

void MainWindow::on_actionItemLoad_triggered()
{
    if(!MasterList.IsEmpty()){
        QMessageBox::warning(this, "Load Error", "Error: ItemList is already Exist! Make List Empty");
        return ;
    }
    QFile File("ObjectData.ini");
    if(!File.open(QFile::ReadOnly|QFile::Text)){
         if(!File.exists())
        {
            QMessageBox::warning(this, "Load Error", "Error: File is not Exist");
        }
        else
        {
            QMessageBox::warning(this, "Load Error", "Error: Cannot Open File");
        }
    }else{
        QTextStream LoadFile(&File);
        QString GetLine;
        int countAdd = 0;
        int countError = 0;
        while(!LoadFile.atEnd()) {
            GetLine=LoadFile.readLine();
            QStringList word = GetLine.split(" ");
            if(word[0].toInt() == 0){
                item = new Object;
                item->SetLabel(word[1].toInt());
                item->SetName(word[2].toStdString());
                item->SetType(word[3].toStdString());
                item->SetVolume(word[4].toInt());
                item->SetBuyDate(word[5].toInt());
                item->SetAttribute(word[6].toInt());
                item->SetStorageID(word[7].toInt());
                item->SetFloorID(word[8].toInt());
                item->SetPicture(word[9].toStdString());
            }else{
                item = new Food;
                item->SetLabel(word[1].toInt());
                item->SetName(word[2].toStdString());
                item->SetType(word[3].toStdString());
                item->SetVolume(word[4].toInt());
                item->SetBuyDate(word[5].toInt());
                item->SetAttribute(word[6].toInt());
                item->SetStorageID(word[7].toInt());
                item->SetFloorID(word[8].toInt());
                item->SetPicture(word[9].toStdString());
            }
            StorageType stotemp;
            FloorType flotemp;
            stotemp.SetLabel(word[7].toInt());
            flotemp.SetLabel(word[8].toInt());
            SimpleItemType simtemp(item);
            if(StorageList.Get(stotemp)){
                if(stotemp.GetFloor(flotemp)){
                    flotemp.AddItem(simtemp);
                    MasterList.Insert(item);
                    countAdd++;
                    count++;
                    stotemp.UpdateFloor(flotemp);
                    StorageList.Replace(stotemp);
                }else{
                    countError++;
                }
            }else{
                countError++;
            }
        }
        ui->Main_Info_label->setText("Add " + QString::number(countAdd) + "Item, Miss " + QString::number(countError) + "Item");
    }
}

void MainWindow::on_actionLocationLoad_triggered()
{
    if(!StorageList.IsEmpty()){
        QMessageBox::warning(this, "Load Error", "Error: StorageList is already Exist! Make List Empty");
        return ;
    }
    QFile File("StorageData.ini");
    if(!File.open(QFile::ReadOnly|QFile::Text)){
         if(!File.exists())
        {
            QMessageBox::warning(this, "Load Error", "Error: File is not Exist");
        }
        else
        {
            QMessageBox::warning(this, "Load Error", "Error: Cannot Open File");
        }
    }else{
        QTextStream LoadFile(&File);
        QString GetLine;
        while(!LoadFile.atEnd())
        {
             GetLine=LoadFile.readLine();
             QStringList word = GetLine.split(" ");
             StorageType stotemp;
             stotemp.SetLabel(word[1].toInt());
             stotemp.SetType(word[2].toStdString());
             for(int i = 0; i < word[0].toInt(); i++){
                 GetLine=LoadFile.readLine();
                 QStringList floword = GetLine.split(" ");
                 FloorType flotemp;
                 flotemp.SetLabel(floword[0].toInt());
                 flotemp.SetType(floword[1].toStdString());
                 stotemp.AddFloor(flotemp);
             }
             StorageList.Add(stotemp);
        }
        ui->Main_Info_label->setText("Load success");
        File.close();
    }

}

void MainWindow::on_actionManual_triggered()
{
    QString aboutText;
    aboutText = "Author: Nakkwan\n";
    aboutText += "Date: 2020-06-20\n";
    aboutText += "(C) DepotManagement (R)\n\n";
    aboutText += QString::fromLocal8Bit("화면의 TabWidget으로 MasterList, Storage에 추가, 삭제\n\n");
    aboutText += QString::fromLocal8Bit("Item 추가시 Storage정보가 입력이 안되면 TempList로 넘어감\n\n");
    aboutText += QString::fromLocal8Bit("파일로부터 불러오기 기능은 저장된 것이 없을 때 사용가능\n\n");
    aboutText += QString::fromLocal8Bit("Heirarchical은 물건을 저장장소 기준으로 보기\n\n");
    aboutText += QString::fromLocal8Bit("Load Temp Item은 저장된 것이 있을때만 사용가능, 해당 Type에 맞춰, TabWidget에 Load됨\n");
    aboutText += QString::fromLocal8Bit("Storage 추가 시, Floor의 타입은 None으로 설정됨\n");

    QMessageBox::about(this, "About Program", aboutText);
}
