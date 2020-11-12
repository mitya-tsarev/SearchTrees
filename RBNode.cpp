
template<typename T>
class RBNode : public ABSNode<T> {
private:
    RBNode *left = nullptr;
    RBNode *right = nullptr;
public:
    RBNode *getRight() {
        return right;
    }

    RBNode *getLeft() {
        return left;
    }
};
