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
bool skirmish(Warrior*** protectors, Warrior*** invaders, int skirRow,
              int rows, int columns, int *reserves, ofstream &output, int skirmishes){
    //returns true if the invaders breach the walls.
    
    for(int i = 0; i < rows; i++){
        if((invaders[skirRow][i][0].power > 0) && (protectors[i][skirRow][0].power > 0)){                       //BOTH EXIST

            if((invaders[skirRow][i][0].weapon == "Axe" && protectors[i][skirRow][0].weapon == "Sword")         //INVADER WINS
              || ((invaders[skirRow][i][0].weapon == protectors[i][skirRow][0].weapon) 
              && (invaders[skirRow][i][0].power > protectors[i][skirRow][0].power))){                                                   
                    if(invaders[skirRow][i][0].power == 0){                                                     //PROTECTOR DEFECTS
                        invaders[skirRow][i][0].power = protectors[skirRow][j][0].power;
                        output << "Protector Defected\n";
                        break;
                    }
                    else{
                        protectors[i][skirRow][0].power = 0;
                        output << "Protector killed\n";                                                         //PROTECTOR DIES
                        break;
                    }
                break;

                if((*reserves > 0) && (protectors[i][skirRow][0].power == 0)){  
                    (*reserves)--;                          //RESERVE ENTERS
                    protectors[i][skirRow][0].power = 100;
                    protectors[i][skirRow][0].weapon = "Axe";
                }
            }

            else if((invaders[skirRow][i][0].weapon == "Sword" && protectors[i][skirRow][0].weapon == "Axe")    //PROTECTOR WINS
                   || ((invaders[skirRow][i][0].weapon == protectors[i][skirRow][0].weapon) 
                   && (invaders[skirRow][i][0].power < protectors[i][skirRow][0].power))){
                invaders[skirRow][i][0].power = 0;                                                              //INVADER DIES
                output << "Invader killed\n";
            }

            else{       
                output << "Duel ends in a draw\n";                                                              //DRAW
            }
        }
        else if(invaders[skirRow][i][0].power == 0 && protectors[i][skirRow][0].power > 0){                     //NO INVADER
            output << "No assualt\n" << endl;
        }
        else if(invaders[skirRow][i][0].power > 0 && protectors[i][skirRow][0].power == 0){
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[])
{
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

    bool end = true;
    for (int i=1; i <= skirmishes; i++){
        int skirRow;

        //read the input file to find the value for skirmish row
        input >> skirRow;
        //In general, it is bad style to throw everything into your main function
        end = skirmish(protectors, invaders, skirRow, rows, cols, &reserves, output, skirmishes);
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
