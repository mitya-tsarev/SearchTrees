#include <iostream>
#ifndef TREEPROJECT_ABSNODE_H
#define TREEPROJECT_ABSNODE_H
#define nullptr NULL

template<typename T>
class ABSNode {
protected:
    T value;

    virtual ABSNode *getLeft() = 0;

    virtual ABSNode *getRight() = 0;

public:
    explicit ABSNode(T value);

    bool find(T val);

    ~ABSNode() = default;
};


template<typename T>
ABSNode<T>::ABSNode(T value) {
    this->value = value;
}

template<typename T>
bool ABSNode<T>::find(T val) {
    if (value == val) return true;
    if (value > val) return (getLeft() == nullptr ? false : getLeft()->find(val));
    return (getRight() == nullptr ? false : getRight()->find(val));
}

#endif //TREEPROJECT_ABSNODE_H
