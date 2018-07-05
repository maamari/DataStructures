#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdexcept>
#include "stackstr.h"

using namespace std;

bool valid(string whole) {                                 //CHECK LINE VALIDITY
  int opPlus = 0, opMin = 0, lcnt = 0, cars = 0, oParen = 0, cParen = 0;
  bool openPar = false, closePar = false;
  unsigned int spaceCnt = 0;

  for(unsigned int i = 0; i < whole.size(); i++) {         //GO THROUGH EACH CHAR
    char c = whole[i];                                               //line CHAR
    int j = i+1;                                                     //NEXT CHAR

    if(isalpha(whole[i]))                                            //IF LETTER 
      lcnt++;
    if(c == ' ')                                                      //IF SPACE
      spaceCnt++;

    if((!(c == '>' || c == '<'|| c == '+' || c == '-' || c ==   //NOT VALID CHAR
      ')' || c == '(' || c == ' ' || (c >= 'a' && c <= 'z'))) ||
      (isalpha(whole[0]) || whole[0] == ')'))            //NO LETTERS BEFORE '('
        return false;

    if(whole[i] == '(') {                                    
      while(whole[j] == ' ')                                       //SKIP SPACES
        j++;

      if(whole[j] == '-' || whole[j] == ')' || whole[j] == '+' )     //NO LETTER
        return false;
                                                                            
      oParen++;                                           //INCREMENT OPEN count
      closePar = false;                                         //CLOSE IS FALSE
      openPar = true;                                             //OPEN IS TRUE
      cars = 0;                                                    //CARROTS = 0
      opMin = 0;                                                      //PLUS = 0
      opPlus = 0;                                                    //MINUS = 0

    }
    else if(whole[i] == ')') {     
      if((whole[j] == '>' || whole[j] == '<' || isalpha(whole[j]) || 
        whole[j] == '(') || ((whole[i-1] != ')') && !cars && 
        (!opMin && !opPlus && (whole[i-1] != ' '))))
        return false;

      cParen++;                                                                     
      closePar = true;
      openPar = false;
      opMin = 0;
      opPlus = 0;
      cars = 0;
    }

    if(whole[i] == '+') {                                       //INCREMENT PLUS  
      opPlus++;
    } 
    else if(whole[i] == '-') {                                 //INCREMENT MINUS
      opMin++;
    } 
    else if(whole[i] == '>' || whole[i] == '<'){             //INCREMENT CARROTS
      cars++;
    }                                //CHECK OPS, PARENS, AND PLACEMENTS OF BOTH
    if((((opMin > 1) || (opMin >= 1 && opPlus >= 1)) || ((!openPar && !closePar)
     && (opPlus || opMin))) || ((i > 0 && i < whole.size() - 1) && (whole[i] == 
     '+' ||whole[i] == '-') && (whole[i + 1] == ')' || whole[i + 1] 
      == '+' || whole[i + 1] == '-' || whole[i - 1] == '(')))
        return false;

    if((whole[i] == '<' || whole[i] == '>') && i > 0) {  //IF CARROT AFER LETTER
      if(isalpha(whole[i - 1])) {
        return false;
      }
    }
  }

  if((whole[0] == '+' || whole[0] == '-' || whole[whole.size() //IF START OR END
   - 1] == '+' || whole[whole.size() - 1] == '-') || ((lcnt == 0) 
   || (oParen != cParen)))                            //IF DIFF # OPEN AND CLOSE
    return false;

  return true;                                                  //OTHERWISE TRUE
}

bool opCheck(const string& operatr) {                      //CHECKS IF OPERATION
  if(!(operatr == "<" || operatr == ">" || operatr == "+" || operatr == "-"))
    return false;
  return true;
}

string operate(string& s1, string& s2, string& op, ofstream& output) {
  if(op == "+")                                                      //OPERATE +
    s1+=s2; 
  else if(op == "-"){                                                //OPERATE -
    string temporary = s1;
    try { s1.erase(s1.find(s2), s2.size());
    } catch (std::out_of_range notInRange){
    }
    if(!(strcmp(temporary.c_str(), s1.c_str())))
      return s1;
  }
  else if(op == "<"){                                                //OPERATE <
    if(s1.size() > 1)
      s1.erase(s1.size() - 1);
  }
  else if(op == ">"){                                                //OPERATE >
    if(s1.size()>1)
      s1.erase(s1.begin());
  }
  return s1;                                                   //RETURN OPERATED
}

string removalCnt(int leftCounter, int rightCounter, string& s1) {
  while(leftCounter){                             //EVAL BASED ON NUM OF CARROTS
    if(s1.size() > 1)                                            //TAKE OFF BACK
      s1.erase(s1.size() - 1);
    leftCounter--;
  }
  while(rightCounter){
    if(s1.size()>1)                                             //TAKE OFF FRONT
      s1.erase(s1.begin());
    rightCounter--;
  }
  return s1;                                                   //RETURN OPERATED
}

string eval(int& tmp, int& wcnt, StackStr& wStack,             //EVALUATE STACKS
  StackStr& oStack, StackStr& tStack, StackStr& stack, 
  string& result, ofstream& output) {
  string w1, o, w2;
  int evalCnt = 0;

  if(!wStack.empty()) {
    while(!oStack.empty()){
      evalCnt++;
      if(evalCnt > 1) {                                 //IF EVALUATING MULT TIMES
        if((wStack.top() == result) && (o == "-"))     //IF SUBSTRACTING FROM SELF
          return "Malformed";
        w2 = wStack.top();
        wStack.pop();
        wcnt--;
        o = oStack.top();
        oStack.pop();
        result = operate(w2, result, o, output);
      }
      else if(wcnt == 1){                                            //IF ONE WORD
        w1 = wStack.top();
        wStack.pop();
        wcnt--;
        o = oStack.top();
        oStack.pop();
        if((w1 == w2) && (o == "-"))
          return "Malformed";
        result = operate(w1, w2, o, output);
      }
      else {                                                           //OTHERWISE
        w1 = wStack.top();
        wStack.pop();
        wcnt--;
        o = oStack.top();
        oStack.pop();
        if((wStack.top() == w1) && (o == "-")){
          return "Malformed";
        }
        w2 = wStack.top();
        wStack.pop();
        wcnt--;
        result = operate(w2, w1, o, output);
    }
  }
}
  while(!wStack.empty() && oStack.empty()){         //IF WORDS BUT NO OPS, EMPTY
    result = wStack.top();
    wcnt--;
    wStack.pop();
  }
  stack.push(result);

  StackStr temp = stack;
  bool tOf = true;
  while(!temp.empty()) {                                      //LOOK FOR CARROTS
    string top = temp.top();
    if(top != "<" && top != ">" && !isalpha(top[0])) {
      tOf = false;
    }
    temp.pop();
  }

  if(tOf) {                                                    //IF CARROT FOUND
    while(!stack.empty()) {
      tStack.push(stack.top());
      tmp++;
      stack.pop();
    }

    int frnt = 0;                                         //COUNT NUM OF CARROTS
    int bck = 0;
    while(tmp != 0) {
        string topStack;

        topStack = tStack.top();
        tStack.pop();
        tmp--;

        if(topStack == "<"){
          frnt++;
          topStack = tStack.top();
          result = removalCnt(frnt, bck, topStack);            //OPERATE CARROTS
        }
        else if(topStack == ">"){
          bck++;
          topStack = tStack.top();
          result = removalCnt(frnt, bck, topStack);            //OPERATE CARROTS
        }
      }
    }
  return result;
}

int main(int argc, char* argv[]) {
  if(argc < 3){
    cerr << "Please provide an input and output file." << endl;
    return 1;
  }
  ofstream output(argv[2]);
  ifstream input(argv[1]);
  string line;

  while(getline(input, line)) {                               //WHILE LINE INPUT
    stringstream ss(line);
    string strng;

    stringstream size(line);             //COUNTER OF LINE SIZE INCLUDING SPACES
    string sizeString;
    string temp;

    string lttrs, wrd, result;            //LTTRS IS A BUFFER, WRD IS COMPARATOR
    int tmp = 0, wcnt = 0;
    
    StackStr stack, tStack, opStack, wordStack;
    while(size >> sizeString)                              //INCREMENT SIZE CNTR
        temp+=sizeString;
    unsigned int lineSize = 0;

    while((ss >> strng) && valid(line)) {     //WHILE INPUTTING AND LINE IS GOOD
      unsigned int strSize = 0;

      while(strSize < strng.size()) {               //WHILE NOT AT END OF STRING
        char c = strng[strSize];
        strSize++;
        lineSize++;

        if((c == '<' || c == '>' || c == '+' ||               //IF STUFF IN BUFF
          c == '-' || c == '(') && (c != ')') && (lttrs.size())) {         
            stack.push(lttrs);
            lttrs.clear();
        }

        if((c == '<' || c == '>' || c == '+' ||                         //IF OPS
          c == '-' || c == '(') && (c != ')')) {
          string holder;                                      //PUSH OP TO STACK
          holder += c;
          stack.push(holder);
        } 

        else if(isalpha(c)) {                                       //IF LETTERS
          lttrs += c;
          if(lineSize == temp.size()){          //IF LETTERS IS AT END OF STRING
            stack.push(lttrs); 
            lttrs.clear();
          }
        }

        else if(c == ')') {                                  //IF END OF SECTION
          if(lttrs != wrd) {  
              stack.push(lttrs);
              lttrs.clear();
          }            

          while(stack.top() != "(") {                            //LOOK FOR OPEN
              if((stack.top()).empty()) 
                stack.pop();
              string pusher = stack.top();           //REMOVE UNITL WE GET THERE
              stack.pop();
              tStack.push(pusher);
              tmp++;
          }
          stack.pop();

          while(tmp) {                                     //WHILE STUFF IN TEMP
            string topStack = tStack.top();
            tStack.pop();
            tmp--;

            int frnt = 0;                                 //FRONT CARROT COUNTER
            int bck = 0;                                   //BACK CARROT COUNTER 
            if(topStack == ">"){                     
                bck++;
              while(tStack.top() == "<" || tStack.top() == ">" ) {
                if(tStack.top() == "<")                      //IF DOUBLE CARROTS
                  frnt++;
                else if(tStack.top() == ">")
                  bck++;
                tStack.pop();
                tmp--;
              }

              topStack = tStack.top();             //IF ( AFTER <, DOUBLE CARROT
              if(topStack == "(") {
                for(int z = 0; z < bck; ++z) 
                  opStack.push(">");
                for (int z = 0; z < frnt; ++z) 
                  opStack.push("<");
              }

              else if(!opCheck(topStack) && topStack               //TOP IS WORD
                != ")" && topStack != "(") {
                wrd = topStack;
                topStack = removalCnt(frnt, bck, topStack);

                wordStack.push(topStack);         //PUSH TO WORDSTACK AND REMOVE
                wcnt++;
                tStack.pop();
                tmp--; 

                if(tmp) {
                  if(opCheck(tStack.top())) {               //IF TEMP ISNT EMPTY
                    opStack.push(tStack.top());                    //LOOK FOR OP 
                    tStack.pop();
                    tmp--; 
                  } 
                } 
              }
            }
            else if(topStack == "<"){
              frnt++;
              while(tStack.top() == "<" || tStack.top() == ">" ) {
                if(tStack.top() == "<")                      //IF DOUBLE CARROTS
                  frnt++;
                else if(tStack.top() == ">")
                  bck++;
                tStack.pop();
                tmp--;
              }

              topStack = tStack.top();             //IF ( AFTER <, DOUBLE CARROT
              if(topStack == "(") {
                for(int z = 0; z < bck; ++z) 
                  opStack.push(">");
                for (int z = 0; z < frnt; ++z) 
                  opStack.push("<");
              }

              else if(!opCheck(topStack) && topStack               //TOP IS WORD
                != ")" && topStack != "(") {
                wrd = topStack;
                topStack = removalCnt(frnt, bck, topStack);

                wordStack.push(topStack);         //PUSH TO WORDSTACK AND REMOVE
                wcnt++;
                tStack.pop();
                tmp--; 

                if(tmp) {
                  if(opCheck(tStack.top())) {               //IF TEMP ISNT EMPTY
                    opStack.push(tStack.top());                    //LOOK FOR OP 
                    tStack.pop();
                    tmp--; 
                  } 
                } 
              }
            }

            else {
              if(!opCheck(topStack)) {                    //IF NOT OP, PUSH WORD
                wcnt++; 
                wordStack.push(topStack);
              } 
              else
                opStack.push(topStack);               

              if(tmp) {
                topStack = tStack.top();
                if(!opCheck(topStack)){
                  wcnt++;
                  wordStack.push(topStack);
                }
                else {
                  opStack.push(topStack);
                }
                tmp--;
                tStack.pop();
              }
            }
          }
          result = eval(tmp, wcnt, wordStack, opStack, tStack, stack, 
            result, output);                                      //SEND TO EVAL
          if(result == "Malformed")
            break;
        }

        if((lineSize == temp.size()) && (c != ')')){    //IF THERE ISN'T A PAREN
          while(!stack.empty()){            //REPEAT ABOVEW/O RESPECT TO THE ')'
            tStack.push(stack.top());
            tmp++;
            stack.pop();
          }

          while(tmp) {
            string topStack;

            topStack = tStack.top();
            tStack.pop();
            tmp--;

            int frnt = 0;
            int bck = 0;
            if(topStack == "<"){
              frnt++;
              while(tStack.top() == "<" || tStack.top() == ">" ) {
              if(tStack.top() == "<")
                frnt++;
              else if(tStack.top() == ">") 
                bck++;
              tStack.pop();
              tmp--;
            }
            topStack = tStack.top();

            if(!opCheck(topStack)) {
              wrd = topStack;
              topStack = removalCnt(frnt, bck, topStack);

              wordStack.push(topStack);
              wcnt++;
              tStack.pop();
              tmp--; 

              if(tmp) {
                if(opCheck(tStack.top())) {
                  opStack.push(tStack.top());
                  tmp--; 
                  tStack.pop();
                } 
              } 
            }
            }
            else if(topStack == ">"){
              bck++;
              while(tStack.top() == "<" || tStack.top() == ">" ) {
              if(tStack.top() == "<")
                frnt++;
              else if(tStack.top() == ">") 
                bck++;
              tStack.pop();
              tmp--;
            }
            topStack = tStack.top();

            if(!opCheck(topStack)) {
              wrd = topStack;
              topStack = removalCnt(frnt, bck, topStack);

              wordStack.push(topStack);
              wcnt++;
              tStack.pop();
              tmp--; 

              if(tmp) {
                if(opCheck(tStack.top())) {
                  opStack.push(tStack.top());
                  tmp--; 
                  tStack.pop();
                } 
              } 
            }
          }

            else {
              if(!opCheck(topStack)) {
                wordStack.push(topStack);
                wcnt++; 
              } 
              else
                opStack.push(topStack);

              if(tmp) {
                topStack = tStack.top();
                if(!opCheck(topStack)){
                  wcnt++;
                  wordStack.push(topStack);
                }
                else {
                  opStack.push(topStack);
                }
                tmp--;
                tStack.pop();
              }
            }
          } 
          result = eval(tmp, wcnt, wordStack, opStack, tStack, stack, 
            result, output);
        }        
      }
    }
    if(!valid(line))
      output << "Malformed" << endl;              //IF VALID FUNC FAILS, MALFORM
    else{
      output << result << endl;                          //OUTPUT RESULT TO FILE
    }
  }
  return 0;
}