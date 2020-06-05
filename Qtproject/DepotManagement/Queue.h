#ifndef __QUEUE_H
#define __QUEUE_H

template<typename T>
class Queue {
private:
	int Q_head;
	int Q_tail;
	int Q_size;					//�����Ͱ� �� �� �ִ� ��ü queue�� ũ��, ��ü �Ҵ�� ũ��� Q_size + 1�̴�.
	int Q_curSize;				//���� ����� �͵��� ũ��
	int Q_curPointer;			//������
	T* Q_item;

public:
	Queue();					//������
	Queue(int size);			//������
	~Queue();					//�Ҹ���

	/*
	@brief: queue �ʱ�ȭ
	@pre: none
	@post: queue�� ũ�Ⱑ 0�� �ǰ�, head�� tail�� �ʱ�ȭ ��
	*/
	void MakeEmpty();

	/*
	@brief: queue�� �� á���� ����
	@pre: none
	@post: none
	*/
	bool IsFull();

	/*
	@brief: queue�� ������� ����
	@pre: none
	@post: none
	*/
	bool IsEmpty();

	/*
	@brief: queue�� ������ �߰�
	@pre: �߰��� ������ ����
	@post: queue�� �����Ͱ� �߰��ǰ� ũ�Ⱑ 1 �þ. head�� ���� ĭ���� �̵�
	@return: �߰��� �Ǹ� 1, �ȵǸ� 0 return
	*/
	int Enqueue(T& data);

	/*
	@brief: queue�� ���� ���� ������ ����
	@pre: none
	@post: queue�� �����Ͱ� �����ǰ� ũ�Ⱑ 1 �پ��. tail�� ���� ĭ���� �̵�. ������ �����͸� reference�� ��ȯ
	@param: ������ �����͸� reference�� ���� ����
	@return: ������ �Ǹ� 1, �ȵǸ� 0 return
	*/
	int Dequeue(T& data);

	/*
	@brief: queue�� ������ Ȯ��
	@pre: none
	@post: none
	*/
	int GetSize();

	/*
	@brief: queue�� ������ ����
	@pre: none
	@post: queue�� �����Ͱ� tail�� ���� �ʱ�ȭ ��
	*/
	void ResetQueue();

	/*
	@brief: ���� �����Ϳ� �ش��ϴ� ������, pointer ��ȯ
	@pre: none
	@post: �����Ͱ� 1�þ�� �׿� �ش��ϴ� �����Ͱ� return ��
	@param: �����͸� ���� ����
	@return: pointer return
	*/
	int GetNextItem(T& data);

	/*
	@brief: �����͸� ã��
	@pre: ã�� ������ ����
	@post: �ش��ϴ� �����Ͱ� reference�� ��ȯ ��
	@param: ��ȯ ���� ����
	@return: �����͸� ã���� 1, �ƴϸ� 0�� return
	*/
	int Get(T& data);

	/*
	@brief: �ش��ϴ� ������ ����
	@pre: ������ ������ ����
	@post: �ش��ϴ� �����Ͱ� �����ǰ�, queue�� �����ĵ�
	@param: ������ �������� ������ ��� ����
	@return: ������ �Ǹ� 1 �ƴϸ� 0�� return
	*/
	int Delete(const T& data);

	/*
	@brief: queue�� element�� ��ü
	@pre: ��ü�� ������ ����
	@post: �ش��ϴ� element�� �����Ͱ� ��ü��
	@param: ��ü�� ������
	@return: �����Ͱ� ��ü�Ǹ� 1, �ƴϸ� 0�� return
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
int Queue<T>::Enqueue(T& data) {					//�߰�
	if (IsFull()) {
		Q_head = (Q_head + 1) % (Q_size + 1);	//head�� ����ĭ���� �ѱ��
		Q_item[Q_head] = data;					//�Ҵ�
		Q_tail = (Q_tail + 1) % (Q_size + 1);
	}
	else {										//queue�� ������ �ʾҴٸ�
		Q_head = (Q_head + 1) % (Q_size + 1);	//head�� ����ĭ���� �ѱ��
		Q_item[Q_head] = data;					//�Ҵ�
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
	else {							//������� �ʴٸ�
		Q_tail = (Q_tail + 1) % (Q_size + 1);	//Q_tail�� ����ĭ���� �ѱ��
		data = Q_item[Q_tail];						//�� ��ȯ ��
		Q_curSize--;							//���� queue ������ ����
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
	if (Q_curPointer == Q_head) {					//head�� �������ٸ�
		Q_curPointer = -1;							//-1 ��ȯ(-1�� �迭�� ���� ���̱� ����)
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
			if (temp == data) {				//���� item�� ã�Ҵٸ�
				int i = Q_curPointer;
				int j;
				while (i != ((Q_tail + 1) % (Q_size + 1))) {		//tail�� ������ ������
					if (i > 0) {
						j = i - 1;
					}
					else {
						j = Q_size;
					}
					Q_item[i] = Q_item[j];		//������ ����
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