#ifndef SEARCHWIN_H
#define SEARCHWIN_H

#include <QDialog>
#include <QMouseEvent>

namespace Ui {
class SearchWin;
}

class SearchWin : public QDialog
{
    Q_OBJECT

public:
    explicit SearchWin(QWidget *parent = nullptr);
    ~SearchWin();
    void MultiKey();

signals:                                            //MainWindow에 검색 하는 물건의 정보를 보내기 위한 signal
    void ObjectLabel(int label);                    //label 검색
    void ObjectName(QString name);                  //이름 검색

    void ObjectType(QString Type);                  //type 검색
    void ObjectDate(int from, int to);              //날짜로 검색
    void ObjectDueDate(int date);                   //유통기한 검색 (food에 한정)

    void StorageLabel(int label);                   //Storage 검색
    void FloorLabel(int sto, int flo);              //Floor 검색

    void PicturePath(QString path);                 //사진 경로로 검색
    void PictureLabel(int label);                   //사진 item label로 검색

private slots:
    void on_Object_Label_pushButton_clicked();

    void on_Object_Name_pushButton_clicked();

    void on_Object_Date_pushButton_clicked();

    void on_Object_DueDate_pushButton_clicked();

    void on_Storage_pushButton_clicked();

    void on_Floor_pushButton_clicked();

    void on_Picture_Path_pushButton_clicked();

    void on_Picture_Label_pushButton_clicked();

    void on_Object_Type_pushButton_clicked();

private:
    Ui::SearchWin *ui;
    QPoint startPos;
};

#endif // SEARCHWIN_H
