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

    RBNode<T> *getGrandfather();

    RBNode<T> *getUncle();

    RBNode<T> *recolor();

    RBNode<T> *llRotation();

    RBNode<T> *lrRotation();

    RBNode<T> *rlRotation();

    RBNode<T> *rrRotation();

public:
    explicit RBNode(T value);

    RBNode(T value, bool red, RBNode<T> *parent);

    RBNode *getRight();

    RBNode *getLeft();

    RBNode *basicInsert(T val);

    RBNode<T> *insertionRebalance();

    template<typename TT>
    friend
    class RBTree;
};


template<typename T>
RBNode<T>::RBNode(T value, bool red, RBNode<T> *parent) : ABSNode<T>(value) {
    this->red = red;
    this->parent = parent;
}

template<typename T>
RBNode<T>::RBNode(T value) : ABSNode<T>(value) {}

template<typename T>
RBNode<T> *RBNode<T>::recolor() {
    red = !red;
    return this;
}

template<typename T>
RBNode<T> *RBNode<T>::getSibling() {
    if (parent == nullptr) return nullptr;
    return (parent->value > this->value) ? parent->right : parent->left;
}

template<typename T>
RBNode<T> *RBNode<T>::getGrandfather() {
    if (parent == nullptr) return nullptr;
    return parent->parent;
}

template<typename T>
RBNode<T> *RBNode<T>::getUncle() {
    if (parent == nullptr) return nullptr;
    return parent->getSibling();
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
RBNode<T> *RBNode<T>::basicInsert(T val) {
    if (this->value == val) return this;
    if (this->value > val) {
        if (left == nullptr) {
            left = new RBNode<T>(val, true, this);
            return left;
        }
        return left->basicInsert(val);
    }
    if (right == nullptr) {
        right = new RBNode<T>(val, true, this);
        return right;
    }
    return right->basicInsert(val);
}

template<typename T>
RBNode<T> *RBNode<T>::llRotation() {
    RBNode *p = parent;
    RBNode *g = getGrandfather();
    RBNode *gg = g->parent;
    g->parent = p;
    g->left = p->right;
    if (p->right != nullptr) p->right->parent = g;
    p->right = g;
    p->parent = gg;
    if (gg != nullptr) {
        if (g->value < gg->value) gg->left = p;
        else gg->right = p;
    }
    g->recolor();
    p->recolor();
    return (gg == nullptr ? p : nullptr);
}

template<typename T>
RBNode<T> *RBNode<T>::lrRotation() {
    RBNode *p = parent;
    RBNode *g = getGrandfather();
    RBNode *s = getSibling();
    if (left != nullptr) left->parent = p;
    if (right != nullptr) right->parent = p;
    if (p->left != nullptr) p->left->parent = this;
    p->left = left;
    p->right = right;
    p->parent = this;
    this->right = s;
    this->parent = g;
    g->left = this;
    return p->llRotation();
}

template<typename T>
RBNode<T> *RBNode<T>::rlRotation() {
    RBNode *p = parent;
    RBNode *g = getGrandfather();
    if (right != nullptr) right->parent = p;
    p->left = right;
    right = p;
    p->parent = this;
    parent = g;
    g->right = this;
    return p->rrRotation();
}

template<typename T>
RBNode<T> *RBNode<T>::rrRotation() {
    RBNode *p = parent;
    RBNode *g = getGrandfather();
    RBNode *gg = g->parent;
    g->parent = p;
    g->right = p->left;
    if (p->left != nullptr) p->left->parent = g;
    p->left = g;
    p->parent = gg;
    if (gg != nullptr) {
        if (g->value < gg->value) gg->left = p;
        else gg->right = p;
    }
    g->recolor();
    p->recolor();
    return (gg == nullptr ? p : nullptr);
}

template<typename T>
RBNode<T> *RBNode<T>::insertionRebalance() { // return new root, nullptr if didn't change
    if (parent == nullptr) {
        red = false;
        return this; // this is root, color set to black
    }
    if (!parent->red) return nullptr; // parent is black, tree is ok
    RBNode<T> *uncle = getUncle();
    if (uncle != nullptr && uncle->red) {
        parent->recolor();
        uncle->recolor();
        return getGrandfather()->recolor()->insertionRebalance(); // uncle was red, recolored and rebalanced grandfather
    }
    bool firstL = (getGrandfather()->value > parent->value); // grandfather should not be nullptr
    bool secondL = (parent->value > this->value);
    if (firstL) return (secondL ? llRotation() : lrRotation());
    else return (secondL ? rlRotation() : rrRotation());
}


#endif //TREEPROJECT_RBNODE_H
