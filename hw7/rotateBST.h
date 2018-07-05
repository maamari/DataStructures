#ifndef ROTATE_H
#define ROTATE_H
#include "bst.h"
#include <set>

template <typename Key, typename Value>
class rotateBST : public BinarySearchTree<Key, Value>{
protected:
	void leftRotate(Node<Key, Value>* r);
	void rightRotate(Node<Key, Value>* r);

public:
	bool sameKeys(const rotateBST& t2) const;
	void transform(rotateBST& t2) const;

private:
	void key_helper(Node<Key, Value> *node, std::set<Key> one);
	void set_helper(bool lOr, Node<Key, Value>* r, Node<Key, Value>* child,
				    Node<Key, Value>* rChildslChild, Node<Key, Value>* parent);
};

template <typename Key, typename Value>
void rotateBST<Key, Value>::set_helper(bool lOr, Node<Key, Value>* r, Node<Key,
 Value>* child, Node<Key, Value>* rlChild, Node<Key, Value>* parent){
	if(!lOr) {
		child->setLeft(r); child->setParent(parent);
		r->setParent(child); r->setRight(rlChild);
	}
	else {
		child->setRight(r); child->setParent(parent);
		r->setParent(child); r->setLeft(rlChild);
	}
}

template <typename Key, typename Value>
void rotateBST<Key, Value>::leftRotate(Node<Key, Value>* r) {
	Node<Key, Value>* rChild = r->getRight();
	Node<Key, Value>* parent = r->getParent();
	Node<Key, Value>* rChildslChild = r->getRight()->getLeft();
	bool lOr = false;
	set_helper(lOr, r, r->getRight(), r->getRight()->getLeft(), r->getParent());

	if(!rChild) return;
	if(rChildslChild) r->getRight()->getLeft()->setParent(r);
	if(parent && (parent->getRight() == r)) r->getParent()->setRight(rChild);
	if(parent && (parent->getLeft() == r)) r->getParent()->setLeft(rChild);

	else (*this).mRoot = rChild;
	rChild->setHeight(r->getHeight());
	r->setHeight(rChild->getHeight());
}

template <typename Key, typename Value>
void rotateBST<Key, Value>::rightRotate(Node<Key, Value>* r){
	Node<Key, Value>* lChild = r->getLeft();
	Node<Key, Value>* parent = r->getParent();
	Node<Key, Value>* lChildsrChild = r->getLeft()->getRight();
	bool lOr = true;
	set_helper(lOr, r, r->getLeft(), lChild->getRight(), r->getParent());

	if(!lChild) return;
	if(lChildsrChild) r->getLeft()->getRight()->setParent(r);
	if(parent && (parent->getRight() == r)) r->getParent()->setRight(lChild);
	if(parent && (parent->getLeft() == r)) r->getParent()->setLeft(lChild);

	else (*this).mRoot = lChild;
	lChild->setHeight(r->getHeight());
	r->setHeight(lChild->getHeight());
}

template <typename Key, typename Value>
void key_helper(Node<Key, Value> *node, std::set<Key> one){
	one.insert(node->getKey());
	node = node->getRight();
	while(node) one.insert(node->getKey());
	node = node->getLeft();
	while(node) one.insert(node->getKey());
}

template <typename Key, typename Value>
bool rotateBST<Key, Value>::sameKeys(const rotateBST& t2) const{
	std::set<Key> one, two;

	Node<Key, Value> *node = (*this).mRoot;
	if(!node) return false;
	key_helper(node, one);
	// one.insert(node->getKey());
	// node = node->getRight();
	// while(node) one.insert(node->getKey());
	// node = node->getLeft();
	// while(node) one.insert(node->getKey());

	Node<Key, Value> * node1 = t2.mRoot;
	if(!node1) return false;
	key_helper(node1, two);
	// two.insert(node1->getKey());
	// node1 = node1->getRight();
	// while(node1) two.insert(node1->getKey());
	// node1 = node1->getLeft();
	// while(node1) two.insert(node1->getKey());

	if(one == two) return true;
	else return false;
}

template <typename Key, typename Value>
void rotateBST<Key, Value>::transform(rotateBST& t2) const{}

#endif