#ifndef _DOUBLYSORTEDLINKEDLIST_H
#define _DOUBLYSORTEDLINKEDLIST_H

template<typename T>
class DoublyIterator;

/**
*	���Ḯ��Ʈ���� ���̴� NodeType�� ����ü
*/
template <typename T>
struct DoublyNode
{
	T data; ///< �� ����� ������.
	DoublyNode* prev; ///< ����� ���� ����Ű�� ������.
	DoublyNode* next; ///< ����� ������ ����Ű�� ������.
};

/**
*	���ĵ� �����Ḯ��Ʈ Ŭ����
*/
template <typename T>
class DoublySortedLinkedList
{
	friend class DoublyIterator<T>; ///< DoublyIterator�� ģ�� Ŭ����.
public:
	DoublySortedLinkedList();
	~DoublySortedLinkedList();

	/*
	@brief	����Ʈ�� ������� �ƴ��� �˻��Ѵ�.
	@pre	m_nLength�� ���� ������ �־�� �Ѵ�.
	@post	������� �ƴ����� �˷��ش�.
	@return	��������� true, �ƴϸ� false�� ��ȯ.
	*/
	bool IsEmpty();

	/*
	@brief	����Ʈ�� ����.
	@pre	����.
	@post	m_pFirst�� m_pLast�� ������ ��� �����͸� �����.
	*/
	void MakeEmpty();

	/*
	@brief	����Ʈ�� ���̸� ��ȯ�Ѵ�.
	@pre	����.
	@post	����Ʈ�� ���̸� ��ȯ.
	@return	m_nLength ����Ʈ�� ���� ��ȯ.
	*/
	int GetLength() const;

	/*
	@brief	���ο� �������� ����Ʈ�� �߰��Ѵ�.
	@pre	item�� �Է¹޴´�.
	@post	�������� ����Ʈ�� �߰��Ѵ�.
	@return	���� �������� ������ 0�� ��ȯ�ϰ�, �Է¿� �����ϸ� 1�� ��ȯ.
	*/
	int Add(T& item);

	/*
	@brief	�Է¹��� �������� ����Ʈ���� �����Ѵ�.
	@pre	item�� �Է¹޴´�.
	@post	�Է¹��� �������� ����Ʈ���� ã�� �����Ѵ�.
	*/
	int Delete(T& item);

	/*
	@brief	�Է¹��� ���������� ������ �ٲ۴�.
	@pre	item�� �Է¹޴´�.
	@post	���ο� ������ ��ü�ȴ�.
	*/
	int Replace(const T& item);

	/*
	@brief	�Է¹��� �������� ������ ���Ͽ� ���� ����Ʈ�� �������� �����´�.
	@pre	item�� �Է¹޴´�.
	@post	�˻��� �����͸� �����ۿ� �ִ´�.
	@return	��ġ�ϴ� �����͸� ã���� 1, �׷��� ������ 0�� ��ȯ.
	*/
	int Get(T& item);


private:
	DoublyNode<T>* m_pFirst; ///< �ּҰ��� ������ ����Ʈ�� �� ó��.
	DoublyNode<T>* m_pLast; ///< �ִ��� ������ ����Ʈ�� �� ��.
	int m_nLength; ///< ����Ʈ�� ����.
};

// ����Ʈ�� �� ó���� ���� ���θ� ����Ű�� �����ϰ� ����Ʈ�� ���̸� 0���� �ʱ�ȭ���ѳ��´�.
template <typename T>
DoublySortedLinkedList<T> ::DoublySortedLinkedList()
{
	m_pFirst = new DoublyNode<T>;
	m_pLast = new DoublyNode<T>;

	m_pFirst->next = m_pLast; // ���� ó���� ���θ� ����Ű�� �ʱ�ȭ.
	m_pFirst->prev = NULL; // ó��.

	m_pLast->next = NULL; // ��.
	m_pLast->prev = m_pFirst; // ���� ó���� ���θ� ����Ű�� �ʱ�ȭ.

	m_nLength = 0; // ���̴� 0.
}

// �Ҹ���.
template <typename T>
DoublySortedLinkedList<T>::~DoublySortedLinkedList()
{
	MakeEmpty();
	delete m_pFirst;
	delete m_pLast;
}

// ����Ʈ�� ������� �˻��Ѵ�.
template <typename T>
bool DoublySortedLinkedList<T>::IsEmpty()
{
	if (m_nLength == 0)
		return true;
	else
		return false;
}

// ����Ʈ�� ����.
template <typename T>
void DoublySortedLinkedList<T>::MakeEmpty()
{
	DoublyNode<T>* pItem;
	DoublyIterator<T> itor(*this);
	itor.Next(); // �������� �̵�.

	while (itor.NextNotNull())
	{
		pItem = itor.m_pCurPointer;
		itor.Next(); // ���� �����͸� �������� �̵�.
		delete pItem;
	}

	m_pFirst->next = m_pLast;
	m_pFirst->prev = NULL;
	m_pLast->prev = m_pFirst;
	m_pLast->next = NULL;

	return;
}

// ����Ʈ�� ���̸� ��ȯ�Ѵ�.
template <typename T>
int DoublySortedLinkedList<T>::GetLength() const
{
	return m_nLength;
}

// �������� �Է¹޾� ����Ʈ�� �´� �ڸ��� ã�� �����Ѵ�.
template <typename T>
int DoublySortedLinkedList<T>::Add(T& item)
{
	DoublyIterator<T> itor(*this);
	itor.Next(); // �������� �̵�.

	if (IsEmpty()) // ó�� ������ ��
	{
		DoublyNode<T>* pItem = new DoublyNode<T>;
		pItem->data = item;
		m_pFirst->next = pItem;
		pItem->prev = m_pFirst;
		pItem->next = m_pLast;
		m_pLast->prev = pItem; // ó���� �� ���̿� ����.
		m_nLength++;
		return 1;
	}
	else // ó���� �ƴ� ��
	{
		while (1)
		{
			if (item < itor.m_pCurPointer->data || !itor.NextNotNull()) // �´� �ڸ��� ã�´�. //�����������ƴ���
			{
				DoublyNode<T>* pItem = new DoublyNode<T>;
				pItem->data = item;
				pItem->prev = itor.m_pCurPointer->prev;
				pItem->next = itor.m_pCurPointer;
				itor.m_pCurPointer->prev->next = pItem;
				itor.m_pCurPointer->prev = pItem; // �������� ����.
				m_nLength++;
				return 1;
			}
			else if (item == itor.m_pCurPointer->data) // ���� ������ �������� ������
				return 0; // 0�� ��ȯ.
			else
				itor.Next(); // �������� �̵�.
		}
	}
}

// �Է¹��� �������� �����Ϳ��� ã�Ƴ��� �����Ѵ�.
template <typename T>
int DoublySortedLinkedList<T>::Delete(T& item)
{
	DoublyIterator<T> itor(*this);
	itor.Next(); // �������� �̵�.

	while (itor.m_pCurPointer != m_pLast)
	{
		if (itor.m_pCurPointer->data == item) // ��ġ�ϴ� �����͸� ã�´�.
		{
			DoublyNode<T>* pItem = new DoublyNode<T>;
			pItem = itor.m_pCurPointer;
			itor.Next();
			pItem->prev->next = itor.m_pCurPointer;
			itor.m_pCurPointer->prev = pItem->prev; // �����ϴ� ����� �հ� �ڸ� ���� �̾��ش�.
			delete pItem; // ����.
			m_nLength--; // ���� ����.
			return 1;
		}
		else
			itor.Next();
	}
	return 0;
}

// �Է¹��� �������� ������ ��ü�Ѵ�.
template <typename T>
int DoublySortedLinkedList<T>::Replace(const T& item)
{
	DoublyIterator<T> itor(*this);
	itor.Next(); // �������� �̵�.

	while (itor.m_pCurPointer != m_pLast)
	{
		if (itor.m_pCurPointer->data == item)
		{
			itor.m_pCurPointer->data = item; // ������ ��ü.
			return 1;
		}
		else
			itor.Next();
	}

	return 0;
}

// �Է¹��� �����۰� ��ġ�ϴ� �������� ����Ʈ���� ã�� �����´�.
template <typename T>
int DoublySortedLinkedList<T>::Get(T& item)
{
	DoublyIterator<T> itor(*this);
	itor.Next();

	while (itor.m_pCurPointer != m_pLast)
	{
		if (itor.m_pCurPointer->data == item)
		{
			item = itor.m_pCurPointer->data;
			return 1; // ��ġ�ϸ� 1�� ��ȯ.
		}
		else
			itor.Next(); // �������� �̵�.
	}

	return 0; // ��ġ���� ������ 0�� ��ȯ.
}

#endif