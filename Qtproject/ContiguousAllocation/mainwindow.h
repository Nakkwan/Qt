#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#define MAXMEMORY 1000

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Memory{
    int index;
    int size;
    int start;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Coalescing();                                                  //Coalescing
    void Compact();                                                     //Compaction
    int Allocate();                                                     //�Ҵ��� ����
    void SortList();                                                    //memState ���� ����
    void SetMemory(QVector<Memory> m, QVector<Memory> get, int n);      //Compaction��, ���� Ž���� ���� (�迭 �� ã�ƺ�)
    int ComparewithList(QVector<Memory> c);                             //memList�� �� ��, ���� ���� Compaction ��� ã�� ����
    void Rearrange(QVector<Memory> &d, int n);                          //compaction �� memory���� ���� ��ġ ����

private slots:
    void on_Input_pushButton_clicked();

    void on_size_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<Memory> memList;            //����� process���� �ִ� vector
    QVector<QVector<int> > memState;    //mem�� �ִ� �Ҵ� �ȵ� ������ ����
    int cur_Memory_size;                //���� �Ҵ�� memory
    int Max_memory_size;                //�Էµ� �� memory
    QVector<Memory> temp;              //BFS�� ���� �ӽ� vector
    QVector<Memory> data;              //memList�� �����ϱ� ���� vector
    QVector<Memory> result;            //BFS�� ����� �����ϱ� ���� vector
    int result_idx;                    //ȿ������ compact�� ���� �ּ� ������ ���
    QString resultview;                 //��� String

};
#endif // MAINWINDOW_H
