#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
* A templated class for a Node in a search tree. The getters for parent/left/right are virtual so that they
* can be overridden for future kinds of search trees, such as Red Black trees, Splay trees, and AVL trees.
*/
template <typename Key, typename Value>
class Node 
{
public:
	Node(const Key& key, const Value& value, Node<Key, Value>* parent);
	virtual ~Node();

	const std::pair<const Key, Value>& getItem() const;
	std::pair<const Key, Value>& getItem();
	const Key& getKey() const;
	const Value& getValue() const;
	Value& getValue();

	virtual Node<Key, Value>* getParent() const;
	virtual Node<Key, Value>* getLeft() const;
	virtual Node<Key, Value>* getRight() const;
	int getHeight() const;

	void setParent(Node<Key, Value>* parent);
	void setLeft(Node<Key, Value>* left);
	void setRight(Node<Key, Value>* right);
	void setValue(const Value &value);
	void setHeight(int height);

protected:
	std::pair<const Key, Value> mItem;
	Node<Key, Value>* mParent;
	Node<Key, Value>* mLeft;
	Node<Key, Value>* mRight;
	int mHeight;
};

/*
	-----------------------------------------
	Begin implementations for the Node class.
	-----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) 
	: mItem(key, value)
	, mParent(parent)
	, mLeft(NULL)
	, mRight(NULL)
	, mHeight(1)
{ 

} 

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node() 
{ 

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const 
{ 
	return mItem; 
}

/**
* A non-const getter for the item. 
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem() 
{ 
	return mItem; 
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const 
{ 
	return mItem.first; 
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const 
{ 
	return mItem.second; 
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
	return mItem.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const 
{ 
	return mParent; 
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const 
{ 
	return mLeft; 
}

/**
* An implementation of the virtual function for retreiving the right child. 
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const 
{ 
	return mRight; 
}

/**
* A const getter for the height.
*/
template<typename Key, typename Value>
int Node<Key, Value>::getHeight() const
{
	return mHeight;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent) 
{ 
	mParent = parent; 
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left) 
{ 
	mLeft = left; 
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right) 
{ 
	mRight = right; 
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value) 
{ 
	mItem.second = value; 
}

/**
* A setter for the height of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setHeight(int height) 
{ 
	mHeight = height;
}

/*
	---------------------------------------
	End implementations for the Node class.
	---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree 
{
	public:
		BinarySearchTree(); //TODO
		virtual ~BinarySearchTree(); //TODO
		int height(); //DONE 
		bool isBalanced(); //DONE 
		virtual void insert(const std::pair<const Key, Value>& keyValuePair); //DONE
		virtual void remove(const Key& key); //DONE
		void clear(); //TODO
		void print() const;

	public:
		/**
		* An internal iterator class for traversing the contents of the BST.
		*/
		class iterator 
		{
			public:
				iterator(Node<Key,Value>* ptr);
				iterator();

				std::pair<const Key, Value>& operator*();
				std::pair<const Key, Value>* operator->();

				bool operator==(const iterator& rhs) const;
				bool operator!=(const iterator& rhs) const;
				iterator& operator=(const iterator& rhs);

				iterator& operator++();

			protected:
				Node<Key, Value>* mCurrent;
		};

	public:
		iterator begin();
		iterator end();
		iterator find(const Key& key) const;

	protected:
		Node<Key, Value>* internalFind(const Key& key) const; //DONE
		Node<Key, Value>* getSmallestNode() const; //DONE
		void printRoot (Node<Key, Value>* root) const;

	protected:
		Node<Key, Value>* mRoot;

	//dont submit
	private:
		bool isBalanced_helper(Node<Key,Value> *node);//DONE
		void update_height(Node<Key,Value> *node);//DONE
		// Node<Key, Value>* internalFind_helper(const Key& key, Node<Key,Value> *target) const;//DONE

};

/*
	---------------------------------------------------------------
	Begin implementations for the BinarySearchTree::iterator class.
	---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value>* ptr)
	: mCurrent(ptr)
{ 

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator()
	: mCurrent(NULL)
{ 

}

/**
* Provides access to the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*() 
{ 
	return mCurrent->getItem();
}

/**
* Provides access to the address of the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->() 
{ 
	return &(mCurrent->getItem()); 
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent == rhs.mCurrent;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent != rhs.mCurrent;
}

/**
* Sets one iterator equal to another iterator.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &BinarySearchTree<Key, Value>::iterator::operator=(const BinarySearchTree<Key, Value>::iterator& rhs)
{
	this->mCurrent = rhs.mCurrent;
	return *this;
}

/**
* Advances the iterator's location using an in-order traversal.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++()
{
	if(mCurrent->getRight() != NULL)
	{
		mCurrent = mCurrent->getRight();
		while(mCurrent->getLeft() != NULL)
		{
			mCurrent = mCurrent->getLeft();
		}
	}
	else if(mCurrent->getRight() == NULL)
	{
		Node<Key, Value>* parent = mCurrent->getParent();
		while(parent != NULL &&  mCurrent == parent->getRight())
		{
			mCurrent = parent;
			parent = parent->getParent();
		}
		mCurrent = parent;
	}
	return *this;
}

/*
	-------------------------------------------------------------
	End implementations for the BinarySearchTree::iterator class.
	-------------------------------------------------------------
*/

/*
	-----------------------------------------------------
	Begin implementations for the BinarySearchTree class.
	-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{ 
	// TODO 
	//set the mRoot to NULL
	mRoot = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree() 
{ 
	// TODO
	//call the clear function
	clear();
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{ 
	printRoot(mRoot);
	std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin()
{
	BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
	return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end()
{
	BinarySearchTree<Key, Value>::iterator end(NULL);
	return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key& key) const 
{
	Node<Key, Value>* curr = internalFind(key);
	BinarySearchTree<Key, Value>::iterator it(curr);
	return it;
}

/**
* An method to return the height of the BST.
*/
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::height()
{
	// TODO
	//check if there is no tree
	if(mRoot == NULL){
		return 0;
	}
	//if there is a tree
	else {
		return mRoot->getHeight();
	}
}

//-------------------------DONE---------------------------------
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced_helper(Node<Key,Value> *node)
{
	
	//declare check node as root
	Node<Key, Value> *start = node;

	if(start == NULL){
		return true;
	}else{
		Node<Key, Value> *rightChild = start->getRight();

		Node<Key, Value> *leftChild = start->getLeft();

		//get left and right Children
		int right = 0;
		if(start->getRight() != NULL)right = rightChild->getHeight();
		int left = 0;
		if(start->getLeft() != NULL)left = leftChild->getHeight();


		//calculate difference
		int diff = abs(right-left);

		//check balance
		if(diff <= 1){
			return isBalanced_helper(rightChild)&&isBalanced_helper(leftChild);
		}
		else{
			return false;
		}
	}
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced()
{
	// TODO
	//check from the root
	return isBalanced_helper(mRoot);
}	

//-------------------------DONE---------------------------------

/**
* An insert method to insert into a Binary Search Tree. The tree will not remain balanced when 
* inserting.
*/

//--------------------------------------DONE----------------------------------------
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value>& keyValuePair)
{
	// TODO 
	//set temp node to root
	Node<Key,Value> *temp = mRoot;

	//if BST does not exist
	if(temp == NULL){
		//create first node of tree
		temp = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
		mRoot = temp;
		return;
	}
	else{
	//if a node exists
		Node<Key, Value> *parent = NULL;
		while (temp != NULL) {
			parent = temp;
			//save left node as temp
			if (keyValuePair.first < temp->getKey()){
				temp = temp->getLeft();
			}
			//save right node as temp
			else if (keyValuePair.first > temp->getKey()){
				temp = temp->getRight();
			} 
			//if node already exist
			else 
				return;
		}

		//when you finally insert node = NULL
		//if value is larger then insert right

		temp = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent);
		if(temp->getKey() > parent->getKey()){
			// temp = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent);
			// right child
			parent->setRight(temp);
			temp->setParent(parent);

			//update height
			while(parent->getHeight() <= temp->getHeight()){
				parent->setHeight(temp->getHeight()+1);
				if (parent == mRoot) break;
				//move to upper node
				temp = parent;
				parent = parent->getParent();
			}
		}
		//if value is the same just return
		else if(temp->getKey() < parent->getKey()){
			// temp = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent);
			// left child
			parent->setLeft(temp);
			temp->setParent(parent);

			//update height
			while(parent->getHeight() <= temp->getHeight()){
				parent->setHeight(temp->getHeight()+1);
				if (parent == mRoot) break;
				//move to upper node
				//supposed to fix this
				temp = parent;
				parent = parent->getParent();
			}
		
		}
		//if insert value already exist DO NOTHING
		else
			return;
	}
}
//--------------------------------------DONE----------------------------------------

//---------------------------------------DONE----------------------------------
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::update_height(Node<Key,Value> *node)
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
		update_height(node->getParent());
	}
}



/**
* An remove method to remove a specific key from a Binary Search Tree. The tree may not remain balanced after
* removal.
*/
//--------------------------------------DONE----------------------------------------
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
	// TODO
	//check if tree does not exist
	if(mRoot == NULL){
		return;
	}
	//when tree does exist
	else
	{
		//when the key is not found in the tree
		if(internalFind(key) == NULL){
			return;
		}
		//when key is found
		else{
			//get the node with corresponding key
			Node<Key, Value> *p = internalFind(key);
			//store the node's parents
			Node<Key, Value> *p_parent = p->getParent();
			// get predecessor of p
			Node<Key,Value> *leftChild = p->getLeft();
			//get right child
			Node<Key, Value> *rightChild = p->getRight();

			//THIS WORKS FINE -----------------------------------
			// if removing the root
			if (p_parent == NULL) {
				// if root doesn't have a predecessor
				if (leftChild == NULL) {
					// set successor as root
					if (p->getRight() != NULL) {
						mRoot = p->getRight();
						mRoot->setParent(NULL);
						// delete p;
					}
					// if it's the only node, set mRoot to NULL
					else {
						mRoot = NULL;
					}
				} //THIS WORKS FINE -----------------------------------
				// WORKS FINE -----------------------------------------
				// if root has a predecessor
				//left child not NULL
				else {
					//if right is NULL promote left
					if(rightChild == NULL){
						//promote leftChild
						mRoot = leftChild;
						mRoot->setParent(NULL);
						// delete p;
					}
					else if(rightChild != NULL){
						// iterate to get predecessors
						Node<Key, Value> *predecessor = leftChild;
						while(predecessor->getRight()!=NULL){
							predecessor = predecessor->getRight();
						}
						Node<Key, Value> *predecessor_parent = predecessor->getParent();
						Node<Key, Value> *predecessor_leftChild = predecessor->getLeft();
						if(predecessor->getParent() != p){
							// if predecessor has a left child (predecessor can't have a right child)
							if (predecessor_leftChild != NULL) {
								// connect the left child to predecessor's parent
								predecessor_parent->setRight(predecessor->getLeft()); 
								predecessor_leftChild->setParent(predecessor->getParent());
							}
							else {
								predecessor_parent->setRight(NULL);
							}

						}
						// set predecessor as root since we're removing current root
						predecessor->setParent(NULL);
						Node<Key, Value> *pRight = p->getRight();
						Node<Key, Value> *pLeft = p->getLeft();
						mRoot = predecessor;
						predecessor->setRight(pRight);
						p->getRight()->setParent(predecessor);

						bool flag_direct = true;
						if(p->getLeft()->getKey()!=predecessor->getKey()){
							predecessor->setLeft(pLeft);
							p->getLeft()->setParent(predecessor);
							flag_direct = false;
						}
						mRoot = predecessor;
						predecessor->setParent(NULL);
						//update height predecessor_parent
						if(flag_direct){
							update_height(mRoot);
						}else{
							update_height(predecessor_parent);	
						}

						// delete p;
					}
				}

			}// WORKS FINE -----------------------------------------
			// if not removing from root
			else {
				// if doesn't have predecessor, replace with successor
				if (leftChild == NULL) {
					// if it doesn't have a rightChild, then it's a leaf node
					if (p->getRight() == NULL) {
						// if p is parent's left child
						if (p->getKey() < p_parent->getKey()) {
							p_parent->setLeft(NULL);
							// delete p;
						}

						else if (p->getKey() > p_parent->getKey()){
							p_parent->setRight(NULL);
							// delete p;
						}
						//update height parent
						update_height(p_parent);
					}
					//RIGHT CHILD NOT NULL
					else {
						Node<Key, Value> *rightChild = p->getRight();

						if (p->getKey() < p_parent->getKey()) {
							p_parent->setLeft(rightChild);
							rightChild->setParent(p_parent);

						}
						else if (p->getKey() > p_parent->getKey()){
							p_parent->setRight(rightChild);
							rightChild->setParent(p_parent);
						}
						//update height parent
						// delete p;
						update_height(p_parent);
					}
				}
				// replace with predecessor 
				else if(leftChild != NULL){
					//IF RIGHT CHILD EXIST
					bool flag_direct = true;
					if(rightChild != NULL){
						// iterate from leftChild to get predecessor
						Node<Key, Value> *predecessor = leftChild;
						while(predecessor->getRight() != NULL)
						{
							flag_direct = false;
							predecessor = predecessor->getRight();
						}
						// if p is parent's left child
						if (p->getKey() < p_parent->getKey()) {
							if(flag_direct!=true){

								if(predecessor->getLeft() != NULL){
									predecessor->getParent()->setRight(predecessor->getLeft());
									predecessor->getLeft()->setParent(predecessor->getParent());
								}else
								{
									predecessor->getParent()->setRight(NULL);
								}
							}
							// handle parent
							p_parent->setLeft(predecessor);
							//store parent
							Node<Key, Value> *tparent = predecessor->getParent(); 
							predecessor->setParent(p_parent);
							// handle children (automatically set to NULL if they don't exist)
							if(flag_direct != true){
								predecessor->setLeft(p->getLeft());
								predecessor->getLeft()->setParent(predecessor);
							}
							// if p has a right child, set its parent
							if (p->getRight() != NULL) {

								predecessor->setRight(p->getRight());

								p->getRight()->setParent(predecessor);
							}
							//update height tparent
							if(flag_direct!=true){
								update_height(tparent);	
							}
							else{
								update_height(predecessor);
							}
							// delete p;
							//WORKS FINE--------------------------------
						}
						// if p is parent's right child WORKS FINE ---------------
						else if (p->getKey() > p_parent->getKey()) {
							if(flag_direct!=true){
								if(predecessor->getLeft() != NULL){
									predecessor->getParent()->setRight(predecessor->getLeft());
									predecessor->getLeft()->setParent(predecessor->getParent());
								}
								else{
									predecessor->getParent()->setRight(NULL);
								}
							}
							//-----Connectring The Predecessor-----/
							Node<Key, Value> *tparent = predecessor->getParent(); // 1
							//set parent Right Child to predecessor
							p_parent->setRight(predecessor);
							//set predecessor parent to p_parent
							predecessor->setParent(p_parent);
							//-----Connectring The Predecessor-----/
							if(flag_direct != true){
								predecessor->setLeft(p->getLeft());
								predecessor->getLeft()->setParent(predecessor);
							}
							// if p has a right child, set its parent
							if (p->getRight() != NULL) {
								predecessor->setRight(p->getRight());
								p->getRight()->setParent(predecessor);
							}
							//update height tparent
							if(flag_direct!=true){
								update_height(tparent);	
							}
							else{
								update_height(predecessor);
							}
							// delete p;
						}
					}
					//RIGHT CHILD DOES NOT EXIST
					else{
						p->getLeft()->setParent(p_parent);
						if(p->getKey() < p_parent->getKey()){
							p_parent->setLeft(p->getLeft());
						}
						else{
							p_parent->setRight(p->getLeft());
						}
						//update height p_parent
						update_height(p_parent);
						// delete p;
					}
				}
			}
			//deallocate the deleted pointer
			delete p;
		}
	}
}
//--------------------------------------DONE----------------------------------------
/**
* A method to remove all contents of the tree and reset the values in the tree 
* for use again.
*/

//--------------------------------------DONE----------------------------------------
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
	// TODO
	while(mRoot != NULL){
		remove(mRoot->getKey());
	}
}
//--------------------------------------DONE----------------------------------------

/**
* A helper function to find the smallest node in the tree.
*/

//--------------------------------------DONE----------------------------------------
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const
{
	// TODO
	//check if there is no tree
	if(mRoot == NULL){
		return NULL;
	}
	//if tree exist
	else{
		//set smallest node to mRoot
		Node<Key,Value> *smallestNode = mRoot;
		//keep moving left
		while(smallestNode->getLeft()!=NULL){
			smallestNode = smallestNode->getLeft();
		}
		return smallestNode;
	}

	//by default
	return NULL;
}
//--------------------------------------DONE----------------------------------------

/**
* Helper function to find a node with given key, k and 
* return a pointer to it or NULL if no item with that key
* exists
*/
//--------------------------------------DONE----------------------------------------

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const 
{
	// TODO	

	//start at the root
	Node<Key,Value> *target = mRoot;
  	while(true){
		if(target == NULL){
			return NULL;
		}
		else{
			//if found
			if(target->getKey() == key){
				return target;
			}
			else{
				//smaller 
				if(key < target->getKey()){
					//if
					target = target->getLeft();
				}
				else if(key > target->getKey()){
					//if
					target = target->getRight();
				}
			}
		}
  	}
}
//--------------------------------------DONE----------------------------------------

/**
* Helper function to print the tree's contents
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::printRoot (Node<Key, Value>* root) const
{	
 	if (root != NULL)
	{
		std::cout << "[";
		printRoot (root->getLeft());
		std::cout << " (" << root->getKey() << ", " << root->getValue() << ") ";
		printRoot (root->getRight());
		std::cout << "]";
	}
}
/*
	---------------------------------------------------
	End implementations for the BinarySearchTree class.
	---------------------------------------------------
*/

#endif
