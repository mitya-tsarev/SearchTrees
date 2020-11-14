#ifndef TREEPROJECT_RBNODE_H
#define TREEPROJECT_RBNODE_H

#include "ABSNode.h"

template<typename T>
class RBNode : public ABSNode<T> {
private:
    bool red = true; // false for black, true for red
    RBNode<T> *left = nullptr;
    RBNode<T> *right = nullptr;
    RBNode<T> *parent = nullptr;

    RBNode<T> *getSibling();

public:
    explicit RBNode(T value);

    RBNode(T value, bool red, RBNode<T> *parent);

    RBNode *getRight();

    RBNode *getLeft();

    RBNode *insert(T val);
};


template<typename T>
RBNode<T>::RBNode(T value, bool red, RBNode<T> *parent) : ABSNode<T>(value) {
    this->red = red;
    this->parent = parent;
}

template<typename T>
RBNode<T>::RBNode(T value) : ABSNode<T>(value) {}

template<typename T>
RBNode<T> *RBNode<T>::getSibling() {
    if (parent == nullptr) return nullptr;
    return (parent->value > this->value) ? parent->right : parent->left;
}

template<typename T>
RBNode<T> *RBNode<T>::getRight() {
    return right;
}

template<typename T>
RBNode<T> *RBNode<T>::getLeft() {
    return left;
}

template<typename T>
RBNode<T> *RBNode<T>::insert(T val) {
    if (this->value == val) return this;
    if (this->value > val) {
        if (left == nullptr) {
            left = new RBNode<T>(val, true, this);
            return left;
        }
        return left->insert(val);
    }
    if (right == nullptr) {
        right = new RBNode<T>(val, true, this);
        return right;
    }
    return right->insert(val);
}

#endif //TREEPROJECT_RBNODE_H
