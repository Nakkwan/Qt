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
    int Allocate();                                                     //할당을 위한
    void SortList();                                                    //memState 순서 정리
    void SetMemory(QVector<Memory> m, QVector<Memory> get, int n);      //Compaction시, 완전 탐색을 위함 (배열 다 찾아봄)
    int ComparewithList(QVector<Memory> c);                             //memList와 비교 후, 제일 좋은 Compaction 방법 찾기 위함
    void Rearrange(QVector<Memory> &d, int n);                          //compaction 후 memory들의 시작 위치 설정

private slots:
    void on_Input_pushButton_clicked();

    void on_size_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<Memory> memList;            //힐당된 process들이 있는 vector
    QVector<QVector<int> > memState;    //mem에 있는 할당 안된 공간을 담음
    int cur_Memory_size;                //현재 할당된 memory
    int Max_memory_size;                //입력된 총 memory
    QVector<Memory> temp;              //BFS를 위한 임시 vector
    QVector<Memory> data;              //memList를 저장하기 위한 vector
    QVector<Memory> result;            //BFS의 결과를 저장하기 위한 vector
    int result_idx;                    //효율적인 compact를 위한 최소 움직인 결과
    QString resultview;                 //결과 String

};
#endif // MAINWINDOW_H
