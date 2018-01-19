#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

struct Warrior {
    string weapon;
    int power;
};

//Feel free to modify the parameters if you need other values
bool skirmish(Warrior*** protectors, Warrior*** invaders, int skirmishIndex,
		      int rows, int columns, int *reserves, ofstream &output, int skirmishes){
    //returns true if the invaders breach the walls.
    if(skirmishIndex > columns-1){
        output << "Both sides stare at each other is confusion as a skirmish at row " << skirmishIndex << " is simply not possible!" << endl;
    }

    else{
    	for(int i = 0; i < rows; i++){
    		if((invaders[skirmishIndex][i][0].power > 0) && (protectors[i][skirmishIndex][0].power > 0)){						//BOTH EXIST

    			if((invaders[skirmishIndex][i][0].weapon == "Axe" && protectors[i][skirmishIndex][0].weapon == "Sword")			//INVADER WINS
    			  || ((invaders[skirmishIndex][i][0].weapon == protectors[i][skirmishIndex][0].weapon) 
    			  && (invaders[skirmishIndex][i][0].power > protectors[i][skirmishIndex][0].power))){

                    bool protectorDef = false;
                    for(int j = 0; j < rows; j++){  
                        for(int k = 0; k < skirmishIndex; k++){                                                         
                            if(invaders[k][j][0].power == 0){                                                                  //PROTECTOR DEFECTS
                                invaders[k][j][0].power = protectors[skirmishIndex][j][0].power;
                                output << "Protector Defected\n";
                                protectorDef = true;
                                break;
                            }
                        }
                        if(protectorDef){
                            break;    
                        }
                    }
                    if(!protectorDef){
                        protectors[i][skirmishIndex][0].power = 0;
                        output << "Protector killed\n";     
                    } 

        			if((*reserves > 0) && (protectors[i][skirmishIndex][0].power == 0)){	
    					(*reserves)--;							//RESERVE ENTERS
    					protectors[i][skirmishIndex][0].power = 100;
    					protectors[i][skirmishIndex][0].weapon = "Axe";
    				}
    			}

        		else if((invaders[skirmishIndex][i][0].weapon == "Sword" && protectors[i][skirmishIndex][0].weapon == "Axe")	//PROTECTOR WINS
    			       || ((invaders[skirmishIndex][i][0].weapon == protectors[i][skirmishIndex][0].weapon) 
    			       && (invaders[skirmishIndex][i][0].power < protectors[i][skirmishIndex][0].power))){
        			invaders[skirmishIndex][i][0].power = 0;																//INVADER DIES
        			output << "Invader killed\n";
        		}

    			else{		
    				output << "Duel ends in a draw\n";																//DRAW
    			}
    		}
     		else if(invaders[skirmishIndex][i][0].power == 0 && protectors[i][skirmishIndex][0].power > 0){						//NO INVADER
    			output << "No assualt\n";
     		}
     		else if(invaders[skirmishIndex][i][0].power > 0 && protectors[i][skirmishIndex][0].power == 0){
     			return true;
     		}
    	}
    }
    return false;
}

int main(int argc, char* argv[]){

    if (argc < 3) {
	   cerr << "Please provide an input and output file" << endl;
	   return -1;
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);

    int rows;
    int cols;
    int reserves;
    int skirmishes;

    //read the input file and initialize the values here.
    input >> rows >> cols >> reserves >> skirmishes;
    
    Warrior ***protectors = new Warrior**[rows];
    Warrior ***invaders = new Warrior**[cols];

    //initialize the protectors and invaders here.
    for(int r = 0; r < rows; r++){
    	protectors[r] = new Warrior*[cols];
    	for(int c = 0; c < cols; c++){
    		protectors[r][c] = new Warrior[1];
    		for(int d = 0; d < 1; d++){
    			protectors[r][c][d].power = ((r*10)+((c+1)*10));
    			if(r%2 == 0){
    				protectors[r][c][d].weapon = "Axe";
    			}
    			else{
    				protectors[r][c][d].weapon = "Sword";
    			}
    		}
    	}
    }

    for(int i = 0; i < cols; i++){
    	invaders[i] = new Warrior*[rows];
    	for(int j = 0; j < rows; j++){
    		invaders[i][j] = new Warrior[1];
    		for(int k = 0; k < 1; k++){
    			invaders[i][j][k].power = ((i*10)+((j+1)*10));
    			if(i%2 == 1){
    				invaders[i][j][k].weapon = "Axe";
    			}
    			else{
    				invaders[i][j][k].weapon = "Sword";
    			}
    		}
    	}
    }

    bool end;
    for (int i=1; i <= skirmishes; i++){
        int skirmishIndex;

        //read the input file to find the value for skirmish row
        input >> skirmishIndex;
        //In general, it is bad style to throw everything into your main function
        end = skirmish(protectors, invaders, skirmishIndex, rows, cols, &reserves, output, skirmishes);
    }

    //output the winner and deallocate your memory.
    if(end == 0){
    	output << "Winner: protectors\n";
    }
    else{
    	output << "Winner: invaders\n";
    }



    for(int i = 0; i < rows; i++){
    	for(int h = 0; h < cols; h++){
        	delete [] protectors[i][h];
        	
    	}
    	delete [] protectors[i];
 
	}
	delete [] protectors;

	for(int i = 0; i < cols; i++){
    	for(int h = 0; h < rows; h++){
        	delete [] invaders[i][h];
        	
    	}
    	delete [] invaders[i];
 
	}
	delete [] invaders;

    return 0;
}
