#pragma once
#include <fstream>

enum class OrderType { INORDER, PREORDER, POSTORDER };			//�˻� ���

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
	@brief: tree�� ������� Ȯ��
	@pre: none
	@post: none
	@return: tree�� ������� true, �ƴϸ� false
	*/
	bool IsEmpty();

	/*
	@brief: tree�� �� item�� �߰��Ҽ� �ִ��� Ȯ��
	@pre: none
	@post: none
	@return: �߰��� �����ϸ� true, �ƴϸ� false
	*/
	bool IsFull();

	/*
	@brief: tree�� ���
	@pre: none
	@post: tree�� �����
	*/
	void MakeEmpty();

	/*
	@brief: node�� ������ ����
	@pre: none
	@post: none
	@return: node�� ������ return
	*/
	int GetLength();

	/*
	@brief: tree�� node�� �߰�
	@pre: set Item
	@post: item is added to tree
	*/
	void Insert(T& value);

	/*
	@brief: tree���� item ����
	@pre: �ش� item�� �����ؾ���
	@post: item is deleted
	*/
	void Delete(T& data);

	/*
	@brief: tree�� node�� ������ ����
	@pre: none
	@post: �ش� node�� ������ ���ŵǰ�, ���ſ��θ� reference�� ��ȯ(bool)
	*/
	void Replace(T& data, bool& found);

	/*
	@brief: tree���� item�� ã��
	@pre: none
	@post: �ش� node�� ������ ã��, �˻����θ� reference�� ��ȯ(bool)
	*/
	void Retrieve(T& data, bool& found);

	/*
	@brief: tree�� item�� Ž�� ����� ���� print
	@pre: none
	@post: node���� print��
	*/
	void PrintTree(std::ostream& out, OrderType type) const;

	/*
	@brief: Ž�� ����� ���� treequeue�� ����
	@pre: none
	@post: queue�� node�� ������ ���� ��
	*/
	void ResetTree(OrderType type);

	/*
	@brief: ���� ��带 ��ȯ��
	@pre: set Queue
	@post: Ž�� ����� ���� ���� �Ǿ��� queue���� ���� node�� ��ȯ ����. ������ ������� reference�� ��ȯ(bool) 
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
