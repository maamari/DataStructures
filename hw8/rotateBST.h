#ifndef rotateBST_H
#define rotateBST_H

#include<iostream>
#include<string>
#include<exception>
#include<cstdlib>
#include <utility>
#include "bst.h"

template <typename Key, typename Value>
class rotateBST: public BinarySearchTree<Key,Value> {
public:
	//constructor
	rotateBST();
	//destructor
	virtual~rotateBST();
	bool sameKeys(const rotateBST& t2) const;
	void transform(rotateBST& t2) const;
protected:
	void leftRotate(Node<Key, Value>* r);
	void rightRotate(Node<Key, Value>* r);
private:
	//HELPER FUNCTIONS
	void updateheight(Node<Key,Value> *node);
	void transformHelper(Node<Key, Value> *node, rotateBST&) const;
	void fixTree(Node<Key, Value> *node, Node<Key, Value> *target, rotateBST&) const;
};

template <typename Key, typename Value>
void rotateBST<Key, Value> :: updateheight(Node<Key,Value> *node)
{
	//update affected node all the way to the root
	if(node!=NULL){

		//get left and right Children
		int right = 0;
		if(node->getRight() != NULL)right = node->getRight()->getHeight();
		int left = 0;
		if(node->getLeft() != NULL)left = node->getLeft()->getHeight();
		
		//if both are NULL then leafNode
		if(right == 0 && left == 0){
			node->setHeight(1);
		}
		//node has children
		else{
			//if right is bigger
			if(right > left){
				node->setHeight(right+1);
			}
			//left is bigger
			else if(left > right){
				node->setHeight(left+1);
			}
			//both children have same height
			else{
				node->setHeight(right+1);
			}
		}
		//recursive call until parent is updated
		updateheight(node->getParent());
	}	
}

//DEFINE THE FUNCTIONS-----------------------------
template <typename Key, typename Value>
rotateBST<Key,Value> ::rotateBST()
{
	//TODO
	this->mRoot = NULL;
}

template<typename Key, typename Value>
rotateBST<Key,Value> ::~rotateBST() 
{ 
	// TODO
	this->clear();
}

template <typename Key, typename Value>
bool rotateBST<Key,Value>:: sameKeys(const rotateBST& t2) const{
	//check if the node pass is a NULL pointer 
	typename rotateBST<Key,Value>::iterator it1(this->getSmallestNode());
	typename rotateBST<Key,Value>::iterator it2(t2.getSmallestNode());

	while(it1 != NULL || it2!= NULL){
		if(it1 == NULL || it2 == NULL){
			return false;
		}
		//increment both iterators
		++it1;
		++it2;
		if(it1 != NULL && it2 != NULL && it1->first != it2->first){
			return false;
		} 
	}

	//kalo semua bener
	return true;
}

template <typename Key, typename Value>
void rotateBST<Key,Value>::leftRotate(Node<Key,Value> *r){
		Node<Key,Value> *lChild = r->getRight();
		Node<Key,Value> *parent = r->getParent();

		if(r->getRight() != NULL){

			//parent of r
			if(parent == NULL){
				//root
				lChild->setParent(NULL);
				this->mRoot = lChild;

			}
			else{

				if(r->getKey() < parent->getKey()){//anak kiri

					lChild->setParent(parent);
					parent->setLeft(lChild);
				}
				else{
					//rightChild
					lChild->setParent(parent);
					parent->setRight(lChild);

				}
			}
			//lChild of lChild
			if(lChild->getLeft()!=NULL){

				r->setRight(lChild->getLeft());
				lChild->getLeft()->setParent(r);
			}
			else{
      			r->setRight(NULL);
     		}
      		//connection
			r->setParent(lChild);
			lChild->setLeft(r);
			updateheight(r);
		}
	
}

template <typename Key, typename Value>
void rotateBST<Key,Value>:: rightRotate(Node<Key,Value> *r){
	Node<Key,Value> *lChild = r->getLeft();
	Node<Key,Value> *parent = r->getParent();
	Node<Key, Value>* lChildsrChild = r->getLeft()->getRight();

	if(!lChild) return;
	if(lChildsrChild){
		r->setLeft(lChildsrChild);
		lChildsrChild->setParent(r);
	}
	else r->setLeft(NULL);
		//rootRotation
	if(!parent){
		//root
		lChild->setParent(NULL);
		this->mRoot = lChild;
	}
	else{
		//left lChild
		if(r->getKey() < parent->getKey()){
			lChild->setParent(parent);
			parent->setLeft(lChild);
		}
		else {//right lChild
			lChild->setParent(parent);
			parent->setRight(lChild);
		}
	}
	//lChild of lChild
	//update the height
	r->setParent(lChild);
	lChild->setRight(r);
	updateheight(r);
}

template <typename Key, typename Value>
void rotateBST<Key,Value>:: transformHelper(Node<Key, Value> *node, rotateBST& t2) const{
	//BC
	if(node == NULL){
		return;
	}

	while (node->getLeft() != NULL) {
		t2.rightRotate(node);
		node = node->getParent();
	}

	transformHelper(node->getRight(), t2);
}

template <typename Key, typename Value>
void rotateBST<Key,Value>:: fixTree(Node<Key, Value> *node, Node<Key, Value> *targetNode, rotateBST& t2) const{

	if (node == NULL || targetNode == NULL) return;

	Key target = targetNode->getKey();
	while (node->getKey() != target) {
		// tiap kali rotate right, value decreases
		if (node->getKey() > target) {
			t2.rightRotate(node);
		}

		// tiap kali rotate left, value increases
		if (node->getKey() < target) {
			t2.leftRotate(node);
		}

		node = node->getParent();
	}

	fixTree(node->getLeft(), targetNode->getLeft(), t2);
	fixTree(node->getRight(), targetNode->getRight(), t2);
}

template <typename Key, typename Value>
void rotateBST<Key,Value>:: transform(rotateBST& t2) const{
	//check if the node pass is a NULL pointer 
	if(t2.mRoot==NULL){
		return;
	}
	//if the keys are the same
	if(sameKeys(t2) == false){
		return;
	}
	else{
		//1. Perform right rotations on the root node of t2 until it has no left lChild.
		while (t2.mRoot->getLeft() != NULL) {
			t2.rightRotate(t2.mRoot);
		}

		//2.Recursively move to the right lChild and repeat the above operation.
		transformHelper(t2.mRoot->getRight(), t2);

		//3.This should produce a tree which is effectively a linked list. OK

		//4.Now perform left rotations on the root node of t2, until the root of t2 is the same as the root of this.
		while(t2.mRoot->getKey() != this->mRoot->getKey()){
			t2.leftRotate(t2.mRoot);
		}

		//5.Recursively do rotations on the left lChild and the right lChild until they match the node at that position of this.
		fixTree(t2.mRoot->getLeft(), this->mRoot->getLeft(), t2);
		fixTree(t2.mRoot->getRight(), this->mRoot->getRight(), t2);
	}
}

#endif