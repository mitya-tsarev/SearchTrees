#include "SearchTree.cpp"
#include "RBNode.cpp"

template<typename T>
class RBTree : public SearchTree<T> {
private:
    RBNode<T> *root = nullptr;
public:
    RBTree<T>() = default;

    RBNode<T>* getRoot() {
        return root;
    }

    void erase(T value) {

    }

    void insert(T value) {
        if (root == nullptr) root = new RBNode<T>(value);
        else root->insert(value);
    }
};
