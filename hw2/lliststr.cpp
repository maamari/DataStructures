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
		Item* traverser;						//while node exists

		if(temp->next) 							//traverse through linked-list
			traverser = temp->next;	

		delete temp;							//delete
		temp = traverser;						//and set the next node
	}		
	delete temp;								//reset head, tail, and size
}

int LListStr::size() const {
	return size_;								
}

bool LListStr::empty() const {					//returns size's bool value
	return(!size_);
}

void LListStr::insert(int pos, const string &val) {
	Item* ins = new Item();						//create node to be inserted
	ins->val = val;								//set it's value to val

	if(pos > size_ || pos < 0) return;			//bad case

	if(empty()) {								//EMPTY LIST INSERTION
        head_ = ins; tail_ = ins;
        ins->next = NULL; ins->prev = NULL;
	}
	else if(pos == size_) {						//TAIL INSERTION
		ins->next = head_; ins->prev = tail_; 	//insert
		tail_->next = ins; tail_ = ins;			//reposition tail
	}
	else if(pos == 0) {							//HEAD INSERTION
		ins->prev = tail_; ins->next = head_;	//insert
        head_->prev = ins; head_ = ins;			//reposition head
	}
	else {										//REGULAR INSERTION
		Item *inFront = posTraverser(pos);
		ins->next = inFront;
        ins->prev = inFront->prev;
        inFront->prev = ins;
        inFront->prev->next = ins;
	}
	size_++;									//increment size
}

void LListStr::remove(int pos) {
	if(pos < 0 || pos >= size_) return;			//bad case

	if(pos == 0){								//HEAD REMOVAL
		Item *temp = head_->next;
        delete head_; 
        head_ = temp;

    	if(size_ == 1){							//SINGULAR-NODE REMOVAL
			head_ = NULL; tail_ = NULL;
		}
	}	
	else if(pos == size_-1){					//TAIL REMOVAL
		Item *temp = tail_->prev;
        delete tail_; 
        tail_ = temp;
	}
	else{										//REGULAR REMOVAL
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
	if(pos >= size_|| pos < 0) 
		return "Invalid position."; 			//bad case
	else 
		return posTraverser(pos)->val;			//return the value at pos
}

LListStr::Item* LListStr::posTraverser(int pos){//gets node to position
	Item* current = head_;						//start at head
	int posCounter = 0;							//position counter

	if(!size_) return NULL;						//if empty, return NULL

	while(posCounter != pos){					//while not at position
		current = current->next;				//traverse
		posCounter++;
	}
	return current;								//return the node
}