#include "ABSNode.cpp"

template <class T> class AVLNode : public ABSNode<T>{
public:
    int height;
    AVLNode* left;
    AVLNode* right;

    explicit AVLNode(T k) : ABSNode<T>(k){
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};
