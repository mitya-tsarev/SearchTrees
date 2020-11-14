#include "ABSNode.cpp"

template<typename T>
class AVLNode : public ABSNode<T> {
//private:

public:
    int height = 0;
    AVLNode *left = nullptr;
    AVLNode *right = nullptr;


    explicit AVLNode(T value) : ABSNode<T>(value) {
        height = 1;
    }

    AVLNode *getRight() {
        return right;
    }

    AVLNode *getLeft() {
        return left;
    }

    //friend class AVLTree;
};

template<typename T>
class SearchTree {
protected:
    virtual ABSNode<T> *getRoot() = 0;

public:

    virtual void erase(T value) = 0;

    //TODO create basic insert if possible

    virtual void insert(T value) = 0;

    bool find(T value) {
        return (getRoot() == nullptr ? false : getRoot()->find(value));
    }
};

