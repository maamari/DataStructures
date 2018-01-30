#include <iostream>
#include "lliststr.h"

using namespace std;

LListStr::LListStr() {
	head_ = NULL;
	tail_ = NULL;
	size_ = 0;
}

LListStr::~LListStr() {
	while(head_) {
		Item *temp = head_->next;
		delete head_;
		head_ = temp;
	}
	
	tail_ = NULL;
	size_ = 0;
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

void LListStr::insert(int pos, const std::string &val) {
	Item* inFront = posTraverser(pos);
	Item* behind = posTraverser(pos-1);
	Item* newNode = new Item();	
	newNode -> val = val;

	if(empty()) {
		head_ = newNode;
		newNode->prev = NULL; newNode->next = NULL;
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
		Item *temp = head_->next;
        delete head_;
        head_ = temp;
	}
	else{
		Item* inFront = posTraverser(pos);
		Item* behind = posTraverser(pos-1);
		cout << "here" << endl;
		Item* removed = new Item();	

		behind->next = removed->next;
		inFront->prev = removed->prev;
		
		removed->next = NULL; removed->prev = NULL; removed->val = "";
	}
}
	

void LListStr::set(int pos, const std::string &val) {
	Item* setNode = posTraverser(pos);

	setNode->val = val;
}

std::string LListStr::get(int pos){
  	Item* setNode = posTraverser(pos);

	return setNode->val;
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