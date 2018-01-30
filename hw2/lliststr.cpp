#include <iostream>
#include "lliststr.h"

using namespace std;

LListInt::LListInt() {

	head_ = NULL;
	tail_ = NULL;
	size_ = 0;
}

LListInt::~LListInt() {
	while(head_) {
		Item *temp = head_->next;
		delete head_;
		head_ = temp;
	}
	
	tail_ = NULL;
	size_ = 0;
}

int LListInt::size() const {
	return size_;
}

bool LListInt::empty() const {
	if(!size_) {
		return true;
	}
	else {
		return false;
	}
}

void LListInt::insert(int pos, const std::string &val) {

}

void LListInt::remove(int pos) {
 
}

void LListInt::set(int pos, const std::string &val) {
 
}

std::string LListInt::get(int pos) const{
  
}