#ifndef SORTEDLINKEDLIST_H
#define SORTEDLINKEDLIST_H

template<typename T>
class SortedIterator;

//Node struct for Link
template <typename T>
struct SortedNode
{
	T value; 
	SortedNode* prev; 
	SortedNode* next; 
};

//SortedLinkedList
template <typename T>
class SortedLinkedList {
	friend class SortedIterator<T>; 

private:
	SortedNode<T>* first; 
	SortedNode<T>* last; 
	int length; 

public:
	SortedLinkedList();
	~SortedLinkedList();

    /*
     * @brief: check if List is Empty
     * @pre: none
     * @post: none
     * @return: if List is empty, return 1, otherwise return 0
    */
	bool IsEmpty();

    /*
     * @brief: Make List Empty
     * @pre: none
     * @post: List Emptyed
    */
	void MakeEmpty();

    /*
     * @brief: Get Length of List
     * @pre: none
     * @post: none
     * @return: Return Length of List(int)
    */
	int GetLength() const;

    /*
     * @brief: Add Data in List
     * @pre: set data for add
     * @post: data is added in List
     * @return: return 1 if success to add, otherwise, return 0
    */
	int Add(T& item);

    /*
     * @brief: Delete Data in List
     * @pre: set data for Delete
     * @post: data delete in List
     * @return: return 1 if success to delete, otherwise, return 0
    */
	int Delete(T& item);

    /*
     * @brief: Replace Data of List
     * @pre: set data for Replace
     * @post: data is Replaced
     * @return: return 1 if success to Replace, otherwise, return 0
    */
	int Replace(const T& item);

    /*
     * @brief: Get data from List
     * @pre: data is already exist
     * @post: return data by reference
     * @return: return 1 if success to Get data, otherwise, return 0
    */
	int Get(T& item);

};

template <typename T>
SortedLinkedList<T> ::SortedLinkedList()            //constructor
{
	first = new SortedNode<T>;
	last = new SortedNode<T>;

	first->next = last;
	first->prev = nullptr; 

	last->next = nullptr;
	last->prev = first; 

	length = 0;
}

template <typename T>
SortedLinkedList<T>::~SortedLinkedList()            //destructor
{
	MakeEmpty();
	delete first;
	delete last;
}

template <typename T>
bool SortedLinkedList<T>::IsEmpty()                 //check if List is Empty
{
	if (length == 0)
		return true;
	else
		return false;
}

template <typename T>
void SortedLinkedList<T>::MakeEmpty()               //Make List Empty
{
	SortedNode<T>* temp;
	SortedIterator<T> itor(*this);
	itor.Next(); 

	while (itor.NextNotNull())
	{
		temp = itor.s_pointer;
		itor.Next();
		delete temp;
	}

	first->next = last;
	first->prev = nullptr;
	last->prev = first;
	last->next = nullptr;

	return;
}


template <typename T>
int SortedLinkedList<T>::GetLength() const {                //Return Length of List
	return length;
}


template <typename T>
int SortedLinkedList<T>::Add(T& data)                       //Add data in List
{
	SortedIterator<T> itor(*this);
	itor.Next();

	if (IsEmpty()) {
		SortedNode<T>* temp = new SortedNode<T>;
		temp->value = data;
		first->next = temp;
		temp->prev = first;
		temp->next = last;
		last->prev = temp;
		length++;
		return 1;
	}
	else {
		while (itor.NextNotNull()) {
			if (data < itor.s_pointer->value) {
				SortedNode<T>* temp = new SortedNode<T>;
				temp->value = data;
				temp->prev = itor.s_pointer->prev;
				temp->next = itor.s_pointer;
				itor.s_pointer->prev->next = temp;
				itor.s_pointer->prev = temp;
				length++;
				return 1;
			}
			itor.Next();
		}
		SortedNode<T>* temp = new SortedNode<T>;
		temp->value = data;
		temp->next = last;
		temp->prev = last->prev;
		temp->prev->next = temp;
		last->prev = temp;
		return 1;
	}
}


template <typename T>
int SortedLinkedList<T>::Delete(T& data)                        //Delete data in List
{
	SortedIterator<T> itor(*this);
	itor.Next(); 

	if (IsEmpty()) {
		return 0;
	}

	while (itor.NextNotNull()) {
		if (itor.s_pointer->value == data) {
			SortedNode<T>* temp = new SortedNode<T>;
			temp = itor.s_pointer;
			data = temp->value;
			itor.Next();
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			delete temp; 
			length--; 
			return 1;
		}
		else {
			itor.Next();
		}
	}
	return 0;
}

template <typename T>
int SortedLinkedList<T>::Replace(const T& data)                 //Replace data in List
{
	SortedIterator<T> itor(*this);
	itor.Next(); 

	while (itor.NextNotNull()) {
		if (itor.s_pointer->value == data) {
			itor.s_pointer->value = data;
			return 1;
		}	
		itor.Next();
	}

	return 0;
}


template <typename T>
int SortedLinkedList<T>::Get(T& data)                           //Get data in List by Reference
{
	SortedIterator<T> itor(*this);
	itor.Next();

	while (itor.NextNotNull()) {
		if (itor.s_pointer->value == data) {
			data = itor.s_pointer->value;
			return 1; 
		}
		itor.Next();
	}

	return 0; 
}

#endif
