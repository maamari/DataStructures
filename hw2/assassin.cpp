#include <iostream>
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

	int pos, size;
	int numPlays = 0;
    string func, str, loser, winner;
    ifstream input(argv[1]);

    while(input >> func >> pos){			//while we input func & pos
	    if(func == "ADD"){					
	    	input >> str;					//if ADD, input name
	    	list->insert(pos, str);			//insert a new person
	    	numPlays++;
	    }
	    else if(func == "REPLACE"){
	    	input >> str;					//if REPLACE, input name
	    	list->set(pos, str);			//set the position to new person
	    }
	    else if(func == "ACT"){				//if ACT
	    	if(pos == list->size()-1){
	    		winner = list->get(pos);	//get winner
	    		loser = list->get(0);		//get loser
	    		list->remove(0);			//remove the loser's position	
	    	}
	    	else {
	    		winner = list->get(pos);
	    		loser = list->get(pos+1);	
	    		list->remove(pos+1);
	    	}
	    }
	}

	size = list->size();
	
	if((winner == "Invalid position."))		//invalid entry
		cout << "Invalid entry of participants" << endl;

	else if(numPlays == 1)					//one player to start
		cout << "Only one participant: " << winner << endl;

	else if(size == 1)						//one person is left, output results
		cout << "Assassinated: " << loser << endl 
			<< "Winner: " << winner << endl;

	else {									//otherwise, output those remaining
		cout << "Remaining Players: " << size << endl;
		for(int i = 0; i < size; i++)
			cout << list->get(i) << endl;
	}
	
    return 0;
}