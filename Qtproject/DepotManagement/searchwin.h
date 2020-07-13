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

signals:                                            //MainWindow�� �˻� �ϴ� ������ ������ ������ ���� signal
    void ObjectLabel(int label);                    //label �˻�
    void ObjectName(QString name);                  //�̸� �˻�

    void ObjectType(QString Type);                  //type �˻�
    void ObjectDate(int from, int to);              //��¥�� �˻�
    void ObjectDueDate(int date);                   //������� �˻� (food�� ����)

    void StorageLabel(int label);                   //Storage �˻�
    void FloorLabel(int sto, int flo);              //Floor �˻�

    void PicturePath(QString path);                 //���� ��η� �˻�
    void PictureLabel(int label);                   //���� item label�� �˻�

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
