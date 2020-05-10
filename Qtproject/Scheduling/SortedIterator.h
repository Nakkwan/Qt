#ifndef SORTEDITERATOR_H
#define SORTEDITERATOR_H

template<typename T>
struct SortedNode;
template<typename T>
class SortedLinkedList;

template <typename T>
class SortedIterator
{
    friend class SortedLinkedList<T>;
private:
    const SortedLinkedList<T>& s_List;
    SortedNode<T>* s_pointer;

public:
    SortedIterator(const SortedLinkedList<T>& list) : s_List(list), s_pointer(list.first) {};

    /*
     * @brief: check current pointer is null
     * @pre: none
     * @post: none
     * @return: return true if current pointer is not null, otherwise, return false
    */
    bool NotNull();

    /*
     * @brief: check next pointer is null
     * @pre: none
     * @post: none
     * @return: return true if next pointer is not null, otherwise, return false
    */
    bool NextNotNull();

    /*
     * @brief: Get value of Fist Node
     * @pre: Least one data is in List
     * @post: none
     * @return: value of first node is returned
    */
    T First();

    /*
     * @brief: Get value of Last Node
     * @pre: Least one data is in List
     * @post: none
     * @return: value of Last node is returned
    */
    T Last();

    /*
     * @brief: pointer point next node
     * @pre: none
     * @post: pointer pointer next node, and return value of node
     * @return: value of node
    */
    T Next();

    /*
     * @brief: Get Current Node
     * @pre: none
     * @post: none
    */
    SortedNode<T> GetCurrentNode();
};

template <typename T>
bool SortedIterator<T>::NotNull() {
    if (s_pointer == nullptr)
        return false;
    else
        return true;
}

template <typename T>
bool SortedIterator<T>::NextNotNull() {
    if (s_pointer->next == nullptr)
        return false;
    else
        return true;
}

template <typename T>
T SortedIterator<T>::First() {
    return s_List.first->next->value;
}

template <typename T>
T SortedIterator<T>::Last() {
    return s_List.last->prev->value;
}

template <typename T>
T SortedIterator<T>::Next() {
    s_pointer = s_pointer->next;
    return s_pointer->value;
}

template <typename T>
SortedNode<T> SortedIterator<T>::GetCurrentNode() {
    return *s_pointer;
}

#endif
