
template<typename T>
class RBNode : public ABSNode<T> {
private:
    bool color = false; // false for black, true for red
    RBNode *left = nullptr;
    RBNode *right = nullptr;
    RBNode *parent = nullptr;
public:
    explicit RBNode(T value) : ABSNode<T>(value) {}

    RBNode *getRight() {
        return right;
    }

    RBNode *getLeft() {
        return left;
    }

    void insert(T value) { // TODO change return type to node*
        if (this->value == value) return;
        if (this->value > value) {
            if (left == nullptr) left = new RBNode<T>(value);
            else left -> insert(value);
            return;
        }
        if (right == nullptr) right = new RBNode<T>(value);
        else right -> insert(value);
    }
};
