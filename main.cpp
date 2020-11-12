#include <iostream>
#include "AVL.cpp"
#include "RBTree.cpp"

int main() {
    AVL_tree<int> tree = AVL_tree<int>();
    tree.insert(239);
    tree.insert(15);
    tree.insert(238);
    tree.insert(37);
    tree.insert(40);
    tree.insert(32);
    std::cout << tree.find(239) << tree.find(4087) << tree.find(3);
    return 0;
}