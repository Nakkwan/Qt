#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pch.h"
#include <QMainWindow>
#include "searchwin.h"
#include "picturewin.h"
#include "QLabel"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public Base
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void SendPicturePath(QString path);

private slots:

    //검색창 띄우기
    void on_actionSearch_triggered();
    //Item Add
    void on_Item_Add_pushButton_clicked();
    //Display All item in TreeView
    void on_Display_All_pushButton_clicked();
    //Clear treeview
    void on_Clear_pushButton_clicked();
    //Storage add
    void on_Storage_Add_pushButton_clicked();
    //Storage load for Update
    void on_Storage_Update_Load_pushButton_clicked();
    //Storgae update
    void on_Storage_Update_pushButton_clicked();
    //Storage Delete
    void on_Storage_Delete_pushButton_clicked();
    //Floor Add
    void on_Floor_Add_pushButton_clicked();
    //Floor Load for Update
    void on_Floor_Update_Load_pushButton_clicked();
    //Floor Update
    void on_Floor_Update_pushButton_clicked();
    //Floor Delete
    void on_Floor_Delete_pushButton_clicked();
    //Floor Add
    void on_Food_Add_pushButton_clicked();
    //Object Delete
    void on_Item_Delete_pushButton_clicked();
    //Object Update
    void on_Item_Update_pushButton_clicked();
    //Add Picture of item
    void on_Item_Add_Picture_pushButton_clicked();
    //Load Object info for upate
    void on_Item_Update_Load_pushButton_clicked();
    //Add Picture of Floor
    void on_Food_Add_Picture_pushButton_clicked();
    //Add picture of Item for update
    void on_Item_Update_Picture_pushButton_clicked();
    //View Item Heirarchically in treeview
    void on_actionHeirarchical_triggered();
    //View TempList in treeview
    void on_actionTemp_List_triggered();
    //Load item in TempList
    void on_actionTemp_Dequeue_triggered();
    //ViewRecentList in treeview
    void on_actionRecent_List_triggered();
    //Save Location information in file
    void on_actionLocationSave_triggered();
    //Save Item information in file
    void on_actionItemSave_triggered();
    //Load item information by file
    void on_actionItemLoad_triggered();
    //Load Storage Information by file
    void on_actionLocationLoad_triggered();

    void on_actionManual_triggered();

public slots:                                           //SearchWin으로부터 받은 signal을 처리하는 slot
    void GetObjectLabel(int label);
    void GetObjectName(QString name);
    void GetObjectType(QString type);
    void GetObjectDate(int from, int to);
    void GetObjectDueDate(int date);

    void GetStorageLabel(int label);
    void GetFloorLabel(int sto, int flo);

    void GetPicturePath(QString path);
    void GetPictureLabel(int label);

private:
    Ui::MainWindow *ui;
    SearchWin* searchwin;
    PictureWin* picwin;
    LinkedQueue<ItemType> TempList;
    Queue<ItemType> RecentList;
    QString MainText;
    int count;
};
#endif // MAINWINDOW_H
