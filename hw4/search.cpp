#include <iostream>
#include <sstream>
#include <stack>
#include <iterator>
#include <vector>
#include <stdio.h>
#include <ctype.h>
#include <fstream>
#include <set>
#include "webpage.h"
using namespace std;

WebPage wpage; 
set<string> :: iterator it;
map< string, vector<string> > :: iterator it2;
vector <string> output;

void commander(string &command, vector<string> 
  &qWords, ofstream &out){
  unsigned int i;

  if(command == "OR" || command == "AND") {                          //if AND/OR
    stack<set<string> > stack;
    for(i = 0; i < qWords.size(); i++)
      stack.push(wpage.wrds[qWords[i]]);                  //push qWords's link(s)

    while(stack.size() >= 2) {
      set<string> one = stack.top(); stack.pop();
      set<string> two = stack.top(); stack.pop();

      if(command == "OR"){                                               //if OR
        for(it = two.begin(); it != two.end(); it++){
          if(one.find(*it) == one.end())           
            one.insert(*it);
        }
        stack.push(one);                                      //find the union
      }
      if(command == "AND"){                                             //if AND
        set<string> output;
        for(it = one.begin(); it != one.end(); it++){
          if(two.find(*it)!=two.end())
            output.insert(*it);
        }
        stack.push(output);                                //intersect the links
      }
    }
          if(stack.top().size() == 0){                 //6,7,8,10,11,12
        out << "0" << endl;
      }
      else if(stack.top().size() >= 1){
        out << stack.top().size() << endl;             //output the num of links
        for(it = stack.top().begin(); it!= stack.top().end(); it++) {
          out << *it << endl;
        }
      }
  }

  else if(command == "PRINT"){                             //if PRINT, send link
    string web = *qWords.begin();
    output = wpage.text[web];
    out << web << endl;                                     //CASE 15
    for(i = 0 ; i < output.size(); i++){
      string doc = output[i];
      for(unsigned int k =0 ; k < 
        doc.length(); k++){
        if(doc[k] == '('){
          while(doc[k] != ')')
            k++;
          k++;
        }
        out << doc[k];
      }
      out << endl;
  }                              
  }
  else if(command == "INCOMING"){                        //if INCOMING, send link
    string web = *qWords.begin();
    it2 = wpage.links.begin();
    while(it2 != wpage.links.end()){
      for(i = 0; i < it2->second.size(); i++){
        unsigned int finder = web.find(it2->second[i]);
        if(finder < web.length() && finder >= 0)
          output.push_back(it2->first);
      }
      it++;
      it2++;
    }
    if(!output.size()){
      out << 0 << endl;
    }
    else {
      out << output.size() << endl;
      i = 0;
      while(i < output.size()){
        out << output[i] << endl;
        i++;
      }
    }
  }

  else if(command == "OUTGOING"){                       //if OUTGOING, send link
    string web = *qWords.begin();
    vector<string> outgoin = wpage.links[web];

    if(outgoin.size()){
      out << outgoin.size() << endl;
      i = 0;
      while(i < outgoin.size()){
        out << outgoin[i] << endl;
        i++;
      }
    }
    else                                                    //CASE 16
      out << "0" << endl;
  }
}

int main (int argc, char *argv[]) {
  ifstream index(argv[1]);                                          //grab index
  ifstream qry(argv[2]);                                           //grab qWords 
  ofstream out(argv[3]);                                     //put output in ofs  
  string doc, line, words;

  while (getline(index,doc)) {                            //grab file from index
    ifstream file(doc.c_str());                         //input file to ifstream
    while(getline(file,words))                           //grab string from file
      wpage.parse(words, doc, wpage);                          //parse the webpage
  }

  while(getline(qry, line)){                             //grab line from qWords
    vector <string> qWords;                            //vector of qWords words
    string word, command;
    stringstream ss(line);                             //input qWords line to ss
    string buff, buff1;

    ss >> command;                                               //input command

    if(command.length() == line.length()){             //if command is only word
      for(unsigned int i = 0; i < command.length(); i++)    //CHANGED 2,3,4,5
        buff1 += tolower(command[i]);                   //lowercase qWords words
      set<string> output = wpage.wrds[buff1];                  //grab the link
      if(output.size()>0) {                                   //if link exists
        out << output.size() << endl;                      //output num of links
        for(it = output.begin(); it !=                         //print all links
          output.end() ; it++)    
          out << *it << endl;
      }
      else if(output.size() == 0)                    //CHANGED 1, 5
        out << "0" << endl;
    }

    else {
      while(ss >> buff){                          //otherwise input qWords words
        string pusher;
        for(unsigned int i = 0; i < 
          buff.length(); i++){
          pusher += tolower(buff[i]);                   //lowercase qWords words
        }
        qWords.push_back(pusher);                   //push them to qWords vector
      }
      commander(command, qWords, out);              //CHANGED
    }
  }
}