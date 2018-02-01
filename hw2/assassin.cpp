#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "lliststr.h"

using namespace std;

int main(int argc, char* argv[]){
	LListStr* list = new LListStr();

	if (argc != 2) {						//check for input file
	   cerr << "Please provide an input file" << endl;
	   return -1;
    }

	int pos;
	int numPlays = 0;
    string func, str, loser;
    ifstream input(argv[1]);

    while(input >> func >> pos){			//while we input a func and a pos
	    if(func == "ADD"){					
	    	input >> str;					//if ADD, input name
	    	list->insert(pos, str);			//insert a new person
	    	numPlays++;
	    }
	    else if(func == "REPLACE"){
	    	input >> str;					//if REPLACE, input name
	    	list->set(pos, str);			//set the position to new person
	    }
	    else if(func == "ACT"){
	    	loser = list->get(pos);			//if ACT, store the loser
	    	list->remove(pos);				//remove the loser's position
	    }
	}

	int size = list->size();

	if(numPlays == 1)
		cout << "Only one participant: " << list->get(0) << endl;

	else if(size == 1)						//one person is left, output results
		cout << "Assassinated: " << loser << endl 
			<< "Winner: " << list->get(0) << endl;

	else {									//otherwise, output those remaining
		cout << "Remaining Players: " << size << endl;
		for(int i = 0; i < size; i++)
			cout << list->get(i) << endl;
	}
	
    return 0;
}