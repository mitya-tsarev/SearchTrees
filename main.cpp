#include "RBTree.h"
#include "AVLTree.h"
#include "Profiler.cpp"

int main() {
    RBTree<int> rb = RBTree<int>();
    rb.insert(5);
    rb.insert(3);
    rb.insert(179);
    rb.insert(1);
    rb.erase(179);
    std::cout << "Searching RB tree: \n179: " << (rb.find(179) ? "Yes" : "No") << "\n3: " << (rb.find(3) ? "Yes" : "No") << '\n';

    return 0;
}