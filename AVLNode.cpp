#include "abs_node.cpp"

template <class T> class node : public abs_node<T>{
public:
    int height;
    node* left;
    node* right;

    node(T k) : abs_node<T>(k){
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};
