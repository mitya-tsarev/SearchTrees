#include <iostream>


template <typename T> class ABSNode
{
protected:
    T value;
    virtual ABSNode* getLeft() = 0;
    virtual ABSNode* getRight() = 0;
public:
    explicit ABSNode (T value) {
        this-> value = value;
    }
};

template <typename T> class ABSTree
{
private:
    ABSNode<T>* root;
public:
    virtual void insert (T value) = 0;
    virtual void erase (T value) = 0;
    virtual void find (T value) = 0;
};

template <typename T> class RBNode : public ABSNode<T> {
private:

};


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}