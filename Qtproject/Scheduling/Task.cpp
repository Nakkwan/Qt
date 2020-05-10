#include "Task.h"

QString Task::GetName() const {
	return T_name;
}
int Task::GetComputation() const {
	return T_computation;
}
int Task::GetPeriod() const {
	return T_period;
}
int Task::GetIndex() const{
    return T_idx;
}

void Task::SetName(QString in) {
	T_name = in;
}
void Task::SetComputation(int in) {
	T_computation = in;
}
void Task::SetPeriod(int in) {
	T_period = in;
}
void Task::SetIndex(int idx){
    T_idx = idx;
}
