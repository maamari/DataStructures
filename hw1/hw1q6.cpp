#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void reverse(stringstream &ss);

int main(int argc, char** argv){
	ifstream inputFile(argv[1]);

	int num;
	string word;
	stringstream ss;

	inputFile >> num;
	ss << inputFile.rdbuf();

	reverse(ss);
}

void reverse(stringstream &ss){
	string word;
	if(ss >> word){
		reverse(ss);
		cout << word << " ";
	}
}



