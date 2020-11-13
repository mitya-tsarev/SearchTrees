#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include "AVLTree.cpp"                    
using namespace std;
 
 struct times{ // struct containing number of nodes in the tree and average operation execution times for it
 	int n;
 	double timeinsert;
 	double timefind;
 	double timeerase;
 };

int main(){
	
	ofstream out;
	out.open("data.txt");

	int x1 = 10, x2 = 10, y1 = 8, y2 = 1;

	srand(time(0));
    
    double start;
    
    AVL_tree<int> avl = AVL_tree<int>();
    	
    int array_size; // number of nodes
    vector<times> plottimes; // vector where data will be stored
    times dot;
    int test;
    
    for(int i = 1; i <= y1; i++){ // search for average operation execution times for trees with different number of nodes (y1)
    	array_size = i*1000000000;
    	double timeinsertn = 0;
    	double timefindn = 0;
    	double timeerasen = 0;
    	for (int k = 0; k < y2; k++){ // search for average operation execution times for different trees with the same number of nodes (y2)
	    	avl = AVL_tree<int>(); // create new tree
	    	for (int i = 0; i < array_size; i++)
	    	{
	    		avl.insert(((rand() % 100000)*100000 + rand() % 10000) % (array_size*10)); // add nodes with random values  			
	    	}    
	    	double timeinsert1 = 0;
	    	double timefind1 = 0;
	    	double timeerase1 = 0;
	    	for (int i = 0; i < x1; i++){ // search for average operation execution times for different numbers (x1)
		    	test = ((rand() % 10000)*10000 + rand() % 10000) % (array_size*10);
		    	cout << test << endl;
		    	double timeinsert2 = 0;
	    		double timefind2 = 0;
	    		double timeerase2 = 0;
		    	for (int j = 0; j < x2; j++){ // search for average operation execution times for the same number (x2)
		    		start = clock();
		    		avl.insert(test);
		    		timeinsert2 += clock()*10000 - start*10000;
		    		start = clock();
		    		avl.find(test);
	    			timefind2 += clock()*10000 - start*10000;
	    			start = clock();
	    			avl.erase(test);
	    			timeerase2 += clock()*1000000 - start*10000;
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
	for(int i = 0; i < y1; i++){
		if (out.is_open()){
			out << plottimes[i].n << ' ' << plottimes[i].timeinsert << ' ' << plottimes[i].timefind << ' ' << plottimes[i].timeerase << endl;
		}			
	}
	out.close();
	return 0;
}
