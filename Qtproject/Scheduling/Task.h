#ifndef TASK_H
#define TASK_H

#include "QString"

//class for Task
class Task {
private:
    QString T_name;                 //Task Name
    int T_computation;              //Computation time of task
    int T_period;                   //Period in Periodic, Arrival time in Aperiodic Task
    int T_idx;                      //Index of task
public:
    QString GetName() const;
    int GetComputation() const;
    int GetPeriod() const;
    int GetIndex() const;

    void SetName(QString inName);
    void SetComputation(int incom);
    void SetPeriod(int inper);
    void SetIndex(int idx);

    bool operator==(const Task& data) {
        if (T_period == data.GetPeriod()) {
            return true;
        }
        else {
            return false;
        }
    }

    bool operator>(const Task& data) {
        if (T_period > data.GetPeriod()) {
            return true;
        }
        else {
            return false;
        }
    }

    bool operator<(const Task& data) {
        if (T_period < data.GetPeriod()) {
            return true;
        }
        else {
            return false;
        }
    }

    void operator=(const Task& data) {
        T_period = data.GetPeriod();
        T_computation = data.GetComputation();
        T_name = data.GetName();
        T_idx = data.GetIndex();
    }
};

#endif
