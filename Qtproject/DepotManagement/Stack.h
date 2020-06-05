#ifndef __STACK_H
#define __STACK_H

template<typename T>
class Stack {
private:
	int S_top;
	int S_size;
	int cur_Pointer;
	T* S_stack;
public:
	Stack();				//constructor
	Stack(int size);		//constructor
	~Stack();				//destructor

	/*
	@breif: 스택 비우기
	@pre: none
	@post: none
	*/
	void MakeEmpty();

	/*
	@breif: 스택이 찼는지 확인
	@pre: none
	@post: none
	*/
	bool IsFull();

	/*
	@breif: 스택이 비었는지 확인
	@pre: none
	@post: none
	*/
	bool IsEmpty();

	/*
	@breif: 스택에 element 추가
	@pre: 넣을 element 설정
	@post: 스택에 element 추가되고, 크기 +1
	*/
	int Push(const T& data);

	/*
	@breif: 스택에서 element 빼기
	@pre: none
	@post: stack 맨위 element가 삭제되고, reference로 반환
	@param: element값을 받을 변수
	*/
	int Pop(T& data);

	/*
	@breif: 스택의 포인터 초기화
	@pre: none
	@post: 스택의 pointer가 -1로 초기화
	*/
	void ResetStack();

	/*
	@breif: 다음 element를 받음
	@pre: none
	@post: stack의 크기 내에서 포인터를 1증가시키고, 해당하는 element를 reference로 받음.
			범위를 벗어나면 -1로 초기화
	@return: 포인터
	*/
	int GetNextItem(T& data);

	/*
	@breif: stack에서 데이터 찾기
	@pre: 찾을 데이터를 설정
	@post: 찾은 데이터를 reference로 반환
	@param: 데이터를 받을 변수
	@return: 데이터를 찾으면 1, 아니면 0을 반환
	*/
	int Get(T& data);

	/*
	@breif: stack에서 top element 받기
	@pre: Set stack
	@post: Stack의 제일 윗 데이터를 reference로 반환
	@param: 데이터를 받을 변수
	@return: 데이터를 받으면 1, 아니면 0을 반환
	*/
	int GetTop(T& data);

	/*
	@breif: stack의 데이터 교체
	@pre: 교체할 데이터 설정
	@post: 해당하는 stack의 element data가 바뀜
	@param: 바꿀 데이터
	@return: 데이터를 바꾸면 1, 아니면 0을 반환
	*/
	int Replace(T& data);

	/*
	@breif: stack에서 데이터를 삭제함
	@pre: 삭제할 값 설정
	@post: 해당하는 stack의 element data가 삭제되고, stack의 크기가 1 줄어듦
	@param: 삭제할 데이터
	@return: 데이터를 삭제하면 1, 아니면 0을 반환
	*/
	int Delete(T& data);

	/*
	@breif: stack의 사이즈 확인
	@pre: none
	@post: none
	@return: stack의 size return
	*/
	int getSize();

	/*
	@breif: stack의 데이터 교체
	@pre: 교체할 데이터가 설정되어 있어야함. index가 범위 내여야 함
	@post: 해당하는 stack의 element data가 바뀜
	@param: 바꿀 데이터, 바꿀 데이터의 index
	@return: 데이터를 바꾸면 1, 아니면 0을 반환
	*/
	int ReplacebyIndex(T& data, int index);

	/*
	@breif: stack에서 데이터 찾기
	@pre: 찾을 데이터의 ID가 설정되어 있어야 함. index가 범위 내여야 함
	@post: 찾은 데이터를 reference로 반환
	@param: 데이터를 받을 변수, 찾을 데이터의 index
	@return: 데이터를 찾으면 1, 아니면 0을 반환
	*/
	int GetbyIndex(T& data, int index);

	/*
	@breif: stack에서 데이터의 존재 여부 확인
	@pre: 찾을 데이터의 ID 설정
	@post: none
	@param: 찾을 데이터
	@return: 데이터가 존재하면 1, 아니면 0을 반환
	*/
	int Find(T& data);
};


template<typename T>
Stack<T>::Stack() {
	S_stack = new T[MAXSTACK];
	S_size = MAXSTACK;
	S_top = -1;
	cur_Pointer = -1;
}

template<typename T>
Stack<T>::Stack(int size) {
	S_stack = new T[size];
	S_size = size;
	S_top = -1;
	cur_Pointer = -1;
}

template<typename T>
Stack<T>::~Stack() {
	delete[] S_stack;
}

template<typename T>
void Stack<T>::MakeEmpty() {
	S_top = -1;
}

template<typename T>
bool Stack<T>::IsFull() {
	if (S_top == S_size - 1) {
		return true;
	}
	else {
		return false;
	}
}

template<typename T>
bool Stack<T>::IsEmpty() {
	if (S_top == -1) {
		return true;
	}
	else {
		return false;
	}
}

template<typename T>
int Stack<T>::Push(const T& data) {
	if (IsFull()) {						//배열이 꽉 차면 에러
		cout << "Error: Stack is already full\n";
		return 0;
	}
	else {
		S_top++;
		S_stack[S_top] = data;
	}
	return 1;
}

template<typename T>
int Stack<T>::Pop(T& data) {
	if (IsEmpty()) {						//배열이 비었으면 에러
		cout << "Error: Stack is already empty\n";
		return 0;
	}
	else {
		data = S_stack[S_top];
		S_top--;
	}
	return 1;
}

template<typename T>
void Stack<T>::ResetStack() {
	cur_Pointer = -1;
}

template<typename T>
int Stack<T>::GetNextItem(T& data) {
	if (cur_Pointer == S_top) {				//포인터가 stack의 꼭대기에 도달했으면 -1로 만듦
		cur_Pointer = -1;
		return cur_Pointer;
	}
	else {
		cur_Pointer++;						//포인터를 증가시킨 후 값 반환
		data = S_stack[cur_Pointer];
		return cur_Pointer;
	}
}

template<typename T>
int Stack<T>::Get(T& data) {
	T temp;
	ResetStack();
	GetNextItem(temp);
	while (cur_Pointer != -1) {
		if (temp == data) {				//찾는 데이터가 있다면
			data = temp;				//reference로 반환
			return 1;
		}
		else {
			GetNextItem(temp);
		}
	}
	return 0;
}

template<typename T>
int Stack<T>::Find(T& data) {
	T temp;
	ResetStack();
	GetNextItem(temp);
	while (cur_Pointer != -1) {
		if (temp == data) {				//찾는 데이터가 있다면	
			return 1;
		}
		else {
			GetNextItem(temp);
		}
	}
	return 0;
}


template<typename T>
int Stack<T>::GetTop(T& data) {
	if (IsEmpty()) {						//배열이 비었으면 에러
		cout << "Error: Stack is already empty\n";
		return 0;
	}
	else {
		data = S_stack[S_top];
	}
	return 1;
}

template<typename T>
int Stack<T>::Replace(T& data) {
	T temp;
	ResetStack();
	GetNextItem(temp);
	while (cur_Pointer != -1) {
		if (temp == data) {						//바꿀 데이터를 찾았으면
			S_stack[cur_Pointer] = data;		//데이터를 바꿔줌
			return 1;
		}
		GetNextItem(temp);					//해당 데이터가 아닐 시, 다음 값 설정
	}
	return 0;
}

template<typename T>
int Stack<T>::Delete(T& data) {
	T temp;
	ResetStack();
	GetNextItem(temp);
	while (cur_Pointer != -1) {
		if (temp == data) {										//삭제할 데이터가 있으면
			for (int i = cur_Pointer; i < S_top; i++) {			//top부터 해당 포인터까지 값을 하나씩 내려줌
				S_stack[i] = S_stack[i + 1];
			}
			S_top--;
			return 1;
		}
		else {
			GetNextItem(temp);
		}
	}
	return 0;
}

template<typename T>
int Stack<T>::getSize() {
	return S_top + 1;
}

template<typename T>
int Stack<T>::ReplacebyIndex(T& data, int index) {
	if (index > S_top || index < 0) {
		return 0;
	}
	S_stack[index] = data;
	return 1;
}

template<typename T>
int Stack<T>::GetbyIndex(T& data, int index) {
	if (index > S_top || index < 0) {
		return 0;
	}
	data = S_stack[index];
	return 1;
}

#endif