#ifndef TREEPROJECT_RBTREE_H
#define TREEPROJECT_RBTREE_H

#include "SearchTree.h"
#include "RBNode.h"

template<typename T>
class RBTree : public SearchTree<T> {
private:
    RBNode<T> *root = nullptr;

    void destroyRecursive(RBNode<T> *p);

    void leftRotate(RBNode<T> *x);

    void rightRotate(RBNode<T> *x);

    RBNode<T> *successor(RBNode<T> *x);

    RBNode<T> *BSTreplace(RBNode<T> *x);

    void deleteNode(RBNode<T> *v);

    void fixDoubleBlack(RBNode<T> *x);

    RBNode<T> * search(T val);

    void swapValues(RBNode<T> *u, RBNode<T> *v);

public:
    RBTree<T>();

    RBNode<T> *getRoot();

    ~RBTree();

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
void RBTree<T>::destroyRecursive(RBNode<T> *p){
    if(p != nullptr){
        destroyRecursive(p->right);
        destroyRecursive(p->left);
        delete p;
    }
}

template<typename T>
RBTree<T>::~RBTree(){
    destroyRecursive(this->root);
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
RBNode<T> *RBTree<T>::BSTreplace(RBNode<T> *x) {
    // when node have 2 children
    if (x->left != nullptr and x->right != nullptr)
        return successor(x->right);

    // when leaf
    if (x->left == nullptr and x->right == nullptr)
        return nullptr;

    // when single child
    if (x->left != nullptr)
        return x->left;
    else
        return x->right;
}

template <typename T>
void RBTree<T>::leftRotate(RBNode<T> *x) {
    RBNode<T> *nParent = x->right;

    // update root if current node is root
    if (x == root) root = nParent;

    x->moveDown(nParent);

    // connect x with new parent's left element
    x->right = nParent->left;
    // connect new parent's left element with node
    // if it is not null
    if (nParent->left != nullptr)
        nParent->left->parent = x;

    // connect new parent with x
    nParent->left = x;
}

template <typename T>
void RBTree<T>::rightRotate(RBNode<T> *x) {
    // new parent will be node's left child
    RBNode<T> *nParent = x->left;

    // update root if current node is root
    if (x == root) root = nParent;

    x->moveDown(nParent);

    // connect x with new parent's right element
    x->left = nParent->right;
    // connect new parent's right element with node
    // if it is not null
    if (nParent->right != nullptr)
        nParent->right->parent = x;

    // connect new parent with x
    nParent->right = x;
}

template <typename T>
RBNode<T> * RBTree<T>::successor(RBNode<T> *x) {
    RBNode<T> *temp = x;

    while (temp->left != nullptr) temp = temp->left;

    return temp;
}

template <typename T>
void RBTree<T>::deleteNode(RBNode<T> *v) {
    RBNode<T> *u = BSTreplace(v);

    // True when u and v are both black
    bool uvBlack = ((u == nullptr or !u->red) and !v->red);
    RBNode<T> *parent = v->parent;

    if (u == nullptr) {
        // u is NULL therefore v is leaf
        if (v == root) {
            // v is root, making root null
            root = nullptr;
        } else {
            if (uvBlack) {
                // u and v both black
                // v is leaf, fix double black at v
                fixDoubleBlack(v);
            } else {
                // u or v is red
                if (v->getSibling() != nullptr)
                    // sibling is not null, make it red"
                    v->getSibling()->red;
            }

            // delete v from the tree
            if (v->isOnLeft()) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        }
        delete v;
        return;
    }

    if (v->left == nullptr or v->right == nullptr) {
        // v has 1 child
        if (v == root) {
            // v is root, assign the value of u to v, and delete u
            v->value = u->value;
            v->left = v->right = nullptr;
            delete u;
        } else {
            // Detach v from tree and move u up
            if (v->isOnLeft()) {
                parent->left = u;
            } else {
                parent->right = u;
            }
            delete v;
            u->parent = parent;
            if (uvBlack) {
                // u and v both black, fix double black at u
                fixDoubleBlack(u);
            } else {
                // u or v red, color u black
                u->red = false;
            }
        }
        return;
    }

    // v has 2 children, swap values with successor and recurse
    swapValues(u, v);
    deleteNode(u);
}

template <typename T>
void RBTree<T>::swapValues(RBNode<T> *u, RBNode<T> *v) {
    T temp;
    temp = u->value;
    u->value = v->value;
    v->value = temp;
}

template <typename T>
void RBTree<T>::fixDoubleBlack(RBNode<T> *x) {
    if (x == root) return;

    RBNode<T> *sibling = x->getSibling(), *parent = x->parent;
    if (sibling == nullptr) {
        // No sibiling, double black pushed up
        fixDoubleBlack(parent);
    } else {
        if (sibling->red) {
            // Sibling red
            parent->red = true;
            sibling->red = false;
            if (sibling->isOnLeft()) {
                // left case
                rightRotate(parent);
            } else {
                // right case
                leftRotate(parent);
            }
            fixDoubleBlack(x);
        } else {
            // Sibling black
            if (sibling->hasRedChild()) {
                // at least 1 red children
                if (sibling->left != nullptr && sibling->left->red) {
                    if (sibling->isOnLeft()) {
                        // left left
                        sibling->left->red = sibling->red;
                        sibling->red = parent->red;
                        rightRotate(parent);
                    } else {
                        // right left
                        sibling->left->red = parent->red;
                        rightRotate(sibling);
                        leftRotate(parent);
                    }
                } else {
                    if (sibling->isOnLeft()) {
                        // left right
                        sibling->right->red = parent->red;
                        leftRotate(sibling);
                        rightRotate(parent);
                    } else {
                        // right right
                        sibling->right->red = sibling->red;
                        sibling->red = parent->red;
                        leftRotate(parent);
                    }
                }
                parent->red = false;
            } else {
                // 2 black children
                sibling->red = true;
                if (!parent->red)
                    fixDoubleBlack(parent);
                else
                    parent->red = false;
            }
        }
    }
}

template<typename T>
RBNode<T> * RBTree<T>::search(T val) {
    RBNode<T> *temp = root;
    while (temp != nullptr) {
        if (val < temp->value) {
            if (temp->left == nullptr)
                break;
            else
                temp = temp->left;
        } else if (val == temp->value) {
            break;
        } else {
            if (temp->right == nullptr)
                break;
            else
                temp = temp->right;
        }
    }

    return temp;
}

template<typename T>
void RBTree<T>::erase(T value) {
    if (root == nullptr) return;

    RBNode<T> *v = search(value); // been u

    if (v->value != value) return;
    deleteNode(v);
}

#endif //TREEPROJECT_RBTREE_H