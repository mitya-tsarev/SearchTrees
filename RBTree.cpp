#include "SearchTree.cpp"
#include "RBNode.cpp"

template<typename T>
class RBTree : public SearchTree<T> {
private:
    RBNode<T> *root = nullptr;
public:
    RBTree<T>() = default;

    RBNode<T> *getRoot() {
        return root;
    }

    void insert(T value) {
        if (root == nullptr) root = new RBNode<T>(value);
        else root->insert(value);
        //TODO use result of insert to rebalance
    }

    void erase(T value) {
        //TODO
    }

    void rebalance(RBNode<T>* node) {
        //TODO
    }
};
