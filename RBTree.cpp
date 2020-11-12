#include "SearchTree.cpp"
#include "RBNode.cpp"

template<typename T>
class RBTree : public SearchTree<T> {
private:
    RBNode<T> *left = nullptr;
    RBNode<T> *right = nullptr;
public:
    RBNode<T> *getRight() {
        return right;
    }

    RBNode<T> *getLeft() {
        return left;
    }

    bool find(T value) {
        return true;
    }

    void erase(T value) {

    }

    void insert(T value) {

    }
};
