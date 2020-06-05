#ifndef __QUEUE_H
#define __QUEUE_H

template<typename T>
class Queue {
private:
	int Q_head;
	int Q_tail;
	int Q_size;					//데이터가 들어갈 수 있는 전체 queue의 크기, 전체 할당된 크기는 Q_size + 1이다.
	int Q_curSize;				//현재 저장된 것들의 크기
	int Q_curPointer;			//포인터
	T* Q_item;

public:
	Queue();					//생성자
	Queue(int size);			//생성자
	~Queue();					//소멸자

	/*
	@brief: queue 초기화
	@pre: none
	@post: queue의 크기가 0이 되고, head와 tail이 초기화 됨
	*/
	void MakeEmpty();

	/*
	@brief: queue가 꽉 찼는지 결정
	@pre: none
	@post: none
	*/
	bool IsFull();

	/*
	@brief: queue가 비었는지 결정
	@pre: none
	@post: none
	*/
	bool IsEmpty();

	/*
	@brief: queue에 데이터 추가
	@pre: 추가할 데이터 설정
	@post: queue에 데이터가 추가되고 크기가 1 늘어남. head가 다음 칸으로 이동
	@return: 추가가 되면 1, 안되면 0 return
	*/
	int Enqueue(T& data);

	/*
	@brief: queue에 먼저 들어온 데이터 삭제
	@pre: none
	@post: queue에 데이터가 삭제되고 크기가 1 줄어듦. tail이 다음 칸으로 이동. 삭제된 데이터를 reference로 반환
	@param: 삭제된 데이터를 reference로 받을 변수
	@return: 삭제가 되면 1, 안되면 0 return
	*/
	int Dequeue(T& data);

	/*
	@brief: queue의 사이즈 확인
	@pre: none
	@post: none
	*/
	int GetSize();

	/*
	@brief: queue의 포인터 리셋
	@pre: none
	@post: queue의 포인터가 tail과 같게 초기화 됨
	*/
	void ResetQueue();

	/*
	@brief: 다음 포인터에 해당하는 데이터, pointer 반환
	@pre: none
	@post: 포인터가 1늘어나고 그에 해당하는 데이터가 return 됨
	@param: 데이터를 받을 변수
	@return: pointer return
	*/
	int GetNextItem(T& data);

	/*
	@brief: 데이터를 찾음
	@pre: 찾을 데이터 설정
	@post: 해당하는 데이터가 reference로 반환 됨
	@param: 반환 받을 변수
	@return: 데이터를 찾으면 1, 아니면 0을 return
	*/
	int Get(T& data);

	/*
	@brief: 해당하는 데이터 삭제
	@pre: 삭제할 데이터 설정
	@post: 해당하는 데이터가 삭제되고, queue가 재정렬됨
	@param: 삭제할 데이터의 정보가 담긴 변수
	@return: 삭제가 되면 1 아니면 0을 return
	*/
	int Delete(const T& data);

	/*
	@brief: queue의 element를 교체
	@pre: 교체할 데이터 설정
	@post: 해당하는 element의 데이터가 교체됨
	@param: 교체할 데이터
	@return: 데이터가 교체되면 1, 아니면 0을 return
	*/
	int Replace(T data);
};


template<typename T>
Queue<T>::Queue() {
	Q_item = new T[MAXQUEUE];
	Q_size = MAXQUEUE - 1;
	Q_head = Q_size;
	Q_tail = Q_size;
	Q_curSize = 0;
	Q_curPointer = -1;
}

template<typename T>
Queue<T>::Queue(int size) {
	Q_item = new T[size + 1];
	Q_size = size;
	Q_head = Q_size;
	Q_tail = Q_size;
	Q_curPointer = -1;
	Q_curSize = 0;
}

template<typename T>
Queue<T>::~Queue() {
	delete[] Q_item;
}

template<typename T>
void Queue<T>::MakeEmpty() {
	Q_head = Q_size;
	Q_tail = Q_size;
	Q_curSize = 0;
}

template<typename T>
bool Queue<T>::IsFull() {
	if (Q_curSize == Q_size) {
		return true;
	}
	else {
		return false;
	}
}

template<typename T>
bool Queue<T>::IsEmpty() {
	if (Q_curSize == 0) {
		return true;
	}
	else {
		return false;
	}
}

template<typename T>
int Queue<T>::Enqueue(T& data) {					//추가
	if (IsFull()) {
		Q_head = (Q_head + 1) % (Q_size + 1);	//head를 다음칸으로 넘기고
		Q_item[Q_head] = data;					//할당
		Q_tail = (Q_tail + 1) % (Q_size + 1);
	}
	else {										//queue가 꽉차지 않았다면
		Q_head = (Q_head + 1) % (Q_size + 1);	//head를 다음칸으로 넘기고
		Q_item[Q_head] = data;					//할당
		Q_curSize += 1;
	}
	return 1;
}

template<typename T>
int Queue<T>::Dequeue(T& data) {
	if (IsEmpty()) {
		cout << "Error: Queue is already empty\n";
		return 0;
	}
	else {							//비어있지 않다면
		Q_tail = (Q_tail + 1) % (Q_size + 1);	//Q_tail을 다음칸으로 넘기고
		data = Q_item[Q_tail];						//값 반환 후
		Q_curSize--;							//현재 queue 사이즈 줄임
	}
	return 1;
}

template<typename T>
int Queue<T>::GetSize() {
	return Q_curSize;
}

template<typename T>
void Queue<T>::ResetQueue() {
	Q_curPointer = Q_tail;
}

template<typename T>
int Queue<T>::GetNextItem(T& data) {
	if (Q_curPointer == Q_head) {					//head랑 같아졌다면
		Q_curPointer = -1;							//-1 반환(-1은 배열엔 없는 수이기 때문)
		return Q_curPointer;
	}
	else {
		Q_curPointer = (Q_curPointer + 1) % (Q_size + 1);
		data = Q_item[Q_curPointer];
		return Q_curPointer;
	}
}

template<typename T>
int Queue<T>::Get(T& data) {
	T temp;
	ResetQueue();
	GetNextItem(temp);
	while (Q_curPointer != -1) {
		if (temp == data) {
			data = temp;
			return 1;
		}
		else {
			GetNextItem(temp);
		}
	}

	return 0;
}

template<typename T>
int Queue<T>::Delete(const T& data) {
	T temp;
	ResetQueue();
	GetNextItem(temp);
	if (IsEmpty()) {
		return 0;
	}
	else {
		while (Q_curPointer != -1) {
			if (temp == data) {				//지울 item을 찾았다면
				int i = Q_curPointer;
				int j;
				while (i != ((Q_tail + 1) % (Q_size + 1))) {		//tail과 같아질 때까지
					if (i > 0) {
						j = i - 1;
					}
					else {
						j = Q_size;
					}
					Q_item[i] = Q_item[j];		//아이템 당기기
					i = j;
				}
				Q_size--;
				Q_tail = (Q_tail + 1) % (Q_size + 1);
				return 1;
			}
			else {
				GetNextItem(temp);
			}
		}
	}
	return 0;
}

template<typename T>
int Queue<T>::Replace(T data) {
	T temp;
	ResetQueue();
	GetNextItem(temp);
	while (Q_curPointer != -1) {
		if (temp == data) {
			Q_item[Q_curPointer] = data;
			return 1;
		}
		else {
			GetNextItem(temp);
		}
	}
	return 0;
}
#endif