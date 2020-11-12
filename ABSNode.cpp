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

    bool find(T val) {
        if (value == val) return true;
        if (value > val) return (getLeft() == nullptr ? false : getLeft()->find(val));
        return (getRight() == nullptr ? false : getRight()->find(val));
    }
};
