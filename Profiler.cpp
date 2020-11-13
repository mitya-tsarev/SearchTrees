#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "AVLTree.cpp"                    
using namespace std;
 
 struct times{ // структура, содержащая количество узлов дерева и средние времена выполнения операций для него
 	int n;
 	double timeinsert;
 	double timefind;
 	double timeerase;
 };

int main(){

	int x1 = 10, x2 = 10, y1 = 8, y2 = 1;

	srand(time(0));
    
    	double start;
    
    	AVL_tree<int> avl = AVL_tree<int>();
    	
        int array_size; // количество узлов дерева
    	vector<times> plottimes; // вектор, в котором будут храниться точки с данными
    	times dot;
    	int test;
    
    	for(int i = 1; i <= y1; i++){ // ищем средние времена выполнения операций для деревьев с разным количеством узлов
    		array_size = i*1000000000;
    		double timeinsertn = 0;
    		double timefindn = 0;
    		double timeerasen = 0;
    		for (int k = 0; k < y2; k++){ // ищем средние времена выполнения операций для разных деревьев с одинаковым количеством узлов
	    		avl = AVL_tree<int>(); // создаём новое дерево
	    		for (int i = 0; i < array_size; i++)
	    		{
	    			avl.insert(((rand() % 100000)*100000 + rand() % 10000) % (array_size*10)); // добавляем в дерево узлы со случайными значениями  			
	    		}    
	    		double timeinsert1 = 0;
	    		double timefind1 = 0;
	    		double timeerase1 = 0;
	    		for (int i = 0; i < x1; i++){ // ищем средние времена выполнения операций для разных чисел
		    		test = ((rand() % 10000)*10000 + rand() % 10000) % (array_size*10);
		    		cout << test << endl;
		    		double timeinsert2 = 0;
	    			double timefind2 = 0;
	    			double timeerase2 = 0;
		    		for (int j = 0; j < x2; j++){ // ищем средние времена выполнения операций для фиксированного числа
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
			cout << plottimes[i].n << ' ' << plottimes[i].timeinsert << ' ' << plottimes[i].timefind << ' ' << plottimes[i].timeerase << endl;	
		}
	return 0;
}
