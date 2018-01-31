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
	Item* temp= head_;
	while(head_) {
		Item *traverser = head_->next;
		free(head_);
		head_ = traverser;
	}
	head_ = temp;
	head_ = NULL; tail_ = NULL; size_ = 0;
}

int LListStr::size() const {
	return size_;
}

bool LListStr::empty() const {
	return(!size_);
}

void LListStr::insert(int pos, const string &val) {
	Item* insert = new Item();	
	insert->val = val;

	if(pos > size_ || pos < 0){
		return;
	}
	if(empty()) {
        head_ = insert; tail_ = insert;
        insert->next = NULL; insert->prev = NULL;
	}
	else if(pos == size_) {
		insert->next = NULL; insert->prev = tail_; 
		tail_->next = insert; tail_ = insert;
	}
	else if(pos == 0) {
		insert->prev = NULL; insert->next = head_;
        head_->prev = insert; head_ = insert;
	}
	else {
		Item *inFront = posTraverser(pos);
		insert->next = inFront;
        insert->prev = inFront->prev;
        inFront->prev = insert;
        inFront->prev->next = insert;
	}
	size_++;
}

void LListStr::remove(int pos) {
	if(pos < 0 || pos >= size_){
		return;
	}
	if(pos == 0){
		Item *temp = head_->next;
        free(head_); head_ = temp;
	}
	else if(pos == size_-1){
		Item *temp = tail_->prev;
        free(tail_); tail_ = temp;
	}
	else{
		Item *curr = posTraverser(pos);
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        free(curr);
	}
	size_--;
}	

void LListStr::set(int pos, const string &val) {
	Item* setNode = posTraverser(pos);

	setNode->val = val;
}

string LListStr::get(int pos){
	if(pos >= size_|| pos < 0) {
		return "Error, invald position.";
	}
	else {
		Item* setNode = posTraverser(pos);
		return setNode->val;
	}
}

LListStr::Item* LListStr::posTraverser(int pos){
	Item* inFront = head_;
	int posCounter = 0;

	if(!size_){
		return NULL;
	}

	while(posCounter != pos){
		inFront = inFront->next;
		posCounter++;
	}
	return inFront;
}