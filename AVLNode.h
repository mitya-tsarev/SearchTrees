#ifndef TREEPROJECT_AVLNODE_H
#define TREEPROJECT_AVLNODE_H

#include "ABSNode.h"

template<typename T>
class AVLNode : public ABSNode<T> {
//private:

public:
    int height = 0;
    AVLNode *left = nullptr;
    AVLNode *right = nullptr;


    explicit AVLNode(T value);

    AVLNode *getRight();

    AVLNode *getLeft();


    T getValue();

    template<typename TT>
    friend
    class AVLTree;
};

template<typename T>
AVLNode<T>::AVLNode(T value) : ABSNode<T>(value) {
    height = 1;
}

template<typename T>
AVLNode<T> *AVLNode<T>::getRight() {
    return right;
}

template<typename T>
AVLNode<T> *AVLNode<T>::getLeft() {
    return left;
}

template<typename T>
T AVLNode<T>::getValue() {
    return this->value;
}


#endif //TREEPROJECT_AVLNODE_H
