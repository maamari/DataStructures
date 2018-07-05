#include "webpage.h"
#include <set>
#include <sstream>
#include <iostream>
#include <map>
using namespace std;

WebPage:: WebPage(){}
WebPage :: ~WebPage(){}

void WebPage :: parse(string &doc, string &file, WebPage &web){
  set<string> fileNames;
  vector<string> links;
  vector<string>tempVec;
  
  if(web.text.size())
    web.text[file].push_back(doc);                          //find file and push
  else {
    tempVec.push_back(doc);                          //push back the line from doc
    web.text.insert(pair <string,
      vector<string> >(file,tempVec));  
  }
    
  for(unsigned int i = 0 ; i < doc.length() ; i++)            //parse the string
  {
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
          if(web.wrds.find(anc) != web.wrds.end()) {
            web.wrds[anc].insert(file); 
          }
          else {
            fileNames.insert(file);                             //insert the doc
            web.wrds.insert(pair <string, set<string> 
              >(anc, fileNames));
          }
        }
      }
      else if(paren){
        string path;
        while(ss >> path){               
          if(path.length() && (web.links.find(file) 
            != web.links.end()))
              web.links[file].push_back(path);                 //add link to set
          else if(path.length()){
              links.push_back(path);                      //connect file to link
              web.links.insert(pair< string, 
                vector<string> >(file,links));    
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

      if(loweredIn.length() && (web.wrds.find(loweredIn)
       == web.wrds.end())) {
        fileNames.insert(file);
        web.wrds.insert(pair <string, set<string> 
          >(loweredIn, fileNames));
      }
      else if(loweredIn.length())
        web.wrds[loweredIn].insert(file);
    }
  }
  return;
}