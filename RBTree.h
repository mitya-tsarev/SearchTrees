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
};


template<typename T>
RBTree<T>::RBTree() = default;

template<typename T>
RBNode<T> *RBTree<T>::getRoot() {
    return root;
}

template<typename T>
void RBTree<T>::insert(T value) {
    if (root == nullptr) {
        root = new RBNode<T>(value, false, nullptr);
        return; // inserted first node
    }
    RBNode<T> *new_root = root->basicInsert(value)->insertionRebalance();
    if (new_root != nullptr) root = new_root;
}

template<typename T>
void RBTree<T>::erase(T value) {
    //TODO
}

#endif //TREEPROJECT_RBTREE_H
