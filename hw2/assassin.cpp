#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "lliststr.h"

using namespace std;

int main(int argc, char* argv[]){
	//LListStr* list = new LListStr();

	if (argc != 2) {
	   cerr << "Please provide an input file" << endl;
	   return -1;
    }

	int pos;
    string func, str;
    ifstream input(argv[1]);

    while(input >> func >> pos){
    	if(func != "ACT"){
    		input >> str;
    	}
	    if(func == "ADD"){
	    	cout << func << " " << pos << " " << str << endl;
	    	//list->insert(pos, str);
	    }
	    else if(func == "REPLACE"){
	    	cout << func << " " << pos << " " << str << endl;
	    	//list->set(pos, str);
	    }
	    else if(func == "ACT"){
	    	cout << func << " " << pos << endl;
	    	//list->remove(pos);
	    }
	}
    return 0;
}