#include <iostream>
#include <functional>
#include <string>
#include "functor.h"
#include "qsort.h"

using namespace std;

template<class Comparator>
void DoStringCompare(const string& s1, const string& s2, Comparator comp){
	cout << comp(s1,s2) << endl;
}

template<class Comparator>
void DoIntCompare(const int & s1, const int & s2, Comparator comp) {
	cout << comp(s1,s2) << endl;
}

int main (){
	// string s1 = "112Blue";
	// string s2 = "234Red";
	// AplhaStrComp comp1;
	// LengthStrComp comp2;
	// NumStrComp  comp3;
	// DoStringCompare(s1, s2, comp1);
	// DoStringCompare(s1, s2, comp2);
	// DoStringCompare(s1, s2, comp3);
	// char x = '0';
	// char y = '1';
	// cout << (int)isupper(x) << endl;
	vector<int> array;
	array.push_back(2);
	array.push_back(3);
	array.push_back(4);
	array.push_back(5);
	array.push_back(1);
	array.push_back(10);
	array.push_back(2);
	AplhaNumComp comp1;
	QuickSort(array, comp1);
	for(unsigned int i = 0 ; i < array.size(); i++)
		cout << array[i] << endl;
}