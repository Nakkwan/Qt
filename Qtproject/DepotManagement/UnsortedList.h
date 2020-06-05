#ifndef __UNSORTEDLIST_H
#define __UNSORTEDLIST_H

template<typename T>
class UnsortedList {
private:
	int m_CurPointer;
	int m_length;				//현재 배열의 크기
	int Array_size;				//배열 크기의 한계
	T* m_Array;
public:
	UnsortedList();		//constructor
	UnsortedList(int size);		//constructor
	~UnsortedList();	//destructor

	/*
	@brief: add element data to array
	@pre: set element data
	@post: data added to array
	@param: ItemType to add the array
	@return: return 1 if add success, return 0 if fail to add
	*/
	int Add(const T& data);

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
	@brief: Get data from list correspond with label
	@pre: set uinque label for finding
	@post: parameter assigned data of list
	@param: ItemType that receive array data
	@return: return 1 if array is empty, otherwise 0
	*/
	int Get(T& data);

	/*
	@brief: delete element of list correspond with unique label
	@pre: set unique label for delete
	@post: element of list is deleted
	@param: data that has unique label for delete
	@return: return 1 if array is empty, otherwise 0
	*/
	int Delete(T data);

	/*
	@brief: replace element of list correspond with unique label
	@pre: set unique label for replace
	@post: element of list are replaced
	@return: return 1 if array is empty, otherwise 0
	*/
	int Replace(const T& data);

	/*
	@brief: Get Item according to index
	@pre: UnsortedList is not empty
	@post: element of the index is return by reference
	@param: UnsortedList Type, index
	*/
	int GetItemByIndex(T& data, int idx) const;

	void operator=(const UnsortedList& data) {
		delete[] m_Array;
		m_length = data.m_length;
		m_CurPointer = data.m_CurPointer;
		Array_size = data.Array_size;
		m_Array = new T[Array_size];
		for (int i = 0; i < m_length; i++) {
			m_Array[i] = data.m_Array[i];
		}
	}
};


template<typename T>
UnsortedList<T>::UnsortedList() {			//변수 없는 동적 할당
	m_CurPointer = -1;
	m_length = 0;
	m_Array = new T[MAXSIZE];
	Array_size = MAXSIZE;
}

template<typename T>
UnsortedList<T>::UnsortedList(int size) {		//size를 준 동적할당
	m_CurPointer = -1;
	m_length = 0;
	m_Array = new T[size];
	Array_size = size;
}

template<typename T>
UnsortedList<T>::~UnsortedList() {				//소멸자
	delete[] m_Array;
}

template<typename T>
int UnsortedList<T>::Add(const T& data) {
	if (!IsFull()) {		//배열이 꽉 차있지 않은지 확인
		T temp;
		ResetList();
		GetNextItem(temp);
		while (m_CurPointer != -1) {	//배열 전체 탐색
			if (temp == data) {
				return 0;
			}
			GetNextItem(temp);
		}

		m_Array[m_length] = data;
		m_length++;
		return 1;
	}
	else {
		cout << "Error: List if full\n";
		return 0;
	}
}

template<typename T>
void UnsortedList<T>::MakeEmpty() {
	m_length = 0;
	delete[] m_Array;
}

template<typename T>
int UnsortedList<T>::GetLength() {
	return m_length;
}

template<typename T>
bool UnsortedList<T>::IsFull() {
	if (m_length == Array_size) {
		return 1;
	}
	else {
		return 0;
	}
}

template<typename T>
bool UnsortedList<T>::IsEmpty() {
	if (m_length == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

template<typename T>
int UnsortedList<T>::GetNextItem(T& data) {		//현재 포인터를 반환하고, 레퍼런스로 데이터를 돌려줌
	m_CurPointer++;
	if (m_CurPointer == m_length) {				//배열의 한계치와 같다면 -1로 리턴
		m_CurPointer = -1;
		return m_CurPointer;
	}
	data = m_Array[m_CurPointer];				//-1부터 시작이기 때문에 먼저 ++하고 데이터 할당
	return m_CurPointer;
}

template<typename T>
void UnsortedList<T>::ResetList() {
	m_CurPointer = -1;
}

template<typename T>
int UnsortedList<T>::Get(T& data) {				//data값이 같으면 reference로 값을 돌려줌
	T temp;
	ResetList();
	GetNextItem(temp);
	while (m_CurPointer != -1) {	//배열 전체 탐색
		if (temp == data) {
			data = temp;			//데이터 반환
			return 1;
		}
		GetNextItem(temp);
	}
	return 0;
}

template<typename T>
int UnsortedList<T>::Delete(T data) {			//data값에 해당하는 값을 삭제함
	T temp;
	ResetList();
	GetNextItem(temp);
	while (m_CurPointer != -1) {
		if (temp == data) {
			for (int j = m_CurPointer; j < m_length - 1; j++) {
				m_Array[j] = m_Array[j + 1];				//현재포인터까지 배열을 한단계씩 앞으로 당김
			}
			m_length--;
			return 1;
		}
		GetNextItem(temp);
	}
	return 0;
}

template<typename T>
int UnsortedList<T>::Replace(const T& data) {				//데이터 교체
	T temp;
	ResetList();
	GetNextItem(temp);
	while (m_CurPointer != -1) {
		if (temp == data) {
			m_Array[m_CurPointer] = data;
			return 1;
		}
		GetNextItem(temp);
	}
	return 0;
}

template<typename T>
int UnsortedList<T>::GetItemByIndex(T& data, int idx) const {
	if (idx < m_length && idx > -1) {				//index가 유효한 값이라면
		data = m_Array[idx];						//reference로 반환
	}
	else {
		return 0;
	}
	return 1;
}
#endif