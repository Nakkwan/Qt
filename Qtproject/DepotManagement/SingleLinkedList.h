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
    @bried: ����Ʈ�� ����ְ� �����.
    @pre: none
    @post: List is empty
    */
    void MakeEmpty();

    /*
    @bried: ����Ʈ�� ������� Ȯ��
    @pre: none
    @post: none
    @return: ����Ʈ�� ������� 1, �ƴϸ� 0�� return ��
    */
    bool IsEmpty();

    /*
    @bried: ����Ʈ�� ���̸� ��ȯ�Ѵ�.
    @pre: none
    @post: none
    */
    int GetLength() const;

    /*
    @bried: ����Ʈ�� ���� �߰��Ѵ�.
    @pre: set data
    @post: ����Ʈ�� ���� ũ�⿡ �°� �߰��ȴ�.
    */
    int Add(const T& data);

    /*
    @bried: delete data from list
    @pre: set data for delete
    @post: ����Ʈ���� �ش� �����Ͱ� �����ǰ� �� ���� reference�� ��ȯ�Ѵ�.
    */
    int Delete(T& data);

    /*
    @bried: ����Ʈ���� data�� ã�´�.
    @pre: set data for find data
    @post: �ش��ϴ� �����Ͱ� reference�� ��ȯ�ȴ�.
    */
    int Get(T& data);

    /*
    @bried: ����Ʈ�� ������ ���� ��ü�Ѵ�.
    @pre: data for replace
    @post: �ش��ϴ� ����Ʈ�� �����Ͱ� ��ü�ȴ�.
    */
    int Replace(T& data);

    /*
    @bried: ����Ʈ�� ���¸� �ʱ�ȭ�Ѵ�.
    @pre: none
    @post: �����͸� ������ ����Ʈ�� ���¸� �ʱ�ȭ�Ѵ�.
    */
    void ResetList();

    /*
    @bried: ���� �����͸� ��ȯ�Ѵ�.
    @pre: none
    @post: �������� ������ �ش��ϴ� �����͸� reference�� ��ȯ�Ѵ�.
    */
    int GetNextItem(T& data);

    void operator=(SingleLinkedList& data) {
        // ���� ��� �ʱ�ȭ
        MakeEmpty();

        data.ResetList();
        // obj ����Ʈ�� ������ ���
        if (data.GetLength())
        {
            // obj curPtr �ʱ�ȭ

            T item;
            //��� ����
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
    // ����Ʈ �ʱ�ȭ
    ResetList();

    // ����Ʈ�� �߰��� ���ο� node ��ü�� ���� ��带 ����ų ������ ����
    Node<T>* node = new Node<T>;
    Node<T>* pre;
    T dummy;
    bool bFound = false;

    // node ��ü�� �Է¹��� ������ ���� �� �ʱ�ȭ
    node->value = data;
    node->next = nullptr;

    // list �� node �� �������� �ʴ� ���
    if (!size)
    {
        head = node;
    }
    // list �� node �� �ϳ� �̻� �����ϴ� ���
    else
    {
        // ���� ������ node �� �̵� �� ����
        while (1)
        {
            // ���� ��带 ����Ű�� ������ ����
            pre = curPointer;

            // iteration �� �̿��� node ������ ����.
            GetNextItem(dummy);

            if (curPointer->value > node->value)
            {
                if (pre == nullptr)
                {
                    node->next = head;
                    head = node;
                    break;
                }	//���� �ڸ� �� ���Ұ� �������� ���� �� ù��° ���ҷ� ����.
                node->next = curPointer;
                pre->next = node;
                break;
            }	//���� ����Ű�� ������ data���� node�� data������ Ŭ ��� pre ���ڸ��� ����.

            // node �����Ͱ� ������ node �� ����Ű�� �� �ڿ� ���ο� node ����.
            if (curPointer->next == nullptr)
            {
                // ������ node �� ���ο� node ����
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
    Node<T>* pre = nullptr;	//���� ����

    curPointer = head;
    found = false;
    moreToSearch = (curPointer != nullptr);	//���� �ʱ�ȭ

    while (moreToSearch && !found)	//����Ʈ�� ���� �ƴϸ鼭 ���� ã�� �ʾ����� �ݺ��Ѵ�.
    {
        if (data == curPointer->value)	//���� ����Ű�� ������ ���� item�� ���� ��ġ�� ��
        {
            found = true;	//ã�����Ƿ� found �� ����
            if (pre == nullptr)
                head = curPointer->next;	//�׸� ������ �ٸ� ���Ұ� ���� �� �׸��� ���� ���Ҹ� ù��° ���ҷ� �Ѵ�.
            else
            {
                pre->next = curPointer->next;
                delete curPointer;
            }	//������ ������ ���� ���Ҹ� '����Ű�� �׸��� ���� ����'�� �ٲ۴�.
            size--;	//����Ʈ�� ���̸� 1 �ٿ��ش�.
        }
        else
        {
            pre = curPointer;
            curPointer = curPointer->next;
            moreToSearch = (curPointer != nullptr);
        }	//��ġ���� ���� �� ���� ���Ҹ� ����Ų��. ��, pre�� ������ ���Ҹ� ����Ų��.
    }

    if (found)
        return 1;
    else
        return 0;	//������ �����ϸ� 1, �ƴϸ� 0�� �����Ѵ�.
}

template<typename T>
int SingleLinkedList<T>::Get(T& data) {
    bool moreToSearch, found;
    Node<T>* location;	//���� ����

    location = head;
    found = false;
    moreToSearch = (location != nullptr);	//���� �ʱ�ȭ

    while (moreToSearch && !found)	//����Ʈ�� ���� �ƴϸ鼭 ���� ã�� �ʾ����� �ݺ��Ѵ�.
    {
        if (data == location->value)
        {
            found = true;
            data = location->value;
        }	//��ġ�ϴ� �׸��� ã���� �� found�� ���� �������ְ� item�� �ش� �׸��� �������ش�.
        else
        {
            location = location->next;
            moreToSearch = (location != nullptr);
        }	//ã�� ������ �� ���� �׸����� location�� �ű�� �� ���� nullptr�̸� ����Ʈ�� ���̹Ƿ� moreToSearch�� ���� �������ش�.
    }

    if (found)
        return 1;
    else
        return 0;	//ã���� 1, �׷��� ���ϸ� 0�� �����Ѵ�.
}

template<typename T>
int SingleLinkedList<T>::Replace(T& data) {
    bool moreToSearch, found;
    Node<T>* location;	//���� ����

    location = head;
    found = false;
    moreToSearch = (location != nullptr);	//���� �ʱ�ȭ

    while (moreToSearch && !found)	//����Ʈ�� ���� �ƴϸ鼭 ���� ã�� �ʾ����� �ݺ��Ѵ�.
    {
        if (data == location->value)
        {
            found = true;
            location->value = data;
        }	//��ġ�ϴ� �׸��� ã���� �� found�� ���� �������ְ� ����Ʈ�� �׸� item�� �������ش�.
        else
        {
            location = location->next;
            moreToSearch = (location != nullptr);
        }	//ã�� ������ �� ���� �׸����� location�� �ű�� �� ���� nullptr�̸� ����Ʈ�� ���̹Ƿ� moreToSearch�� ���� �������ش�.
    }

    if (found)
        return 1;
    else
        return 0;	//������ �����ϸ� 1, �׷��� ���ϸ� 0�� �����Ѵ�.
}

template<typename T>
void SingleLinkedList<T>::ResetList() {
    curPointer = nullptr;
    curIndex = -1;
}

template<typename T>
int SingleLinkedList<T>::GetNextItem(T& data) {
    // current pointer �� nullptr�̶�� ó�� node�� ����Ŵ.
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
        //current position �� ���� ���� �̵�
        curPointer = curPointer->next;
        curIndex = curIndex + 1;
    }
    //item �� current position �� info �� ����
    data = curPointer->value;
    return curIndex;
}

#endif // !1
