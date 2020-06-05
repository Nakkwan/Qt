#ifndef __SINGLELINKEDLIST_H
#define __SINGLELINKEDLIST_H

template <typename T>
struct Node
{
    T value;	///< A data for each node.
    Node* next;	///< A node pointer to point succeed node.
};


/*Class for CircularList*/
template<typename T>
class SingleLinkedList {
public:
    int size;               //list size
    Node<T>* head;          //pointer for fist node of list
    Node<T>* curPointer;
    int curIndex;

    // constructor
    SingleLinkedList() {
        size = 0;
        head = nullptr;
        curPointer = nullptr;
        curIndex = -1;
    }

    // destructor
    ~SingleLinkedList() {
        MakeEmpty();
    }

    /*
    @bried: 리스트를 비어있게 만든다.
    @pre: none
    @post: List is empty
    */
    void MakeEmpty();

    /*
    @bried: 리스트가 비었는지 확인
    @pre: none
    @post: none
    @return: 리스트가 비었으면 1, 아니면 0을 return 함
    */
    bool IsEmpty();

    /*
    @bried: 리스트의 길이를 반환한다.
    @pre: none
    @post: none
    */
    int GetLength() const;

    /*
    @bried: 리스트에 값을 추가한다.
    @pre: set data
    @post: 리스트에 값이 크기에 맞게 추가된다.
    */
    int Add(const T& data);

    /*
    @bried: delete data from list
    @pre: set data for delete
    @post: 리스트에서 해당 데이터가 삭제되고 그 값을 reference로 반환한다.
    */
    int Delete(T& data);

    /*
    @bried: 리스트에서 data를 찾는다.
    @pre: set data for find data
    @post: 해당하는 데이터가 reference로 반환된다.
    */
    int Get(T& data);

    /*
    @bried: 리스트의 데이터 값을 교체한다.
    @pre: data for replace
    @post: 해당하는 리스트의 데이터가 교체된다.
    */
    int Replace(T& data);

    /*
    @bried: 리스트의 상태를 초기화한다.
    @pre: none
    @post: 데이터를 제외한 리스트의 상태를 초기화한다.
    */
    void ResetList();

    /*
    @bried: 다음 데이터를 반환한다.
    @pre: none
    @post: 포인터의 다음에 해당하는 데이터를 reference로 반환한다.
    */
    int GetNextItem(T& data);

    void operator=(SingleLinkedList& data) {
        // 기존 노드 초기화
        MakeEmpty();

        data.ResetList();
        // obj 리스트가 존재할 경우
        if (data.GetLength())
        {
            // obj curPtr 초기화

            T item;
            //노드 복사
            while (data.GetNextItem(item) != -1)
                Add(item);
        }
    }
};

template<typename T>
void SingleLinkedList<T>::MakeEmpty() {
    Node<T>* tempPtr;

    while (head != nullptr)
    {
        tempPtr = head;
        head = head->next;
        delete tempPtr;
    }

    size = 0;
}

template<typename T>
bool SingleLinkedList<T>::IsEmpty() {
    if (size == 0) {
        return true;
    }
    else {
        return false;
    }
}

template<typename T>
int SingleLinkedList<T>::GetLength() const {
    return size;
}

template<typename T>
int SingleLinkedList<T>::Add(const T& data) {
    // 리스트 초기화
    ResetList();

    // 리스트에 추가할 새로운 node 객체와 이전 노드를 가리킬 포인터 선언
    Node<T>* node = new Node<T>;
    Node<T>* pre;
    T dummy;
    bool bFound = false;

    // node 객체에 입력받은 데이터 설정 및 초기화
    node->value = data;
    node->next = nullptr;

    // list 에 node 가 존재하지 않는 경우
    if (!size)
    {
        head = node;
    }
    // list 에 node 가 하나 이상 존재하는 경우
    else
    {
        // 가장 마지막 node 로 이동 후 삽입
        while (1)
        {
            // 이전 노드를 가리키는 포인터 갱신
            pre = curPointer;

            // iteration 을 이용해 node 포인터 갱신.
            GetNextItem(dummy);

            if (curPointer->value > node->value)
            {
                if (pre == nullptr)
                {
                    node->next = head;
                    head = node;
                    break;
                }	//넣을 자리 앞 원소가 존재하지 않을 때 첫번째 원소로 삽입.
                node->next = curPointer;
                pre->next = node;
                break;
            }	//지금 가리키는 원소의 data값이 node의 data값보다 클 경우 pre 뒷자리에 삽입.

            // node 포인터가 마지막 node 를 가리키면 그 뒤에 새로운 node 삽입.
            if (curPointer->next == nullptr)
            {
                // 마지막 node 와 새로운 node 연결
                curPointer->next = node;
                break;
            }
        }
    }

    size++;

    return 1;
}

template<typename T>
int SingleLinkedList<T>::Delete(T& data) {
    bool moreToSearch, found;
    Node<T>* pre = nullptr;	//변수 선언

    curPointer = head;
    found = false;
    moreToSearch = (curPointer != nullptr);	//변수 초기화

    while (moreToSearch && !found)	//리스트의 끝이 아니면서 아직 찾지 않았으면 반복한다.
    {
        if (data == curPointer->value)	//현재 가리키는 원소의 값과 item의 값이 일치할 때
        {
            found = true;	//찾았으므로 found 값 변경
            if (pre == nullptr)
                head = curPointer->next;	//항목 이전에 다른 원소가 없을 때 항목의 다음 원소를 첫번째 원소로 한다.
            else
            {
                pre->next = curPointer->next;
                delete curPointer;
            }	//이전의 원소의 다음 원소를 '가리키는 항목의 다음 원소'로 바꾼다.
            size--;	//리스트의 길이를 1 줄여준다.
        }
        else
        {
            pre = curPointer;
            curPointer = curPointer->next;
            moreToSearch = (curPointer != nullptr);
        }	//일치하지 않을 때 다음 원소를 가리킨다. 단, pre는 지금의 원소를 가리킨다.
    }

    if (found)
        return 1;
    else
        return 0;	//삭제가 성공하면 1, 아니면 0을 리턴한다.
}

template<typename T>
int SingleLinkedList<T>::Get(T& data) {
    bool moreToSearch, found;
    Node<T>* location;	//변수 선언

    location = head;
    found = false;
    moreToSearch = (location != nullptr);	//변수 초기화

    while (moreToSearch && !found)	//리스트의 끝이 아니면서 아직 찾지 않았으면 반복한다.
    {
        if (data == location->value)
        {
            found = true;
            data = location->value;
        }	//일치하는 항목을 찾았을 때 found의 값을 변경해주고 item에 해당 항목을 복사해준다.
        else
        {
            location = location->next;
            moreToSearch = (location != nullptr);
        }	//찾지 못했을 때 다음 항목으로 location을 옮기고 그 값이 nullptr이면 리스트의 끝이므로 moreToSearch의 값을 변경해준다.
    }

    if (found)
        return 1;
    else
        return 0;	//찾으면 1, 그렇지 못하면 0을 리턴한다.
}

template<typename T>
int SingleLinkedList<T>::Replace(T& data) {
    bool moreToSearch, found;
    Node<T>* location;	//변수 선언

    location = head;
    found = false;
    moreToSearch = (location != nullptr);	//변수 초기화

    while (moreToSearch && !found)	//리스트의 끝이 아니면서 아직 찾지 않았으면 반복한다.
    {
        if (data == location->value)
        {
            found = true;
            location->value = data;
        }	//일치하는 항목을 찾았을 때 found의 값을 변경해주고 리스트의 항목에 item을 복사해준다.
        else
        {
            location = location->next;
            moreToSearch = (location != nullptr);
        }	//찾지 못했을 때 다음 항목으로 location을 옮기고 그 값이 nullptr이면 리스트의 끝이므로 moreToSearch의 값을 변경해준다.
    }

    if (found)
        return 1;
    else
        return 0;	//수정에 성공하면 1, 그렇지 못하면 0을 리턴한다.
}

template<typename T>
void SingleLinkedList<T>::ResetList() {
    curPointer = nullptr;
    curIndex = -1;
}

template<typename T>
int SingleLinkedList<T>::GetNextItem(T& data) {
    // current pointer 이 nullptr이라면 처음 node를 가리킴.
    if (IsEmpty()) {
        return -1;
    }

    if (curIndex == size - 1) {
        return -1;
    }

    if (curPointer == nullptr)
    {
        curPointer = head;
        data = curPointer->value;
        curIndex = 0;
        return 0;
    }
    else {
        //current position 을 다음 노드로 이동
        curPointer = curPointer->next;
        curIndex = curIndex + 1;
    }
    //item 에 current position 의 info 를 삽입
    data = curPointer->value;
    return curIndex;
}

#endif // !1
