#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "lliststr.h"

using namespace std;

int main(int argc, char* argv[]){
	LListStr* list = new LListStr();

	if (argc < 2) {
	   cerr << "Please provide an input file" << endl;
	   return -1;
    }

	int pos;
    string func, str;

    ifstream input(argv[1]);
    input >> func >> pos >> str;

    if(func == "ADD"){
    	cout << "inserting" << endl;
    	list->insert(pos, str);
    }
    else if(func == "REPLACE"){
    	cout << "replacing" << endl;
    	list->set(pos, str);
    }
    else if(func == "ACT"){
    	cout << "acting" << endl;
    	list->remove(pos);
    }
    return 0;
}