#ifndef TREEPROJECT_AVLTREE_H
#define TREEPROJECT_AVLTREE_H

#include "AVLNode.h"
#include "SearchTree.h"

template<typename T>
class AVLTree : public SearchTree<T> {
private:
    AVLNode<T> *root = nullptr;

    AVLNode<T> *getRoot();

    void destroyRecursive(AVLNode<T> *p);

    int height(AVLNode<T> *p);

    int bFactor(AVLNode<T> *p);

    void fixHeight(AVLNode<T> *p);

    AVLNode<T> *rightRotate(AVLNode<T> *p);

    AVLNode<T> *leftRotate(AVLNode<T> *q);

    AVLNode<T> *balance(AVLNode<T> *p);

    AVLNode<T> *insertNode(AVLNode<T> *p, int k);

    AVLNode<T> *findMin(AVLNode<T> *p);

    AVLNode<T> *removeMin(AVLNode<T> *p);

    AVLNode<T> *removeNode(AVLNode<T> *p, int k);

public:
    AVLTree();

    ~AVLTree();

    void insert(T k);

    void erase(T k);

};


template<typename T>
AVLNode<T> *AVLTree<T>::getRoot() {
    return this->root;
}

template<typename T>
int AVLTree<T>::height(AVLNode<T> *p) {
    return (p != nullptr) ? p->height : 0;
}

template<typename T>
int AVLTree<T>::bFactor(AVLNode<T> *p) {
    return height(p->right) - height(p->left);
}

template<typename T>
void AVLTree<T>::fixHeight(AVLNode<T> *p) {
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

template<typename T>
void AVLTree<T>::destroyRecursive(AVLNode<T> *p){
    if(p != nullptr){
        destroyRecursive(p->right);
        destroyRecursive(p->left);
    delete p;
    }
}

template<typename T>
AVLTree<T>::~AVLTree(){
    destroyRecursive(this->root);
}

template<typename T>
AVLNode<T> *AVLTree<T>::rightRotate(AVLNode<T> *p) {
    AVLNode<T> *q = p->left;
    p->left = q->right;
    q->right = p;
    fixHeight(p);
    fixHeight(q);
    return q;
}

template<typename T>
AVLNode<T> *AVLTree<T>::leftRotate(AVLNode<T> *q) {
    AVLNode<T> *p = q->right;
    q->right = p->left;
    p->left = q;
    fixHeight(q);
    fixHeight(p);
    return p;
}

template<typename T>
AVLNode<T> *AVLTree<T>::balance(AVLNode<T> *p) {
    fixHeight(p);
    if (bFactor(p) == 2) {
        if (bFactor(p->right) < 0)
            p->right = rightRotate(p->right);
        AVLNode<T> *q = leftRotate(p);
        if (root == p) root = q;
        return q;
    }

    if (bFactor(p) == -2) {
        if (bFactor(p->left) > 0)
            p->left = leftRotate(p->left);
        AVLNode<T> *q = rightRotate(p);
        if (root == p) root = q;
        return q;
    }
    return p;
}

template<typename T>
AVLNode<T> *AVLTree<T>::insertNode(AVLNode<T> *p, int k) {
    if (p == nullptr) return new AVLNode<T>(k);
    if (k < (*p).getValue())
        p->left = insertNode(p->left, k);
    else
        p->right = insertNode(p->right, k);
    return balance(p);
}


template<typename T>
AVLNode<T> *AVLTree<T>::findMin(AVLNode<T> *p) {
    return (p->left != nullptr) ? findMin(p->left) : p;
}

template<typename T>
AVLNode<T> *AVLTree<T>::removeMin(AVLNode<T> *p) {
    if (p->left == nullptr) return p->right;
    p->left = removeMin(p->left);
    return balance(p);
}

template<typename T>
AVLNode<T> *AVLTree<T>::removeNode(AVLNode<T> *p, int k) {
    if (p == nullptr) return nullptr;
    if (k < p->getValue()) p->left = removeNode(p->left, k);
    else if (k > p->getValue()) p->right = removeNode(p->right, k);
    else {
        AVLNode<T> *q = p->left;
        AVLNode<T> *r = p->right;
        if (root == p) root = q;
        delete p;
        if (r == nullptr) {
            return q;
        }
        AVLNode<T> *min = findMin(r);
        min->right = removeMin(r);
        min->left = q;
        min = balance(min);
        if (root == q) root = min;
        return min;
    }
    AVLNode<T> *ret = balance(p);
    if (root == p) root = ret;
    delete p;
    return ret;
}


template<typename T>
AVLTree<T>::AVLTree() = default;

template<typename T>
void AVLTree<T>::insert(T k) {
    if (root == nullptr) {
        root = new AVLNode<T>(k);
    } else {
        if (k < root->getValue())
            root->left = insertNode(root->left, k);
        else
            root->right = insertNode(root->right, k);
    }
    balance(root);
}

template<typename T>
void AVLTree<T>::erase(T k) {
    removeNode(root, k);
}


#endif //TREEPROJECT_AVLTREE_H
