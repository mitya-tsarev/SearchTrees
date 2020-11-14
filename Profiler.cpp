#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <string>
#include "AVLTree.h"
#include "RBTree.h"
#include <chrono>
#define nullptr NULL

typedef std::chrono::high_resolution_clock Clock;

using namespace std;

struct times { // struct containing number of nodes in the tree and average operation execution times for it
    int n;
    double timeinsert;
    double timefind;
    double timeerase;
};

template <typename T>
class Profiler{

private:

    string s;
    
    const int Ct = 1000000;

public:

    Profiler(std::string s1) {
        s = s1;
    }

    ~Profiler() {

    }

    vector<times> average(int x1, int x2, int y1, int y2, int nmult) {

        srand(time(0));

        double start, finish;

        if (s == "AVL_Tree") {
            AVLTree<T> tre = AVLTree<T>();
        } else if (s == "RB_Tree") {
            RBTree<T> tre = RBTree<T>();
        }


        int array_size; // number of nodes
        vector<times> plottimes; // vector where data will be stored
        times dot;
        int test;

        double timeinsertn = 0;
        double timefindn = 0;
        double timeerasen = 0;
        double timeinsert1 = 0;
        double timefind1 = 0;
        double timeerase1 = 0;
        double timeinsert2 = 0;
        double timefind2 = 0;
        double timeerase2 = 0;
        

        for (int i = 1; i <= y1; i++) { // search for average operation execution times for trees with different number of nodes (y1)
            array_size = i * nmult;
            timeinsertn = 0;
            timefindn = 0;
            timeerasen = 0;
            for (int k = 0; k < y2; k++) { // search for average operation execution times for different trees with the same number of nodes (y2)
                AVLTree<long long> tre = AVLTree<long long>(); // create new tree
                for (int j = 0; j < array_size; j++) {
                    tre.insert(((rand() % 10000) * 100000000 + (rand() % 10000) * 10000 + rand() % 10000) % (array_size * 100)); // add nodes with random values
                }
                timeinsert1 = 0;
                timefind1 = 0;
                timeerase1 = 0;
                for (int j = 0;
                     j < x1; j++) { // search for average operation execution times for different numbers (x1)
                    test = ((rand() % 10000) * 10000 + rand() % 10000) % (array_size * 100);
                    cout << test << endl;
                    timeinsert2 = 0;
                    timefind2 = 0;                    
                    timeerase2 = 0;
                    for (int l = 0; l < x2; l++) { // search for average operation execution times for the same number (x2)
						auto t1 = Clock::now();                      
                        tre.insert(test);
                        auto t2 = Clock::now();
                        timeinsert2 += chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
                        tre.erase(test);
                    }
                    for (int l = 0; l < x2; l++) { // search for average operation execution times for the same number (x2)                       
                        tre.insert(test);
                        auto t1 = Clock::now();
                        tre.find(test);
                        auto t2 = Clock::now();
                        timefind2 += chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
                        tre.erase(test);
                    }
                    for (int l = 0; l < x2; l++) { // search for average operation execution times for the same number (x2)                       
                        tre.insert(test);
                        auto t1 = Clock::now();
                        tre.erase(test);
                        auto t2 = Clock::now();
                        timeerase2 += chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
                    }
                    timeinsert2 = timeinsert2 / x2;
                    timefind2 = timefind2 / x2;
                    timeerase2 = timeerase2 / x2;
                    timeinsert1 += timeinsert2;
                    timefind1 += timefind2;
                    timeerase1 += timeerase2;
                }
                timeinsert1 = timeinsert1 / x1;
                timefind1 = timefind1 / x1;
                timeerase1 = timeerase1 / x1;
                timeinsertn += timeinsert1;
                timefindn += timefind1;
                timeerasen += timeerase1;
            }
            timeinsertn = timeinsertn / y2;
            timefindn = timefindn / y2;
            timeerasen = timeerasen / y2;
            dot.n = array_size;
            dot.timeinsert = timeinsertn;
            dot.timefind = timefindn;
            dot.timeerase = timeerasen;
            plottimes.push_back(dot);
        }
        return plottimes;
    }
    
};

int main() {
    /*RBTree<int> rb = RBTree<int>();
    rb.insert(5);
    rb.insert(3);
    rb.insert(179);
    //rb.insert(1);
    std::cout << "Searching RB tree: \n179: " << (rb.find(179) ? "Yes" : "No") << "\n40: " << (rb.find(40) ? "Yes" : "No") << '\n';*/

    ofstream out;
    out.open("treeData.txt");
    int y1 = 10;

    Profiler<long long> prof = Profiler<long long>("AVL_Tree");
    vector<times> a = prof.average(3, 3, 20, 1, 5000000);

    for (int i = 0; i < y1; i++) {
        if (out.is_open()) {
            out << a[i].n << ' ' << a[i].timeinsert << ' ' << a[i].timefind << ' ' << a[i].timeerase << endl;
        }
    }
    out.close();

    return 0;
}

