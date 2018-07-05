#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <string>
#include <sstream>
#include <fstream>
#include "webpage.h"
#include "setutility.h"
using namespace std;

void search(int step_number, float prob, const char *index, 
			const  char *query, const  char *output) {
	WebPage wp;
	ifstream input(index);
	string line, txt;

	while(getline(input,line)) {
		ifstream file(line.c_str());
		if(!file.fail()) {
			while(getline(file,txt))
				wp.parse(txt,line,wp);
		}
 	}

 	map< string, vector<string> > :: iterator it = wp.text.begin();
	while(it != wp.text.end()) {
		string web_name = it->first;
		set <string> result;
		map< string, vector<string> > :: iterator it2 = wp.links.begin();
		while(it2 != wp.links.end()) {
			unsigned int i = 0;
			while(i < it2->second.size()) {
				if(web_name== it2->second[i])
					result.insert(it2->first);
				i++;
			}
			it2++;
		}
		wp.incoming_links.insert(make_pair(web_name, result));
		it++;
	}

 	ifstream ops(query);
 	ofstream out(output);
 	vector <string> operate;
 	stringstream ss;
	string command;

 	while(getline(ops, line)){
 		if(line.length()){

 			unsigned int i = 0;
	 		while(i < line.length()){
	 			ss << line[i];
	 			i++;
	 		}

	 		ss >> command;

	 		string buff, word;
 			while(ss >> word) {
 				unsigned int j = 0;
				while(j < word.length()) {
					word[j] = tolower(word[j]);		//CHANGE
					j++;
				}
				operate.push_back(word);			//CHANGE
 			}

	 		if(!operate.size()) {
	 			string buff;
	 			unsigned int i = 0; 
	 			while(i < command.length()){
	 				buff += tolower(command[i]);
	 				i++;
	 			}
	 			set<string> result = wp.keywords[buff];
	 			wp.rank(wp, result, step_number, prob, out);
	 		}
	 		else if(command == "AND" || command == "OR") {
	 			set<string> result;
				vector<set<string> > docs;

				unsigned int i = 0, j = 0;
				while(i < operate.size()){
					docs.push_back(wp.keywords[operate[i]]);
					i++;
				}
				while(j < docs.size()-1){
					if(command == "AND") docs[j+1]= intersectSet(docs[j], docs[j+1]);		//CHANGE
					else docs[j+1]= unionSet(docs[j], docs[j+1]);							//CHANGE
					j++;
				}

				result = docs[docs.size()-1]; 
	 			wp.rank(wp, result, step_number, prob, out);
	 		}

	 		else if(command == "INCOMING" || command == "OUTGOING" || command == "PRINT") {
	 			if(operate.size() >= 2)
	 				out << "Invalid query" << endl;
	 			else {
	 				string target = *operate.begin();
	 				if(command == "INCOMING"){
	 					set<string> result= wp.incoming_links[target];
	 					if(result.size()) {
							out << result.size() << endl;
							set<string> :: iterator it = result.begin();
							while(it != result.end()){
								out << *it << endl;
								it++;
							}
						}
						else if(!result.size())
							out << 0 << endl;
	 				}
	 				else if(command == "OUTGOING"){
	 					vector<string> result = wp.links[target];
						if(result.size()) {
							out << result.size() << endl;
							for(unsigned int i = 0; i < result.size(); i++)
								out << result[i] << endl;
						}
						else if (!result.size())
							out << 0 <<  endl;
	 				}
	 				else{
	 					if(!wp.text[target].size()) {
						out << "HERE" << endl;
						out << "0" << endl;
						return;
						}
						out << target << endl;
						vector <string> result;
						result = wp.text[target];
						for(unsigned int i = 0; i < result.size(); i++) {
							string line = result[i];
							for(unsigned int j = 0; j < line.length(); j++) {
								if(line[j] == '(') {
									while(line[j] != ')')
										j++;
									if(j != line.length())
										j++;
								}
								if(j != line.length())
									out <<  line[j];
							}
							out << endl;
						}
						break;
	 				}
	 			}
	 		}
	 		else
	 			out << "Invalid query" << endl;
 		}
 	}
}

int main (int argc, char *argv[]) {
	int step_number = 0; float prob = 0;
	string index, query, output, line, command;
	ifstream input(argv[1]);

	while(getline(input, line)) {
		stringstream ss;
		bool tru;
		int length = (int)line.length(), i = 0;
		string buff, ind = "INDEX_FILE", o = "OUTPUT_FILE", q = "QUERY_FILE", 
			   		            r = "RESTART_PROBABILITY", s = "STEP_NUMBER";

		while(i < length) {
			if(line[0] == '#')
				break;

			ss << line[i];
			i++;

			if(line[i] == '=') {
				i++;
				ss >> command;
				ss.clear();
				while(i <= length) {
					if(i == length || line[i] == '#'){
						ss >> buff;
						if(command == ind) {
							index = buff; tru = true;
						}
						else if(command == o) {
							output = buff; tru = true;
						}
						else if(command == q) {
							query = buff; tru = true;
						}
						else if(command == r) {
							prob = atof(buff.c_str()); tru = true;
						}
						else if(command == s) {
							step_number = atoi(buff.c_str()); tru = true;
						}
						if(tru){
							i++; break;
						}
					}
					else if(command == ind || command == o || command == q 
										   || command == r || command == s) {
						ss << line[i];
						i++;
					}
					else
						break;
				}
			}
		}
	}
	input.close();
	search(step_number, prob, index.c_str(), query.c_str(), output.c_str());
}