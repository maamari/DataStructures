#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "lliststr.h"

using namespace std;

int main(int argc, char* argv[]){
	LListStr* list = new LListStr();

	if (argc != 2) {
	   cerr << "Please provide an input file" << endl;
	   return -1;
    }

	int pos;
    string func, str, loser;
    ifstream input(argv[1]);

    while(input >> func >> pos){
	    if(func == "ADD"){
	    	input >> str;
	    	list->insert(pos, str);
	    }
	    else if(func == "REPLACE"){
	    	input >> str;
	    	list->set(pos, str);
	    }
	    else if(func == "ACT"){
	    	loser = list->get(pos);
	    	list->remove(pos);
	    }
	}

	int size = list->size();
	if(size == 1){
		cout << "Assassinated: " << loser << endl << "Winner: " << list->get(0) << endl;
	}
	else{
		cout << "Remaining Players: " << size << endl;
		for(int i = 0; i < size; i++){
			cout << list->get(i) << endl;
		}
	}
	

    return 0;
}