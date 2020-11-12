template<typename T>
class ABSNode {
protected:
    T value;

    virtual ABSNode *getLeft() = 0;

    virtual ABSNode *getRight() = 0;

public:
    explicit ABSNode(T value) {
        this->value = value;
    }
};
