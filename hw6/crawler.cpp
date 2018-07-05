#include <vector>
#include <set>
#include <fstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void crawl(string indx, set<string> &one, ofstream &out) {
	ifstream inpt(indx.c_str());
	string line, nxt;
	while(getline(inpt, line)) {
		unsigned int i = 0;
		while(i < line.length()) {
			stringstream ss;
			if(line[i] == '(') {
				++i;
				while(line[i]!=')') {
					ss << line[i];
					i++;					
				}
			}
			while(ss >> nxt) {
				if(nxt.length()) {
					ifstream real(nxt.c_str());
					if(one.find(nxt) == one.end()&& !real.fail()) {
						out << nxt << endl;
						one.insert(nxt);
						crawl(nxt, one, out);
					}
				}
			}
			i++;
		}
	}
}

void read_config (char* configFile, string &indx, string &output) {
	ifstream input(configFile);
	string line, outpt, inpt;

	if(input.fail())
		return;
	else {
		while(getline(input,line)) {
			int i = 0, length = (int)line.length();
			stringstream ss; 
			while(i < length){
				bool comment = false;
				if(line[i] == '#')
					comment = true;
				ss << line[i]; i++;
				if(line[i] == ' '){
					continue;
					i++;
				}
				if(line[i] == '=' && comment == false) {
					i++;
					string cmnd;
					ss >> cmnd;
					ss.clear();
					if(cmnd == "OUTPUT_FILE") {
						while(i <= length) {
							ss << line[i];
							++i;
						}
						ss >> outpt;
						output = outpt;
						i++;
						break;
					}
					else if(cmnd == "INDEX_FILE") {
						while(i <= length) {
							ss << line[i];
							++i;
						}
						ss >> inpt;
						indx = inpt;
						i++;
					}
					else
						break;
				}
			}
		}
	}	
}


int main(int argc, char* argv[]) {
	string indx, output, doc;
	set<string> temp;
	read_config(argv[1], indx, output);

	ofstream out(output.c_str());
	ifstream inpt(indx.c_str());

	while(getline(inpt, doc)) {
		if(temp.end() == temp.find(doc)) {
			temp.insert(doc);
			out << doc << endl;
			crawl(doc, temp, out);
		}
	}
}