#ifndef __SORTEDLIST_H
#define __SORTEDLIST_H

template<typename T>
class SortedList {
private:
	int m_CurPointer;
	int m_length;
	int m_size;
	T* m_Array;
public:
	SortedList();		//constructor
	SortedList(int size);		//constructor
	~SortedList();	//destructor

	/*
	@brief: add data tot array
	@pre: set data
	@post: data added to array sorted by size in ascending order
	@param: ItemType to add the array
	@return: return 1 if add success, return 0 if fail to add
	*/
	int Add(T& data);

	/*
	@brief: make array empty
	@pre: none
	@post: array is empty
	*/
	void MakeEmpty();

	/*
	@brief: get length of array
	@pre: none
	@post: none
	@return array length
	*/
	int GetLength();

	/*
	@brief: confirm if array is full
	@pre: none
	@post: none
	@return: return 1 if array is full, otherwise 0
	*/
	bool IsFull();

	/*
	@brief: confirm if array is empty
	@pre: none
	@post: none
	@return: return 1 if array is empty, otherwise 0
	*/
	bool IsEmpty();

	/*
	@brief: reset pointer of list
	@pre: none
	@post: set pointer of list initially
	*/
	void ResetList();

	/*
	@brief: Get pointer of list and correspond element
	@pre: Set list object
	@post: Receive index and corresponding data
	@param: ItemType that receive array data
	@return: current pointer of list
	*/
	int GetNextItem(T& data);

	/*
	@brief: Get data from list correspond with parameter
	@pre: set ItemType for finding, and sorted list
	@post: parameter assigned data of list
	@param: ItemType that receive array data
	@return: return 1 if array is empty, otherwise 0
	*/
	int Get(T& data);

	/*
	@brief: delete element of list correspond with parameter
	@pre: set ItemType for delete
	@post: element of list is deleted
	@param: ItemType for delete
	@return: return 1 if delete success, otherwise 0
	*/
	int Delete(T data);

	/*
	@brief: replace element of list correspond with ItemType
	@pre: set ItemType for replace
	@post: element of list are replaced
	@return: return 1 if replace success, otherwise 0
	*/
	int Replace(T& data);

	void operator=(const SortedList& data) {
		delete[] m_Array;
		m_size = data.m_size;
		m_length = data.m_length;
		m_CurPointer = data.m_CurPointer;
		m_Array = new T[m_size];
		for (int i = 0; i < m_length; i++) {
			m_Array[i] = data.m_Array[i];
		}
	}
};


template<typename T>
SortedList<T>::SortedList() {			//�迭 ���� ���� �����Ҵ�
	m_Array = new T[MAXSORT];
	m_CurPointer = -1;
	m_length = 0;
	m_size = MAXSORT;
}

template<typename T>
SortedList<T>::SortedList(int size) {		//���� �ִ� �����Ҵ�
	m_Array = new T[size];
	m_CurPointer = -1;
	m_length = 0;
	m_size = size;
}

template<typename T>
SortedList<T>::~SortedList() {					//�Ҹ���
	delete[] m_Array;
}

template<typename T>
int SortedList<T>::Add(T& data) {			//������ ���ϱ�
	if (m_length == 0) {						//�迭�� ����ٸ�, 0��° �ε����� �Ҵ�
		m_Array[0] = data;
		m_length++;
		return 1;
	}
	else if (m_length == m_size) {				//��á�ٸ� ���� ǥ��
		cout << "Array is pull/n";
		return 0;
	}
	else {
		T temp;
		bool complete = false;				//�� �������� �߰��Ǵ� ���� Ȯ��
		ResetList();
		GetNextItem(temp);
		while (m_CurPointer < m_length&& m_CurPointer != -1) {
			if (temp < data) {				//���������̱� ������ ���� ��Һ��� ���� ���� ũ�ٸ� ���ʿ� ��ġ
				GetNextItem(temp);
				continue;
			}
			else if (temp > data) {			//���� ���� �� ū���� ó�� ���� ������ item�� ��ġ�� ���̴�.
				for (int j = m_length; j > m_CurPointer; j--) {
					m_Array[j] = m_Array[j - 1];
				}
				m_Array[m_CurPointer] = data;
				m_length++;
				complete = true;
				break;
			}
			else if (temp == data) {							//���� ���� ���� ���� ���⶧���� add�� return 0�� ����
				ResetList();
				return 0;
			}
		}
		if (complete == false) {			//���� ���� Ŀ�� ���� �ڿ� ��ġ�ؾ� �� ��
			m_Array[m_length] = data;
			m_length++;
		}
		ResetList();
		return 1;
	}
}

template<typename T>
void SortedList<T>::MakeEmpty() {
	m_length = 0;
}

template<typename T>
int SortedList<T>::GetLength() {
	return m_length;
}

template<typename T>
bool SortedList<T>::IsFull() {
	if (m_length == m_size) {
		return 1;
	}
	else {
		return 0;
	}
}

template<typename T>
bool SortedList<T>::IsEmpty() {
	if (m_length == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

template<typename T>
int SortedList<T>::GetNextItem(T& data) {		//���� �����͸� ��ȯ�ϰ�, ���۷����� �����͸� ������
	m_CurPointer++;
	if (m_CurPointer == m_length) {
		m_CurPointer = -1;
		return m_CurPointer;
	}
	data = m_Array[m_CurPointer];
	return m_CurPointer;
}

template<typename T>
void SortedList<T>::ResetList() {
	m_CurPointer = -1;
}

template<typename T>
int SortedList<T>::Get(T& data) {
	if (m_length == 0) {
		return 0;
	}
	else {										//���ĵ� list�̱� ������ 
		ResetList();
		int left = 0, right = m_length;
		m_CurPointer = (left + right) / 2;
		while (left != m_CurPointer) {
			if (m_Array[m_CurPointer] > data) {
				right = m_CurPointer;
			}
			else if (m_Array[m_CurPointer] < data) {
				left = m_CurPointer;
			}
			else if (m_Array[m_CurPointer] == data) {
				data = m_Array[m_CurPointer];
				ResetList();
				return 1;
			}
			m_CurPointer = (left + right) / 2;
		}
		if (m_Array[m_CurPointer] == data) {			//�迭�� ũ�Ⱑ 1�̶�� while�� ������ �ȵ��� ������ Ȯ��
			data = m_Array[m_CurPointer];
			ResetList();
			return 1;
		}
	}
	ResetList();
	return 0;
}

template<typename T>
int SortedList<T>::Delete(T data) {
	if (m_length == 0) {
		return 0;
	}
	else {
		ResetList();
		int left = 0, right = m_length;					//�̺�Ž��
		m_CurPointer = (left + right) / 2;
		while (left != m_CurPointer) {
			if (m_Array[m_CurPointer] > data) {
				right = m_CurPointer;
			}
			else if (m_Array[m_CurPointer] < data) {
				left = m_CurPointer;
			}
			else {												//������ �����Ͷ��
				data = m_Array[m_CurPointer];
				for (int i = m_CurPointer; i < m_length - 1; i++) {
					m_Array[i] = m_Array[i + 1];				//���������ͱ��� �迭�� �Ѵܰ辿 ������ ���
				}
				m_length--;
				ResetList();
				return 1;
			}
			m_CurPointer = (left + right) / 2;
		}
		if (m_Array[m_CurPointer] == data) {					//�迭�� ũ�Ⱑ 1�̶�� while�� ������ �ȵ��� ������ Ȯ��
			for (int j = m_CurPointer; j < m_length - 1; j++) {
				m_Array[j] = m_Array[j + 1];
			}
			m_length--;
			ResetList();
			return 1;
		}
	}
	ResetList();
	return 0;
}

template<typename T>
int SortedList<T>::Replace(T& data) {
	if (m_length == 0) {
		return 0;
	}
	else {
		ResetList();
		int left = 0, right = m_length;					//�̺�Ž��
		m_CurPointer = (left + right) / 2;
		while (left != m_CurPointer) {
			if (m_Array[m_CurPointer] > data) {
				right = m_CurPointer;
			}
			else if (m_Array[m_CurPointer] < data) {
				left = m_CurPointer;
			}
			else {
				m_Array[m_CurPointer] = data;
				ResetList();
				return 1;
			}
			m_CurPointer = (left + right) / 2;
		}
		if (m_Array[m_CurPointer] == data) {			//�迭�� ũ�Ⱑ 1�̶�� while�� ������ �ȵ��� ������ Ȯ��
			m_Array[m_CurPointer] = data;
			ResetList();
			return 1;
		}
	}
	ResetList();
	return 0;
}

#endif