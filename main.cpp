#include "RBTree.h"
#include "AVLTree.h"
#include "Profiler.cpp"

int main() {
    AVLTree<int> avl = AVLTree<int>();
    avl.insert(15);
    avl.erase(15);
    avl.insert(400);
    avl.insert(239);
    avl.insert(1);
    std::cout << "Searching AVL tree: \n239: " << (avl.find(239) ? "Yes" : "No") << "\n40: " << (avl.find(40) ? "Yes" : "No") << '\n';
    RBTree<int> rb = RBTree<int>();
    rb.insert(2);
    rb.insert(3);
    rb.insert(179);
    rb.insert(1);
    std::cout << "Searching RB tree: \n179: " << (rb.find(179) ? "Yes" : "No") << "\n40: " << (rb.find(40) ? "Yes" : "No") << '\n';
    return 0;
}