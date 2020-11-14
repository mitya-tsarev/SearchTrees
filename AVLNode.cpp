#include "abs_node.cpp"

template <class T> class AVLNode : public abs_node<T>{
public:
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode *getRight() {
        return right;
    }

    AVLNode *getLeft() {
        return left;
    }

    explicit AVLNode(T k) : abs_node<T>(k){
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};
