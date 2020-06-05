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
SortedList<T>::SortedList() {			//배열 변수 없는 동적할당
	m_Array = new T[MAXSORT];
	m_CurPointer = -1;
	m_length = 0;
	m_size = MAXSORT;
}

template<typename T>
SortedList<T>::SortedList(int size) {		//변수 있는 동적할당
	m_Array = new T[size];
	m_CurPointer = -1;
	m_length = 0;
	m_size = size;
}

template<typename T>
SortedList<T>::~SortedList() {					//소멸자
	delete[] m_Array;
}

template<typename T>
int SortedList<T>::Add(T& data) {			//아이템 더하기
	if (m_length == 0) {						//배열이 비었다면, 0번째 인덱스에 할당
		m_Array[0] = data;
		m_length++;
		return 1;
	}
	else if (m_length == m_size) {				//꽉찼다면 에러 표시
		cout << "Array is pull/n";
		return 0;
	}
	else {
		T temp;
		bool complete = false;				//맨 마지막에 추가되는 것을 확인
		ResetList();
		GetNextItem(temp);
		while (m_CurPointer < m_length&& m_CurPointer != -1) {
			if (temp < data) {				//오름차순이기 때문에 기존 요소보다 고유 라벨이 크다면 뒷쪽에 위치
				GetNextItem(temp);
				continue;
			}
			else if (temp > data) {			//고유 라벨이 더 큰것이 처음 나온 순간이 item이 위치할 곳이다.
				for (int j = m_length; j > m_CurPointer; j--) {
					m_Array[j] = m_Array[j - 1];
				}
				m_Array[m_CurPointer] = data;
				m_length++;
				complete = true;
				break;
			}
			else if (temp == data) {							//고유 라벨이 같은 경우는 없기때문에 add는 return 0로 끝남
				ResetList();
				return 0;
			}
		}
		if (complete == false) {			//고유 라벨이 커서 제일 뒤에 배치해야 할 때
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
int SortedList<T>::GetNextItem(T& data) {		//현재 포인터를 반환하고, 레퍼런스로 데이터를 돌려줌
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
	else {										//정렬된 list이기 때문에 
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
		if (m_Array[m_CurPointer] == data) {			//배열의 크기가 1이라면 while문 안으로 안들어가기 때문에 확인
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
		int left = 0, right = m_length;					//이분탐색
		m_CurPointer = (left + right) / 2;
		while (left != m_CurPointer) {
			if (m_Array[m_CurPointer] > data) {
				right = m_CurPointer;
			}
			else if (m_Array[m_CurPointer] < data) {
				left = m_CurPointer;
			}
			else {												//삭제할 데이터라면
				data = m_Array[m_CurPointer];
				for (int i = m_CurPointer; i < m_length - 1; i++) {
					m_Array[i] = m_Array[i + 1];				//현재포인터까지 배열을 한단계씩 앞으로 당김
				}
				m_length--;
				ResetList();
				return 1;
			}
			m_CurPointer = (left + right) / 2;
		}
		if (m_Array[m_CurPointer] == data) {					//배열의 크기가 1이라면 while문 안으로 안들어가기 때문에 확인
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
		int left = 0, right = m_length;					//이분탐색
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
		if (m_Array[m_CurPointer] == data) {			//배열의 크기가 1이라면 while문 안으로 안들어가기 때문에 확인
			m_Array[m_CurPointer] = data;
			ResetList();
			return 1;
		}
	}
	ResetList();
	return 0;
}

#endif