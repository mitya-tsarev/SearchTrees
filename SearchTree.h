#ifndef TREEPROJECT_SEARCHTREE_H
#define TREEPROJECT_SEARCHTREE_H

#include "ABSNode.h"

template<typename T>
class SearchTree {
public:
    virtual ABSNode<T> *getRoot() = 0;

    virtual void erase(T value) = 0;

    virtual void insert(T value) = 0;

    bool find(T value);

    SearchTree() = default;

    ~SearchTree() = default;
};


template<typename T>
bool SearchTree<T>::find(T value) {
    return (getRoot() == nullptr ? false : getRoot()->find(value));
}

#endif //TREEPROJECT_SEARCHTREE_H
