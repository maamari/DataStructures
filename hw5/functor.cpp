#include "functor.h"
#include <string>
using namespace std;	

bool NumStrComp ::operator()(const string &lhs,const string &rhs) {
	int first = 0, second = 0;
	unsigned int i = 0, j = 0;

	while(i < lhs.length()){
		if(isdigit(lhs[i]))					  //if it's already a number
			first += (int)lhs[i] - 48;			 //cast it to an int and subtract 48
		else if(isalpha(lhs[i]))							   //check if it is a letter
			first += (int)toupper(lhs[i]) - 55;	 //change to upper case, subtract 55
		i++;
	}

	while(j < rhs.length()){
		if(isalpha(rhs[i]))								 //same as above for all
			second += (int)toupper(rhs[i]) - 55;
		else if (isdigit(rhs[i]))
			second += (int)rhs[i] - 48;
		j++;
	}
	if(first == second) return lhs < rhs;
    else return first < second;
}