#ifndef FUNCTOR_H
#define FUNCTOR_H
#include <string>
#include <iostream>

struct AplhaStrComp{
	bool operator()(const std :: string &lhs, const std ::  string &rhs){
		return lhs < rhs; 
	}
};

struct AplhaNumComp{
	bool operator()(const int &lhs, const int  &rhs){
		return lhs < rhs;
	}
};

struct LengthStrComp{
	bool operator()(const std :: string &lhs,const  std :: string &rhs){
		return lhs.size() < rhs.size(); 
	}
};

struct NumStrComp {
	bool operator()(const std :: string &lhs,const  std :: string &rhs);
};
#endif
