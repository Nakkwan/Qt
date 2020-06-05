#pragma once
#include <fstream>

enum class OrderType { INORDER, PREORDER, POSTORDER };			//검색 방법

template<typename T>
class LinkedQueue;

template <typename T>
struct BinaryNode {
	T data;
	BinaryNode* left;
	BinaryNode* right;
};

template <typename T>
class BinarySearchTree {
private:
	BinaryNode<T>* root;
	LinkedQueue<T> queue;
public:
	BinarySearchTree();
	~BinarySearchTree() {}

	/*
	@brief: tree가 비었는지 확인
	@pre: none
	@post: none
	@return: tree가 비었으면 true, 아니면 false
	*/
	bool IsEmpty();

	/*
	@brief: tree에 더 item을 추가할수 있는지 확인
	@pre: none
	@post: none
	@return: 추가가 가능하면 true, 아니면 false
	*/
	bool IsFull();

	/*
	@brief: tree를 비움
	@pre: none
	@post: tree가 비워짐
	*/
	void MakeEmpty();

	/*
	@brief: node의 개수를 측정
	@pre: none
	@post: none
	@return: node의 개수가 return
	*/
	int GetLength();

	/*
	@brief: tree에 node를 추가
	@pre: set Item
	@post: item is added to tree
	*/
	void Insert(T& value);

	/*
	@brief: tree에서 item 삭제
	@pre: 해당 item이 존재해야함
	@post: item is deleted
	*/
	void Delete(T& data);

	/*
	@brief: tree의 node의 정보를 갱신
	@pre: none
	@post: 해당 node의 정보가 갱신되고, 갱신여부를 reference로 반환(bool)
	*/
	void Replace(T& data, bool& found);

	/*
	@brief: tree에서 item을 찾음
	@pre: none
	@post: 해당 node의 정보를 찾고, 검색여부를 reference로 반환(bool)
	*/
	void Retrieve(T& data, bool& found);

	/*
	@brief: tree의 item을 탐색 방법에 따라 print
	@pre: none
	@post: node들이 print됨
	*/
	void PrintTree(std::ostream& out, OrderType type) const;

	/*
	@brief: 탐색 방법에 따라 treequeue를 갱신
	@pre: none
	@post: queue에 node의 정보가 담기게 됨
	*/
	void ResetTree(OrderType type);

	/*
	@brief: 다음 노드를 반환함
	@pre: set Queue
	@post: 탐색 방법에 따라 저장 되었던 queue에서 다음 node를 반환 받음. 마지막 노드인지 reference로 반환(bool) 
	*/
	void GetNextItem(T& value, bool& finished);
};

template<typename T>
BinarySearchTree<T>::BinarySearchTree() {
	root = nullptr;
}

template<typename T>
bool BinarySearchTree<T>::IsEmpty()
{
	if (root == nullptr) {
		return true;
	}
	return false;
}

template<typename T>
bool BinarySearchTree<T>::IsFull()
{
    BinaryNode<T>* room;
	try
	{
        room = new BinaryNode<T>;
		delete room;
		return false;
	}
	catch (std::bad_alloc exception)
	{
		return true;
	}
}

template<typename T>
void BinarySearchTree<T>::MakeEmpty()
{
	MakeEmptyTree(root);
}

template<typename T>
int BinarySearchTree<T>::GetLength()
{
	return CountNode(root);
}

template<typename T>
void BinarySearchTree<T>::Insert(T& value)
{
	InsertNode(root, value);
}

template<typename T>
void BinarySearchTree<T>::Delete(T& data)
{
	BinaryDelete(root, data);
}

template<typename T>
void BinarySearchTree<T>::Replace(T& data, bool& found)
{
	ReplaceNode(root, data, found);
}

template<typename T>
void BinarySearchTree<T>::Retrieve(T& data, bool& found)
{
	RetrieveNode(root, data, found);
}

template<typename T>
void BinarySearchTree<T>::PrintTree(std::ostream& out, OrderType type) const
{
	if (type == OrderType::INORDER) {
		PrintInorder(root, out);
	}
	else if (type == OrderType::PREORDER) {
		PrintPreorder(root, out);
	}
	else if (type == OrderType::POSTORDER) {
		PrintPostorder(root, out);
	}
}

template<typename T>
int CountNode(BinaryNode<T>* root)
{
	if (root == nullptr) {
		return 0;
	}
	else {
		return CountNode(root->left) + CountNode(root->right) + 1;
	}
}

template <typename T>
void InsertNode(BinaryNode<T>*& root, T& value) {
	if (root == nullptr) {
		root = new BinaryNode<T>;
		root->data = value;
		root->right = nullptr;
		root->left = nullptr;
	}
	else if (root->data < value) {
		InsertNode(root->right, value);
	}
	else if (root->data > value) {
		InsertNode(root->left, value);
	}
}

template<typename T>
void GetPreNode(BinaryNode<T>* root, T& value) {
	while (root->right != nullptr)
		root = root->right;
	value = root->data;
}

template<typename T>
void DeleteNode(BinaryNode<T>*& root) {
	T value;
	BinaryNode<T>* temp = root;

	if (root->right == nullptr) {
		root = root->left;
		delete temp;
	}
	else if (root->left == nullptr) {
		root = root->right;
		delete temp;
	}
	else {
		GetPreNode(root->left, value);
		root->data = value;
		BinaryDelete(root->left, value);
	}

}

template <typename T>
void BinaryDelete(BinaryNode<T>*& root, T& value) {
	if (root->data > value) {
		BinaryDelete(root->left, value);
	}
	else if (root->data < value) {
		BinaryDelete(root->right, value);
	}
	else {
		DeleteNode(root);
	}
}

template <typename T>
void ReplaceNode(BinaryNode<T>*& root, T& value, bool& result) {
	if (root == nullptr) {
		result = false;
	}
	else if (root->data > value) {
		RetrieveNode(root->left, value, result);
	}
	else if (root->data < value) {
		RetrieveNode(root->right, value, result);
	}
	else {
		root->data = value;
		result = true;
	}
}

template <typename T>
void RetrieveNode(BinaryNode<T>* root, T& value, bool& result) {
	if (root == nullptr) {
		result = false;
	}
	else if (root->data > value) {
		RetrieveNode(root->left, value, result);
	}
	else if (root->data < value) {
		RetrieveNode(root->right, value, result);
	}
	else {
		value = root->data;
		result = true;
	}
}

template <typename T>
void PrintInorder(BinaryNode<T>* root, std::ostream& out) {
	if (root != nullptr) {
		PrintInorder(root->left, out);
		out << root->data;
		PrintInorder(root->right, out);
	}
}

template <typename T>
void PrintPreorder(BinaryNode<T>* root, std::ostream& out) {
	if (root != nullptr) {
		out << root->data;
		PrintPreorder(root->left, out);
		PrintPreorder(root->right, out);
	}
}

template <typename T>
void PrintPostorder(BinaryNode<T>* root, std::ostream& out) {
	if (root != nullptr) {
		PrintPostorder(root->left, out);
		PrintPostorder(root->right, out);
		out << root->data;
	}
}

template<typename T>
void InorderQueue(BinaryNode<T>* root, LinkedQueue<T>& q) {
	if (root != nullptr) {
		InorderQueue(root->left, q);
		q.Enqueue(root->data);
		InorderQueue(root->right, q);
	}
}

template<typename T>
void PreorderQueue(BinaryNode<T>* root, LinkedQueue<T>& q) {
	if (root != nullptr) {
		q.Enqueue(root->data);
		PreorderQueue(root->left, q);
		PreorderQueue(root->right, q);
	}
}

template<typename T>
void PostorderQueue(BinaryNode<T>* root, LinkedQueue<T>& q) {
	if (root != nullptr) {
		PostorderQueue(root->left, q);
		PostorderQueue(root->right, q);
		q.Enqueue(root->data);
	}
}

template <typename T>
void BinarySearchTree<T>::ResetTree(OrderType type) {
	queue.MakeEmpty();
	if (type == OrderType::INORDER) {
		InorderQueue(root, queue);
	}
	else if (type == OrderType::PREORDER) {
		PreorderQueue(root, queue);
	}
	else if (type == OrderType::POSTORDER) {
		PostorderQueue(root, queue);
	}
}

template <typename T>
void BinarySearchTree<T>::GetNextItem(T& value, bool& finished) {
	if (!queue.IsEmpty()) {
		finished = false;
		queue.Dequeue(value);
		if (queue.IsEmpty()) {
			finished = true;
		}
	}
	else {
		finished = true;
	}
}

template<class T>
void MakeEmptyTree(BinaryNode<T>*& root)
{
	if (root != nullptr) {
		MakeEmptyTree(root->left);
		MakeEmptyTree(root->right);
		root = nullptr;
	}
}
