#ifndef TREEPROJECT_RBTREE_H
#define TREEPROJECT_RBTREE_H

#include "SearchTree.h"
#include "RBNode.h"

template<typename T>
class RBTree : public SearchTree<T> {
private:
    RBNode<T> *root = nullptr;

    void deleteFix(RBNode<T> *x);

    void leftRotate(RBNode<T>* x);

    void rightRotate(RBNode<T>* x);

    void rbTransplant(RBNode<T>* u, RBNode<T>* v);

    void deleteNodeHelper(RBNode<T>* node, T key);

    RBNode<T>* minimum(RBNode<T>* node);

    void destroyRecursive(RBNode<T> *p);
    
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
void RBTree<T>::erase(T value) {
    deleteNodeHelper(this->root, value);
}

template<typename T>
void RBTree<T>::leftRotate(RBNode<T>* x) {
    RBNode<T>* y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

template<typename T>
void RBTree<T>::rightRotate(RBNode<T> *x) {
    RBNode<T> *y = x->left;
    x->left = y->right;
    if (y->right != nullptr) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

template<typename T>
void RBTree<T>::deleteFix(RBNode<T> *x){
    RBNode<T> *s;
    if (x == nullptr) return;
    while (x != root && !(x->red)) {
        if (x == x->parent->left) {
            s = x->getSibling();
            if (s->red) {
                s->red = false;
                x->parent->red = true;
                leftRotate(x->parent);
                s = x->parent->right;
            }

            if (!(s->left->red) && !(s->right->red)) {
                s->red = true;
                x = x->parent;
            } else {
                if (!(s->right->red)) {
                    s->left->red = false;
                    s->red = true;
                    rightRotate(s);
                    s = x->parent->right;
                }

                s->red = x->parent->red;
                x->parent->red = false;
                s->right->red = false;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            s = x->parent->left;
            if (s->red) {
                s->red = false;
                x->parent->red = true;
                rightRotate(x->parent);
                s = x->parent->left;
            }

            if (!(s->right->red) && !(s->left->red)) {
                s->red = true;
                x = x->parent;
            } else {
                if (! s->left->red) {
                    s->right->red = false;
                    s->red = true;
                    leftRotate(s);
                    s = x->parent->left;
                }

                s->red = x->parent->red;
                x->parent->red = false;
                s->left->red = false;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->red = false;
}

template<typename T>
void RBTree<T>::rbTransplant(RBNode<T>* u, RBNode<T>* v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nullptr) v->parent = u->parent;
}

template<typename T>
void RBTree<T>::deleteNodeHelper(RBNode<T>* node, T key) {
    RBNode<T>* z = nullptr;
    RBNode<T>* x = nullptr;
    RBNode<T>* y = nullptr;
    while (node != nullptr) {
        if (node->value == key) {
            z = node;
        }

        if (node->value <= key) {
            node = node->right;
        } else {
            node = node->left;
        }
    }

    if (z == nullptr) return;

    y = z;
    bool y_original_color = y->red;
    if (z->left == nullptr) {
        x = z->right;
        rbTransplant(z, z->right);
    } else if (z->right == nullptr) {
        x = z->left;
        rbTransplant(z, z->left);
    } else {
        y = minimum(z->right);
        y_original_color = y->red;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            rbTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        rbTransplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->red = z->red;
    }
    delete z;
    if (! y_original_color) {
        deleteFix(x);
    }
}

template <typename T>
RBNode<T>* RBTree<T>::minimum(RBNode<T>* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

#endif //TREEPROJECT_RBTREE_H