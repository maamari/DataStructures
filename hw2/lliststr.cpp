#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "lliststr.h"

using namespace std;

LListStr::LListStr() {
	head_ = NULL;
	tail_ = NULL;
	size_ = 0;
}

LListStr::~LListStr() {
	fullClear();
}

int LListStr::size() const {
	return size_;
}

bool LListStr::empty() const {
	if(!size_) {
		return true;
	}
	else {
		return false;
	}
}

void LListStr::insert(int pos, const string &val) {
	Item* inFront = posTraverser(pos);
	Item* behind = posTraverser(pos-1);
	Item* newNode = new Item();	
	newNode -> val = val;

	if(empty()) {
		head_ = newNode; tail_ = newNode;
		newNode->prev = NULL; newNode->next = NULL;
	}
	else if(pos == 0) {
		head_->prev = newNode; head_ = newNode;
		newNode->prev = NULL; newNode->next = head_;
	}
	else if(pos == size_) {
		tail_->next = newNode; tail_ = newNode;
		newNode->prev = tail_; newNode->next = NULL;
	}
	else {
		newNode->next = inFront;
		behind->next = newNode;
		newNode->prev = behind;
		inFront->prev = newNode;
	}
	size_++;
}

void LListStr::remove(int pos) {
	if(!pos){
		Item* removed = head_;
		removed->next = NULL; removed->prev = NULL; removed->val = "";
	}
	else if(pos = size_){
		Item* removed = tail_;
		removed->next = NULL; removed->prev = NULL; removed->val = "";
	}
	else{
		Item* inFront = posTraverser(pos);
		Item* behind = posTraverser(pos-1);
		Item* removed = new Item();	

		behind->next = removed->next;
		inFront->prev = removed->prev;
		
		removed->next = NULL; removed->prev = NULL; removed->val = "";
	}
	size_--;
}

void LListStr::fullClear(){
	while(head_) {
		Item *temp = head_->next;
		delete head_;
		head_ = temp;
	}
	
	tail_ = NULL;
	size_ = 0;
}
	

void LListStr::set(int pos, const string &val) {
	Item* setNode = posTraverser(pos);

	setNode->val = val;
}

string LListStr::get(int pos){
	if(pos >= size_|| pos < 0) {
		cerr << "cmon man" << endl;
		return "";
	}
	else {
		Item* setNode = posTraverser(pos);
		return setNode->val;
	}
}

LListStr::Item* LListStr::posTraverser(int pos){
	Item* current = head_;

	if(!size_){
		return NULL;
	}

	int posCounter = 0;

	while(posCounter != pos){
		current = current->next;
		posCounter++;
	}
	return current;
}