#include "rotateBST.h"
#include "bst.h"

template <typename Key, typename Value>
class SplayTree : public rotateBST <Key, Value>{
	public:
		SplayTree();
		void insert(const std::pair<const Key, Value>& keyValuePair); 
		void remove(const Key& key); 
		typename SplayTree<Key, Value>::iterator find(const Key& key); 
		typename SplayTree<Key, Value>::iterator findMin(); 
		typename SplayTree<Key, Value>::iterator findMax(); 
		void deleteMinLeaf(); 
		void deleteMaxLeaf(); 

	protected:
		void splay(Node<Key, Value>*r); 
};

template <typename Key, typename Value>
SplayTree<Key, Value>::SplayTree(){
	this->mRoot = NULL;
}

//SPLAY METHOD, CONTAINS ZIG ZAGS
template <typename Key, typename Value>
void SplayTree<Key, Value>::splay(Node<Key, Value>*r){
	if(!r || !this->mRoot || (r == this->mRoot)) return;

	Node<Key, Value>*parent = r->getParent();
	Node<Key, Value>*grandparnt = parent->getParent();
	int state = 0;

	if(r == this->mRoot->getRight()) rotateBST<Key, Value>::leftRotate(parent);
	else if(r == this->mRoot->getLeft()) rotateBST<Key, Value>::rightRotate(parent);
	else {
		if(grandparnt->getLeft() && (grandparnt->getLeft()->getLeft() == r)) state = 1;
		else if(grandparnt->getLeft() && (grandparnt->getLeft()->getRight() == r)) state = 2;
		else if(grandparnt->getRight() && (grandparnt->getRight()->getRight() == r)) state = 3;
		else if(grandparnt->getRight() && (grandparnt->getRight()->getLeft() == r)) state = 4;

		//ZIGZAGS
		if(state == 1){
			rotateBST<Key, Value>::rightRotate(grandparnt);
			rotateBST<Key, Value>::rightRotate(parent);
		}
		if(state == 2){
			rotateBST<Key, Value>::leftRotate(parent);
			rotateBST<Key, Value>::rightRotate(grandparnt);
		}
		if(state == 3){
			rotateBST<Key, Value>::leftRotate(grandparnt);
			rotateBST<Key, Value>::leftRotate(parent);
		}
		if(state == 4){
			rotateBST<Key, Value>::rightRotate(parent);
			rotateBST<Key, Value>::leftRotate(grandparnt);
		}
	}
	splay(r);
}


//FIND METHODS: FIND, FINDMIN, FINDMAX
template <typename Key, typename Value>
typename SplayTree<Key, Value>::iterator 
SplayTree<Key, Value>::find(const Key& key){
	Node<Key, Value>*pre = NULL;
	Node<Key, Value>*curr = this->mRoot;

	while(curr){
		pre = curr;
		if(curr->getKey() == key) break;
		else if(curr->getKey() > key) curr = curr->getLeft();
		else curr = curr->getRight();
		continue;
	}

	splay(pre);
	typename SplayTree<Key, Value>::iterator end(curr);
	return end;
}

	
template <typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::findMin(){
	Node<Key, Value>*mn = this->mRoot;
	typename SplayTree<Key, Value>::iterator it(NULL);

	if(!this->mRoot) return it;
	while(mn->getLeft()) mn = mn->getLeft();

	splay(mn);
	typename SplayTree<Key, Value>::iterator min(mn);
	return min;
}
 
template <typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::findMax(){
	Node<Key, Value>* mx = this->mRoot;
	typename SplayTree<Key, Value>::iterator end(NULL);

	if(!this->mRoot ) return end;
	while(mx->getRight()) mx = mx->getRight();

	splay(mx);
	typename SplayTree<Key, Value>::iterator max(mx);
	return max;
}

//INSERTION METHOD
template <typename Key, typename Value>
void SplayTree<Key,Value>::insert(const std::pair<const Key, Value>& keyValuePair){
	Node<Key, Value>* parent = NULL;
	Node<Key, Value>* curr = this->mRoot;
	Node<Key, Value>* n;

	while(curr){
		parent = curr;
		if(curr->getKey() == keyValuePair.first) break;
		else if(curr->getKey() > keyValuePair.first) curr = curr->getLeft();
		else curr = curr->getRight();
		continue;
	}

	if(!curr){
		if(!this->mRoot){
			n = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
			this->mRoot = n;
			splay(n);
			return;
		}

		n = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent);

		if(n->getKey() > parent->getKey()) parent->setRight(n);
		else parent->setLeft(n);
		splay(n);
	}			
	else splay(curr);
}


//REMOVAL METHODS: REMOVE, DELETEMINLEAF, DELETEMAXLEAF
template <typename Key, typename Value>
void SplayTree<Key,Value>::remove(const Key& key){
	Node<Key, Value>* pre = NULL;
	Node<Key, Value>* curr = this->mRoot;

	while(curr){
		pre = curr;
		if(curr->getKey() == key) break;
		else if(curr->getKey() > key) curr = curr->getLeft();
		else curr = curr->getRight();
		continue;
	}
			
	if(curr){
		if(!curr) return;
		Node<Key, Value>* pred = curr->getParent();
		if(curr->getRight() || curr->getLeft()){
			if(curr->getLeft()) pred = curr->getLeft();
			if(curr->getRight()) pred = curr->getRight();
			if(curr->getRight() && curr->getLeft()){
				while(pred->getRight()) pred = pred->getRight();
				if(pred->getParent() != curr) pred = pred->getParent();
			}
		}
		BinarySearchTree<Key, Value>::remove(curr->getKey());
		splay(pred);
	} 
	else splay(pre);
}

template <typename Key, typename Value>
void SplayTree<Key,Value>::deleteMinLeaf(){
	if(this->mRoot){
		Node<Key, Value>* mn = this->mRoot;
		while(mn->getLeft() || mn->getRight()){
			if(mn->getLeft()) mn = mn->getLeft();
			else if(mn->getRight()) mn = mn->getRight();
			else break;
		}
		if(!mn) return;
		Node<Key, Value>* pred = mn->getParent();
		if(mn->getRight() || mn->getLeft()){
			if(mn->getLeft()) pred = mn->getLeft();
			if(mn->getRight()) pred = mn->getRight();
			if(mn->getRight() && mn->getLeft()){
				while(pred->getRight()) pred = pred->getRight();
				if(pred->getParent() != mn) pred = pred->getParent();
			}
		}
		BinarySearchTree<Key, Value>::remove(mn->getKey());
		splay(pred);
	} 
	else return;
}

template <typename Key, typename Value>
void SplayTree<Key,Value>::deleteMaxLeaf(){
	if(this->mRoot) {
		Node<Key, Value>* mx = this->mRoot;
		while(mx->getRight() || mx->getLeft()){
			if(mx->getRight()) mx = mx->getRight();
			else if(mx->getLeft()) mx = mx->getLeft();
		}
		if(!mx) return;
		Node<Key, Value>* pred = mx->getParent();
		if(mx->getRight() || mx->getLeft()){
			if(mx->getLeft()) pred = mx->getLeft();
			if(mx->getRight()) pred = mx->getRight();
			if(mx->getRight() && mx->getLeft()){
				while(pred->getRight()) pred = pred->getRight();
				if(pred->getParent() != mx) pred = pred->getParent();
			}
		}
		BinarySearchTree<Key, Value>::remove(mx->getKey());
		splay(pred);
	}
	else return;
}

