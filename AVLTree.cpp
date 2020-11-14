//#include "SearchTree.cpp"
#include "AVLNode.cpp"

template<typename T>
class AVLTree{  // : public SearchTree<T>
private:
    AVLNode<T> *root = nullptr;
public:
    AVLTree<T>() = default;

    AVLNode<T> *getRoot() {
        return root;
    }

    void insert(T value) {
        if (root == nullptr) root = new AVLNode<T>(value);
    }

    void erase(T value) {
        //TODO
    }
};
