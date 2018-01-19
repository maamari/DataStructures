#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void reverse(istringstream& stream);
void streamIn(const string str);

int main(int argc, char** argv){
	ifstream input(argv[1]);
	string line;
	getline(input, line);
	streamIn(line);
}

void reverse(istringstream& stream){
   string word;
   if (stream >> word){
      reverse(stream);
      cout << word << " ";
   }
}

void streamIn(const string str){
   istringstream stream(str);
   reverse(stream);
   cout << endl;
}

