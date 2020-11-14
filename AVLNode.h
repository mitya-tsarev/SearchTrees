#ifndef TREEPROJECT_AVLNODE_H
#define TREEPROJECT_AVLNODE_H

#include "ABSNode.h"

template<typename T>
class AVLNode : public ABSNode<T> {
private:
    int height = 0;
    AVLNode *left = nullptr;
    AVLNode *right = nullptr;


public:

    explicit AVLNode(T value);

    //~AVLNode();

    AVLNode *getRight();

    AVLNode *getLeft();

    T getValue();

    template<typename TT>
    friend
    class AVLTree;
};


/*template<typename T>
AVLNode<T>::~AVLNode(){
    delete right;
    delete left;
}*/

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
