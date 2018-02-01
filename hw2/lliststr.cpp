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
	Item* temp = head_;
		while(temp != tail_) {
			Item *traverser;						//while node exists
			if(temp->next) traverser = temp->next;	//traverse through
			delete temp;							//delete
			temp = traverser;						//and set the next node
		}		
		delete temp;								//reset head, tail, and size
}

int LListStr::size() const {					//DO I NEED THIS???
	return size_;								
}

bool LListStr::empty() const {					//returns size's bool value
	return(!size_);
}

void LListStr::insert(int pos, const string &val) {
	Item* insert = new Item();					//create node to be inserted
	insert->val = val;							//set it's value to val

	if(pos > size_ || pos < 0) return;			//bad case
	if(empty()) {								//insert to empty list
        head_ = insert; tail_ = insert;
        insert->next = NULL; insert->prev = NULL;
	}
	else if(pos == size_) {						//insert at tail
		insert->next = head_; insert->prev = tail_; 
		tail_->next = insert; tail_ = insert;
	}
	else if(pos == 0) {							//insert at head
		insert->prev = tail_; insert->next = head_;
        head_->prev = insert; head_ = insert;
	}
	else {										//otherwise
		Item *inFront = posTraverser(pos);
		insert->next = inFront;
        insert->prev = inFront->prev;
        inFront->prev = insert;
        inFront->prev->next = insert;
	}
	size_++;									//increment size
}

void LListStr::remove(int pos) {
	if(pos < 0 || pos >= size_) return;			//bad case
	if(pos == 0){								//remove from head
		Item *temp = head_->next;
        delete head_; head_ = temp;
        	if(size_ == 1){
				head_ = NULL; tail_ = NULL;
			}
	}	
	else if(pos == size_-1){					//remove from tail
		Item *temp = tail_->prev;
        delete tail_; tail_ = temp;
	}
	else{										//otherwise
		Item *curr = posTraverser(pos);
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
	}
	size_--;									//decrement size
}	

void LListStr::set(int pos, const string &val) {
	posTraverser(pos)->val = val;				//set the value of curr to val
}

string LListStr::get(int pos){
	if(pos >= size_|| pos < 0) return "Invald position."; //bad case
	else return posTraverser(pos)->val;			//return the value at pos
}

LListStr::Item* LListStr::posTraverser(int pos){	//gets node to position
	Item* current = head_;						//start at head
	int posCounter = 0;							//position counter

	if(!size_) return NULL;						//if empty, return NULL

	while(posCounter != pos){					//while not at position
		current = current->next;				//traverse
		posCounter++;
	}
	return current;								//return the node
}