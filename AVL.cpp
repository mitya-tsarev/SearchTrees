#include <set>
#include <iostream>
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


template <class T> class AVL_tree{
private:
    node<T>* root;

    int height(node<T>* p){
        return (p != nullptr) ? p->height : 0;
    }

    int b_factor(node<T>* p){
        return height(p->right) - height(p->left);
    }

    void fix_height(node<T>* p){
        unsigned char hl = height(p->left);
        unsigned char hr = height(p->right);
        p->height = (hl > hr ? hl : hr) + 1;
    }

    node<T>* right_rotate(node<T>* p){
        node<T>* q = p->left;
        p->left = q->right;
        q->right = p;
        fix_height(p);
        fix_height(q);
        return q;
    }

    node<T>* left_rotate(node<T>* q){
        node<T>* p = q->right;
        q->right = p->left;
        p->left = q;
        fix_height(q);
        fix_height(p);
        return p;
    }

    node<T>* balance(node<T>* p){
        fix_height(p);
        if(b_factor(p) == 2){
            if(b_factor(p->right) < 0)
                p->right = right_rotate(p->right);
            node<T>* q = left_rotate(p);
            if(root == p) root = q;
            return q;
        }

        if(b_factor(p) == -2){
            if(b_factor(p->left) > 0)
                p->left = left_rotate(p->left);
            node<T>* q = right_rotate(p);
            if(root == p) root = q;
            return q;
        }
        return p;
    }

    node<T>* insert_node(node<T>* p, int k){
        if(p == nullptr) return new node<T>(k);
        if(k < (*p).get_value())
            p->left = insert_node(p->left, k);
        else
            p->right = insert_node(p->right, k);
        return balance(p);
    }

    node<T>* find_min(node<T>* p){
        return (p->left != nullptr) ? find_min(p->left) : p;
    }

    bool find_node(node<T>* p, int k){
        if((*p).get_value() == k) return true;
        if((*p).get_value() > k and p->left == nullptr) return false;
        else if((*p).get_value() > k and p->left != nullptr) return find_node(p->left, k);

        if((*p).get_value() < k and p->right == nullptr) return false;
        else if((*p).get_value() < k and p->right != nullptr) return find_node(p->right, k);
    }

    node<T>* remove_min(node<T>* p){
        if(p->left == nullptr) return p->right;
        p->left = remove_min(p->left);
        return balance(p);
    }

    node<T>* remove_node(node<T>* p, int k) {
        if(p == nullptr) return nullptr;
        if(k < (*p).get_value()) p->left = remove_node(p->left, k);
        else if(k > (*p).get_value()) p->right = remove_node(p->right, k);
        else{
            node<T>* q = p->left;
            node<T>* r = p->right;
            if(root == p) root = q;
            delete p;
            if(r == nullptr) {
                return q;
            }
            node<T>* min = find_min(r);
            min->right = remove_min(r);
            min->left = q;
            min = balance(min);
            if(root == q) root = min;
            return min;
        }
        node<T>* ret = balance(p);
        if(root == p) root = ret;
        return ret;
    }


public:
    AVL_tree(){
        root = nullptr;
    }
    AVL_tree(node<T>* root){
        this->root = root;
    }
    void insert(T k){
        if(root == nullptr){
            root = new node<T>(k);
        }else {
            if (k < (*root).get_value())
                root->left = insert_node(root->left, k);
            else
                root->right = insert_node(root->right, k);
        }
        balance(root);
    }
    void erase(T k){
        remove_node(root, k);
    }
    bool find(T k){
        return find_node(root, k);
    }
};


int main(){
    AVL_tree<int> tree = AVL_tree<int>();
    tree.insert(239);
    tree.insert(15);
    tree.insert(238);
    tree.insert(37);
    tree.insert(40);
    tree.insert(3);
    std::cout << tree.find(239) << tree.find(4087) << tree.find(3);

    return 0;
}
