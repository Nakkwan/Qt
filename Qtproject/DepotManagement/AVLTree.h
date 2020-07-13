#ifndef AVLTREE_H
#define AVLTREE_H

template<typename T>
class LinkedQueue;

template<typename T>
struct AVLnode{
   int height;
   T* data;
   AVLnode *left;
   AVLnode *right;
   AVLnode(){
       left= nullptr;
       right = nullptr;
       height = 0;
   }
   AVLnode(int h){
       height = h;
   }
};

template<typename T>
class AVLTree{
private:
    AVLnode<T> *root;
    LinkedQueue<T> queue;
public:
    AVLTree(){
        root = nullptr;
    }
    ~AVLTree();

    /*
    @brief: Insert Item in Tree
    @pre: none
    @post: Item is added to tree
    @return: if success to add return 1, otherwise return 0
    */
    int Insert(T*& value);

    /*
    @brief: Delete item in Tree
    @pre: none
    @post: Item is deleted
    @return: if success to Delete return 1, otherwise return 0
    */
    int Delete(T*& value);

    /*
    @brief: Retrieve item in tree
    @pre: none
    @post: item is return by reference
    @return: if success to Retrieve return 1, otherwise return 0
    */
    int Retrieve(T*& value);

    /*
    @brief: replace item in tree
    @pre: none
    @post: item is replaced
    @return: if success to add return 1, otherwise return 0
    */
    int Replace(T* value);

    /*
    @brief: check whether tree is empty
    @pre: none
    @post: none
    @return: if tree is empty, return 1, otherwise return 0;
    */
    bool IsEmpty();

    /*
    @brief: check whether tree is Full
    @pre: none
    @post: none
    @return: if tree is full, return 1, otherwise return 0;
    */
    bool ISFull();

    /*
    @brief: make tree empty
    @pre: none
    @post: make tree empty
    */
    void MakeEmpty();

    /*
    @brief: get height of tree
    @pre: none
    @post: none
    @return: height of tree
    */
    int GetHeight();

    /*
    @brief: get length of tree
    @pre: none
    @post: none
    @return: get number of node in tree
    */
    int GetLength();

    /*
    @brief: Reset tree for GetNextItem
    @pre: none
    @post: All node is add to tree by inorder
    */
    void ResetTree();

    /*
    @brief: Get next item of tree
    @pre: ResetTree by ResetTree function
    @post: GetNext item of tree
    */
    void GetNextItem(T*& value, bool& finished);
};

template<typename T>
AVLTree<T>::~AVLTree(){
    MakeEmpty();
}

template<typename T>
int AVLTree<T>::Insert(T*& value){
    bool result;
    root = InsertNode(root, value, result);
    if(result == true){
        return 1;
    }else {
        return 0;
    }
}

template<typename T>
int AVLTree<T>::Delete(T*& value){
    bool result;
    root = DeleteNode(root, value, result);
    if(result == true){
        return 1;
    }else {
        return 0;
    }
}

template<typename T>
int AVLTree<T>::Retrieve(T*& value){
    bool result;
    RetrieveNode(root, value, result);
    if(result == true){
        return 1;
    }else {
        return 0;
    }
}

template<typename T>
int AVLTree<T>::Replace(T* value){
    bool result;
    ReplaceNode(root, value, result);
    if(result == true){
        return 1;
    }else {
        return 0;
    }
}

template<typename T>
bool AVLTree<T>::IsEmpty(){
    if (root == nullptr) {
        return true;
    }
    return false;
}

template<typename T>
bool AVLTree<T>::ISFull(){
    AVLnode<T>* room;
    try
    {
        room = new AVLnode<T>;
        delete room;
        return false;
    }
    catch (std::bad_alloc exception)
    {
        return true;
    }
}

template<typename T>
void AVLTree<T>::MakeEmpty(){
    MakeEmptyTree(root);
}

template<typename T>
int AVLTree<T>::GetLength(){
    return CountNode(root);
}


template<typename T>
int AVLTree<T>::GetHeight(){
    return Height(root);
}

template<typename T>
int Height(AVLnode<T>* node){
    if(node == nullptr){
        return -1;
    }else{
        return node->height;
    }
}

template<typename T>
void AVLTree<T>::ResetTree(){
    queue.MakeEmpty();
    Reset(root, queue);
}

template<typename T>
void Reset(AVLnode<T>* root, LinkedQueue<T>& q){
    if(root != nullptr){
        Reset(root->left, q);
        q.Enqueue(root->data);
        Reset(root->right, q);
    }
}


template<typename T>
void AVLTree<T>::GetNextItem(T*& value, bool& finished){
    if (!queue.IsEmpty()) {
        finished = false;
        queue.Dequeue(value);
    }
    else {
        finished = true;
    }
}


template<typename T>
AVLnode<T>* RotateLeft(AVLnode<T>*& node){
    AVLnode<T>* newroot = node->right;
    node->right = newroot->left;
    newroot->left = node;
    node->height = max(Height(node->left), Height(node->right)) + 1;
    newroot->height = max(Height(newroot->left), Height(newroot->right)) + 1;

    return newroot;
}

template<typename T>
AVLnode<T>* RotateRight(AVLnode<T>*& node){
    AVLnode<T>* newroot = node->left;
    node->left = newroot->right;
    newroot->right = node;
    node->height = max(Height(node->left), Height(node->right)) + 1;
    newroot->height = max(Height(newroot->left), Height(newroot->right)) + 1;

    return newroot;
}


template<typename T>
int GetBalance(AVLnode<T>*& root){
    if(root->left == nullptr){
        if(root->right == nullptr){
            return 0;
        }else{
            return -(root->right->height + 1);
        }
    }else if(root->right == nullptr){
        return root->left->height + 1;
    }else{
        return root->left->height - root->right->height;
    }
}

template <typename T>
AVLnode<T>* InsertNode(AVLnode<T>*& root, T*& value, bool& result) {
    if (root == nullptr) {
        AVLnode<T>* newnode = new AVLnode<T>;
        newnode->data = value;
        newnode->right = nullptr;
        newnode->left = nullptr;
        result = true;
        return newnode;
    }
    else if (*(root->data) < *value) {
        root->right = InsertNode(root->right, value, result);
    }
    else if (*(root->data) > *value) {
        root->left = InsertNode(root->left, value, result);
    } else {
        result = false;
    }

    if(result != false){
        root->height = max(Height(root->left), Height(root->right)) + 1;

        int balance = GetBalance(root);

        if(balance > 1){
            if(*value < *(root->left->data)){
                return RotateRight(root);
            }else{
                root->left = RotateLeft(root->left);
                return RotateRight(root);
            }
        }else if(balance < -1){
            if(*value > *(root->right->data)){
                return RotateLeft(root);
            }else{
                root->right = RotateRight(root->right);
                return RotateLeft(root);
            }
        }
    }
    return root;
}

template<typename T>
AVLnode<T>* DeleteNode(AVLnode<T>*& root, T* value, bool& result) {
    if(root == nullptr){
        result = false;
        return nullptr;
    }
    if (*(root->data) > *value) {
        root->left = DeleteNode(root->left, value, result);
    }
    else if (*(root->data) < *value) {
        root->right = DeleteNode(root->right, value, result);
    }
    else {
        if(root->left == nullptr){
            if(root->right == nullptr){
                delete root;
                root = nullptr;
                result = true;
            }else{
                AVLnode<T>* newroot = root->right;
                delete root;
                root = newroot;
            }
        }else if (root->right == nullptr){
            AVLnode<T>* newroot = root->left;
            delete root;
            root = newroot;
        }else{
            AVLnode<T>* right = root->right;
            while(right->left != nullptr){
                right = right->left;
            }
            root->data = right->data;
            root->right = DeleteNode(root->right, right->data, result);
        }
        result = true;
    }

    if(result != false){
        if(root == nullptr){
            return nullptr;
        }

        root->height = max(Height(root->left), Height(root->right)) + 1;

        int balance = GetBalance(root);

        if(balance > 1){
            if(*value < *(root->left->data)){
                return RotateRight(root);
            }else{
                root->left = RotateLeft(root->left);
                return RotateRight(root);
            }
        }else if(balance < -1){
            if(*value > *(root->right->data)){
                return RotateLeft(root);
            }else{
                root->right = RotateRight(root->right);
                return RotateLeft(root);
            }
        }
    }

    return root;
}

template<typename T>
void RetrieveNode(AVLnode<T>*& root, T*& value, bool& result) {
    if(root == nullptr){
        result = false;
    }
    if(*(root->data) == *value){
        value = root->data;
        result = true;
    }else if(*(root->data) > *value){
        RetrieveNode(root->left, value, result);
    }else if (*(root->data) < *value){
        RetrieveNode(root->right, value, result);
    }
}

template<typename T>
void ReplaceNode(AVLnode<T>*& root, T* value, bool& result) {
    if(root == nullptr){
        result = false;
    }
    if(*(root->data) == *value){
        *(root->data) = *value;
        result = true;
    }else if(*(root->data) > *value){
        ReplaceNode(root->left, value, result);
    }else if (*(root->data) < *value){
        ReplaceNode(root->right, value, result);
    }
}

template<class T>
void MakeEmptyTree(AVLnode<T>*& root)
{
    if (root != nullptr) {
        MakeEmptyTree(root->left);
        MakeEmptyTree(root->right);
        delete root;
    }
}

template<typename T>
int CountNode(AVLnode<T>* root)
{
    if (root == nullptr) {
        return 0;
    }
    else {
        return CountNode(root->left) + CountNode(root->right) + 1;
    }
}

#endif // AVLTREE_H
