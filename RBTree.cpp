#include "SearchTree.cpp"
#include "RBNode.cpp"

template<typename T>
class RBTree : public SearchTree<T> {
private:
    RBNode<T> *root = nullptr;
public:
    RBTree<T>() = default;

    bool find(T value) {
        return (root == nullptr ? false : root->find(value));
    }

    void erase(T value) {

    }

    void insert(T value) {
        if (root == nullptr) root = new RBNode<T>(value);
        else root->insert(value);
    }
};
