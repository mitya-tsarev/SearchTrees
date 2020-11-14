#ifndef TREEPROJECT_RBTREE_H
#define TREEPROJECT_RBTREE_H

#include "SearchTree.h"
#include "RBNode.h"

template<typename T>
class RBTree : public SearchTree<T> {
private:
    RBNode<T> *root = nullptr;
public:
    RBTree<T>();

    RBNode<T> *getRoot();

    void insert(T value);

    void erase(T value);

    void rebalance(RBNode<T> *node);
};


template<typename T>
RBTree<T>::RBTree() = default;

template<typename T>
RBNode<T> *RBTree<T>::getRoot() {
    return root;
}

template<typename T>
void RBTree<T>::insert(T value) {
    if (root == nullptr) root = new RBNode<T>(value, false, nullptr);
    rebalance(root->insert(value));
}

template<typename T>
void RBTree<T>::erase(T value) {
    //TODO
}

template<typename T>
void RBTree<T>::rebalance(RBNode<T> *node) {
    //TODO
}

#endif //TREEPROJECT_RBTREE_H
