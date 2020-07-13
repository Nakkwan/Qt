#ifndef BASE_H
#define BASE_H

#include "pch.h"


template<typename T>
class SortedList;

template<typename T>
class UnsortedList;

template<typename T>
class DoublySortedLinkedList;

template<typename T>
class AVLTree;

template<typename T>
class LinkedQueue;

class ItemType;

class FloorType;

class StorageType;

class Base
{
public:
    static ItemType * item;
    static AVLTree<ItemType> MasterList;
    static DoublySortedLinkedList<StorageType> StorageList;
};

#endif // BASE_H
