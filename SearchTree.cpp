#include "ABSNode.cpp"

template<typename T>
class SearchTree {
private:
    ABSNode<T> *root;
public:
    virtual void insert(T value) = 0;

    virtual void erase(T value) = 0;

    virtual bool find(T value) = 0;
};
