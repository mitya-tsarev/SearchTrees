#include "AVLNode.cpp"

template<class T>
class AVL_tree {
private:
    AVLNode<T> *root;

    int height(AVLNode<T> *p) {
        return (p != nullptr) ? p->height : 0;
    }

    int b_factor(AVLNode<T> *p) {
        return height(p->right) - height(p->left);
    }

    void fix_height(AVLNode<T> *p) {
        unsigned char hl = height(p->left);
        unsigned char hr = height(p->right);
        p->height = (hl > hr ? hl : hr) + 1;
    }

    AVLNode<T> *right_rotate(AVLNode<T> *p) {
        AVLNode<T> *q = p->left;
        p->left = q->right;
        q->right = p;
        fix_height(p);
        fix_height(q);
        return q;
    }

    AVLNode<T> *left_rotate(AVLNode<T> *q) {
        AVLNode<T> *p = q->right;
        q->right = p->left;
        p->left = q;
        fix_height(q);
        fix_height(p);
        return p;
    }

    AVLNode<T> *balance(AVLNode<T> *p) {
        fix_height(p);
        if (b_factor(p) == 2) {
            if (b_factor(p->right) < 0)
                p->right = right_rotate(p->right);
            AVLNode<T> *q = left_rotate(p);
            if (root == p) root = q;
            return q;
        }

        if (b_factor(p) == -2) {
            if (b_factor(p->left) > 0)
                p->left = left_rotate(p->left);
            AVLNode<T> *q = right_rotate(p);
            if (root == p) root = q;
            return q;
        }
        return p;
    }

    AVLNode<T> *insert_node(AVLNode<T> *p, int k) {
        if (p == nullptr) return new AVLNode<T>(k);
        if (k < (*p).get_value())
            p->left = insert_node(p->left, k);
        else
            p->right = insert_node(p->right, k);
        return balance(p);
    }

    AVLNode<T> *find_min(AVLNode<T> *p) {
        return (p->left != nullptr) ? find_min(p->left) : p;
    }

    bool find_node(AVLNode<T> *p, int k) {
        if ((*p).get_value() == k) return true;
        if ((*p).get_value() > k and p->left == nullptr) return false;
        else if ((*p).get_value() > k and p->left != nullptr) return find_node(p->left, k);

        if ((*p).get_value() < k and p->right == nullptr) return false;
        return find_node(p->right, k);
    }

    AVLNode<T> *remove_min(AVLNode<T> *p) {
        if (p->left == nullptr) return p->right;
        p->left = remove_min(p->left);
        return balance(p);
    }

    AVLNode<T> *remove_node(AVLNode<T> *p, int k) {
        if (p == nullptr) return nullptr;
        if (k < (*p).get_value()) p->left = remove_node(p->left, k);
        else if (k > (*p).get_value()) p->right = remove_node(p->right, k);
        else {
            AVLNode<T> *q = p->left;
            AVLNode<T> *r = p->right;
            if (root == p) root = q;
            delete p;
            if (r == nullptr) {
                return q;
            }
            AVLNode<T> *min = find_min(r);
            min->right = remove_min(r);
            min->left = q;
            min = balance(min);
            if (root == q) root = min;
            return min;
        }
        AVLNode<T> *ret = balance(p);
        if (root == p) root = ret;
        return ret;
    }


public:
    AVL_tree() {
        root = nullptr;
    }

    explicit AVL_tree(AVLNode<T> *root) {
        this->root = root;
    }

    void insert(T k) {
        if (root == nullptr) {
            root = new AVLNode<T>(k);
        } else {
            if (k < (*root).get_value())
                root->left = insert_node(root->left, k);
            else
                root->right = insert_node(root->right, k);
        }
        balance(root);
    }

    void erase(T k) {
        remove_node(root, k);
    }

    bool find(T k) {
        return find_node(root, k);
    }
};
