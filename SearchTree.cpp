#include "ABSNode.cpp"

template<typename T>
class SearchTree {
public:
    virtual ABSNode<T> *getRoot() = 0;

    virtual void erase(T value) = 0;

    //TODO create basic insert if possible

    virtual void insert(T value) = 0;

    bool find(T value) {
        return (getRoot() == nullptr ? false : getRoot()->find(value));
    }
};
