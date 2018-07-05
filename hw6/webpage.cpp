#include "webpage.h"
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iostream>
#include <functional>
using namespace std;

WebPage:: WebPage(){}
WebPage :: ~WebPage(){}

void WebPage::parse(const string &doc, const string &filename, WebPage &wp){
	set<string> fileNames;
	vector<string> links;
	vector<string> tempVec;

	if(wp.text.size())
		wp.text[filename].push_back(doc);                          //find file and push
	else {
		tempVec.push_back(doc);                          	//push back the line from doc
		wp.text.insert(pair <string,
		vector<string> >(filename ,tempVec));  
	}
	for(unsigned int i = 0; i < doc.length() ; i++){
		string in, loweredDoc;
		bool paren;
		stringstream ss;
		loweredDoc += tolower(doc[i]);

		if(doc[i] == '[' || doc[i]== '('){
			if(doc[i] == '(')
				paren = true;
			else if(doc[i] == '[')
				paren = false;
			++i;

			while(doc[i] != ']' && doc[i] !=')'){
				ss << doc[i];                                            //add doc to ss
				i++;
			}

			if(!paren){
				string anc;
				while(ss >> anc){
					if(wp.keywords.find(anc) != wp.keywords.end()) {
						wp.keywords[anc].insert(filename); 
					}
					else {
						fileNames.insert(filename);                             //insert the doc
						wp.keywords.insert(pair <string, set<string> >(anc, fileNames));
					}
				}
			}
			else if(paren){
				string path;
				while(ss >> path){               
					if(path.length() && (wp.links.find(filename) != wp.links.end()))
						wp.links[filename].push_back(path);                 //add link to set
					else if(path.length()){
						links.push_back(path);                      //connect filename to link
						wp.links.insert(pair< string, 
						vector<string> >(filename,links));    
					}
				}     
			}
		}

		else {
			while(isalpha(doc[i]) || isdigit(doc[i])){
				ss << doc[i]; 
				i++;
			}
			ss >> in;
			string loweredIn = in;

			int j = 0;
			signed int len = in.length();
			while(j != len){
				loweredIn[j] = tolower(in[j]);
				j++;
			}

			if(loweredIn.length() && (wp.keywords.find(loweredIn) == wp.keywords.end())) {
				fileNames.insert(filename);
				wp.keywords.insert(pair <string, set<string> >(loweredIn, fileNames));
			}
			else if(loweredIn.length())
				wp.keywords[loweredIn].insert(filename);
		}
	}
	return;
}

void WebPage::sigma(WebPage &wp, double init, double probability, int step_number, set<string> &result, map<string, double> &ranking) {
	int i = 0;
	double const1 = 1 - probability;
	double const2 = probability*(init);

	while(i < step_number) {
		map<string, double> temp;
		set<string> :: iterator it = result.begin();
		while(it != result.end()) {
			double sum = 0, outs;
			string next;
			set<string> income = wp.incoming_links[*it];

			if(income.size()) {
				set<string>::iterator it2 = income.begin();
				while(it2 != income.end()) {
					outs = wp.links[*it2].size()+1; 
					sum += (ranking[*it2]*(1/outs));
					it2++;
				}
				outs = wp.links[*it].size()+1;
				sum += ranking[*it] * (1/(outs));
				temp.insert(make_pair(*it, (const1 * sum) + (const2)));
			}
			else {
				outs = wp.links[*it].size()+1;
				temp.insert(make_pair(*it, (const1 * (ranking[*it] * (1/(outs)))) + (const2)));
			}
			it++;
		}
		ranking = temp;
		i++;
	}
}

void WebPage::rank(WebPage &wp, set<string> &result, int step_number, double probability, ofstream &out) {	
	set<string> :: iterator it = result.begin();
	double sze = result.size();
	double init = 1/sze;
	map<string, double> ranking;

	while(it != result.end()) {
		set<string> incoming = wp.incoming_links[*it];
		set<string> :: iterator it2 = incoming.begin();
		while(it2 != incoming.end()){
			result.insert(*it2);
			it2++;
		}
		vector<string> outgoing = wp.links[*it];
		for(unsigned int i = 0 ; i < outgoing.size(); i++)
			result.insert(outgoing[i]);
		it++;
	}

	for(set<string> :: iterator it = result.begin(); it != result.end(); it++)
		ranking.insert(pair<string, double>(*it, init));
	
	sigma(wp, init, probability, step_number, result, ranking);
	
	multimap <double, string, greater<double> > output;
	map<string, double> :: iterator it2 = ranking.begin();
	while(it2 != ranking.end()){
		output.insert(make_pair(it2->second, it2->first));
		it2++;
	}

	out << output.size() << endl;
	multimap <double, string, greater<double> > :: iterator it3 = output.begin();
	while(it3 != output.end()){
		out << it3->second << endl;
		it3++;
	}
}

