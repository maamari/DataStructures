#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void reverse(stringstream &ss);

int main(int argc, char** argv){
	ifstream inputFile(argv[1]);			//INPUT FILE WITH IFSTREAM

	int num;								//INITIALIZE VARIABLES
	string word;
	stringstream ss;

	inputFile >> num;
	ss << inputFile.rdbuf();				//PUT THE BUFFER INTO THE SS

	reverse(ss);
}

void reverse(stringstream &ss){
	string word;
	if(ss >> word){							//IF SS IS STORING IN WORD, REVERSE
		reverse(ss);
		cout << word << " ";
	}
}



