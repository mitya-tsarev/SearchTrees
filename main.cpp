#include "RBTree.h"
#include "AVLTree.h"
#include "Profiler.cpp"

int main() {
    auto *rb = new RBTree<int>();
    long long k = 1;
    for (int i = 0; i < 10000000 + 19; ++i) {
        rb -> insert(k);
        k += 3000017;
        k %= (10000000 + 19);
    }
    delete rb;
    return 0;
}