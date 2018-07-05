#ifndef BST_H
#define BST_H
#include <cstdlib>
#include <exception>
#include <iostream>
#include <utility>

/**
 * A templated class for a Node in a search tree. The getters for
 * parent/left/right are virtual so that they can be overridden for future kinds
 * of search trees, such as Red Black trees, Splay trees, and AVL trees.
 */
template <typename Key, typename Value> class Node {
public:
  Node(const Key &key, const Value &value, Node<Key, Value> *parent);
  virtual ~Node();

  const std::pair<const Key, Value> &getItem() const;
  std::pair<const Key, Value> &getItem();
  const Key &getKey() const;
  const Value &getValue() const;
  Value &getValue();

  virtual Node<Key, Value> *getParent() const;
  virtual Node<Key, Value> *getLeft() const;
  virtual Node<Key, Value> *getRight() const;
  int getHeight() const;

  void setParent(Node<Key, Value> *parent);
  void setLeft(Node<Key, Value> *left);
  void setRight(Node<Key, Value> *right);
  void setValue(const Value &value);
  void setHeight(int height);

protected:
  std::pair<const Key, Value> mItem;
  Node<Key, Value> *mParent;
  Node<Key, Value> *mLeft;
  Node<Key, Value> *mRight;
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
template <typename Key, typename Value>
Node<Key, Value>::Node(const Key &key, const Value &value,
                       Node<Key, Value> *parent)
    : mItem(key, value), mParent(parent), mLeft(NULL), mRight(NULL),
      mHeight(1) {}

/**
 * Destructor, which does not need to do anything since the pointers inside of a
 * node are only used as references to existing nodes. The nodes pointed to by
 * parent/left/right are freed within the deleteAll() helper method in the
 * BinarySearchTree.
 */
template <typename Key, typename Value> Node<Key, Value>::~Node() {}

/**
 * A const getter for the item.
 */
template <typename Key, typename Value>
const std::pair<const Key, Value> &Node<Key, Value>::getItem() const {
  return mItem;
}

/**
 * A non-const getter for the item.
 */
template <typename Key, typename Value>
std::pair<const Key, Value> &Node<Key, Value>::getItem() {
  return mItem;
}

/**
 * A const getter for the key.
 */
template <typename Key, typename Value>
const Key &Node<Key, Value>::getKey() const {
  return mItem.first;
}

/**
 * A const getter for the value.
 */
template <typename Key, typename Value>
const Value &Node<Key, Value>::getValue() const {
  return mItem.second;
}

/**
 * A non-const getter for the value.
 */
template <typename Key, typename Value> Value &Node<Key, Value>::getValue() {
  return mItem.second;
}

/**
 * An implementation of the virtual function for retreiving the parent.
 */
template <typename Key, typename Value>
Node<Key, Value> *Node<Key, Value>::getParent() const {
  return mParent;
}

/**
 * An implementation of the virtual function for retreiving the left child.
 */
template <typename Key, typename Value>
Node<Key, Value> *Node<Key, Value>::getLeft() const {
  return mLeft;
}

/**
 * An implementation of the virtual function for retreiving the right child.
 */
template <typename Key, typename Value>
Node<Key, Value> *Node<Key, Value>::getRight() const {
  return mRight;
}

/**
 * A const getter for the height.
 */
template <typename Key, typename Value>
int Node<Key, Value>::getHeight() const {
  return mHeight;
}

/**
 * A setter for setting the parent of a node.
 */
template <typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value> *parent) {
  mParent = parent;
}

/**
 * A setter for setting the left child of a node.
 */
template <typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value> *left) {
  mLeft = left;
}

/**
 * A setter for setting the right child of a node.
 */
template <typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value> *right) {
  mRight = right;
}

/**
 * A setter for the value of a node.
 */
template <typename Key, typename Value>
void Node<Key, Value>::setValue(const Value &value) {
  mItem.second = value;
}

/**
 * A setter for the height of a node.
 */
template <typename Key, typename Value>
void Node<Key, Value>::setHeight(int height) {
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
		int height(); //TODO 
		bool isBalanced(); //TODO 
		virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
		virtual void remove(const Key& key); //TODO
		void clear(); //TODO
		void print() const;

	public:
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
		Node<Key, Value>* internalFind(const Key& key) const; //TODO
		Node<Key, Value>* getSmallestNode() const; //TODO
		void printRoot (Node<Key, Value>* root) const;

	protected:
		Node<Key, Value>* mRoot;

	//helper function
	private:
		void clear_help(Node<Key, Value>* node);
		void height_help(Node<Key, Value> *root);
};
/*
        ---------------------------------------------------------------
        Begin implementations for the BinarySearchTree::iterator class.
        ---------------------------------------------------------------
*/

/**
 * Explicit constructor that initializes an iterator with a given node pointer.
 */
template <typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key, Value> *ptr)
    : mCurrent(ptr) {}

/**
 * A default constructor that initializes the iterator to NULL.
 */
template <typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator() : mCurrent(NULL) {}

/**
 * Provides access to the item.
 */
template <typename Key, typename Value>
std::pair<const Key, Value> &BinarySearchTree<Key, Value>::iterator::
operator*() {
  return mCurrent->getItem();
}

/**
 * Provides access to the address of the item.
 */
template <typename Key, typename Value>
std::pair<const Key, Value> *BinarySearchTree<Key, Value>::iterator::
operator->() {
  return &(mCurrent->getItem());
}

/**
 * Checks if 'this' iterator's internals have the same value
 * as 'rhs'
 */
template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::
operator==(const BinarySearchTree<Key, Value>::iterator &rhs) const {
  return this->mCurrent == rhs.mCurrent;
}

/**
 * Checks if 'this' iterator's internals have a different value
 * as 'rhs'
 */
template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::
operator!=(const BinarySearchTree<Key, Value>::iterator &rhs) const {
  return this->mCurrent != rhs.mCurrent;
}

/**
 * Sets one iterator equal to another iterator.
 */
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &
BinarySearchTree<Key, Value>::iterator::
operator=(const BinarySearchTree<Key, Value>::iterator &rhs) {
  this->mCurrent = rhs.mCurrent;
  return *this;
}

/**
 * Advances the iterator's location using an in-order traversal.
 */
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &
BinarySearchTree<Key, Value>::iterator::operator++() {
  if (mCurrent->getRight()) {
    mCurrent = mCurrent->getRight();
    while (mCurrent->getLeft()) {
      mCurrent = mCurrent->getLeft();
    }
  } else if (mCurrent->getRight() == NULL) {
    Node<Key, Value> *parent = mCurrent->getParent();
    while (parent && mCurrent == parent->getRight()) {
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
template<typename Key, typename Value>				//DONE
BinarySearchTree<Key, Value>::BinarySearchTree() { 
	mRoot = NULL;
}

template<typename Key, typename Value>				//DONE
BinarySearchTree<Key, Value>::~BinarySearchTree() { 
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
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() {
  BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
  return begin;
}

/**
 * Returns an iterator whose value means INVALID
 */
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() {
  BinarySearchTree<Key, Value>::iterator end(NULL);
  return end;
}

/**
 * Returns an iterator to the item with the given key, k
 * or the end iterator if k does not exist in the tree
 */
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key &key) const {
  Node<Key, Value> *temp = internalFind(key);
  BinarySearchTree<Key, Value>::iterator it(temp);
  return it;
}
/**
* An method to return the height of the BST.
*/
template<typename Key, typename Value>				//DONE
int BinarySearchTree<Key, Value>::height() {
	if(mRoot)return (mRoot)->getHeight();
	else return 0; 
}


/*
* An method to checks if the BST is balanced. This method returns true if and only if the BST is balanced.
*/
template<typename Key, typename Value>				//DONE
bool BinarySearchTree<Key, Value>::isBalanced()
{
	if(!mRoot) return true;

	Node<Key, Value>* l = (mRoot)->getLeft();
	Node<Key, Value>* r = (mRoot)->getRight();
	int lHeight, rHeight;

	if(l) lHeight = l->getHeight();
	else lHeight = 0;

	if(r) rHeight = r->getHeight();
	else rHeight = 0;

	int diff1 = lHeight - rHeight;
	int diff2 = rHeight - lHeight;
	if(lHeight == rHeight) return true;
	else if(lHeight > rHeight) return (diff1 == 1);
	else return (diff2 == 1);
}

/**
* An insert method to insert into a Binary Search Tree. The tree will not remain balanced when 
* inserting.
*/
template<typename Key, typename Value>				//DONE
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value>& keyValuePair) 
{
	if(!mRoot) mRoot = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
	else if(!internalFind(keyValuePair.first)){
		Node<Key, Value>* temp = mRoot;
		Node<Key, Value>* parent = mRoot;
		bool lOr;

		if(keyValuePair.first > (*temp).getKey()) lOr = 1;
		else lOr = 0;

		if(lOr) temp = (*mRoot).getRight();
		else temp = (*mRoot).getLeft();

		while(temp){
			parent = temp;
			if(keyValuePair.first > (*temp).getKey()){ 
				temp = (*temp).getRight();
				lOr = 1;
			}
			else{ 	
				temp = (*temp).getLeft();
				lOr = 0;
			}
		}

		Node<Key, Value> *newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent);

		if(lOr) parent->setRight(newNode);
		else parent->setLeft(newNode);

		Node<Key, Value>* back = parent;
		if(!parent->getLeft() || !parent->getRight()){
			while(back){
				back->setHeight(back->getHeight()+1);
				back = back->getParent();
			}
		}
	}
}

template <typename Key, typename Value>				//DONE
void BinarySearchTree<Key, Value>::height_help(Node<Key, Value> *root) {
  while (root) {
    Node<Key, Value> *ri = root->getRight();
    Node<Key, Value> *le = root->getLeft();
    int rightHeight, leftHeight;
    bool r = false, l = false;
    if(!ri || !le){
    	if(!ri) r = true;
    	if(!le) l = true;
    }
    if (r) rightHeight = 0;
    else rightHeight = ri->getHeight();
    if (l) leftHeight = 0; 
    else leftHeight = le->getHeight();

    if (leftHeight > rightHeight) {
      root->setHeight(++leftHeight);
      root = root->getParent();
    } 
    else {
      root->setHeight(++rightHeight);
      root = root->getParent();
    }
  }
}

/**
* An remove method to remove a specific key from a Binary Search Tree. The tree may not remain balanced after
* rmvNode.
*/
template<typename Key, typename Value>				//DONE
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
	Node<Key, Value> *removeNode = internalFind(key);
	if (!removeNode) return;

	if (!removeNode->getLeft() && !removeNode->getRight()) {
		if (!(removeNode->getParent())) mRoot = NULL;
		else if (removeNode->getParent()->getLeft() == removeNode) removeNode->getParent()->setLeft(NULL);
		else removeNode->getParent()->setRight(NULL);
		if(removeNode->getParent()) height_help(removeNode->getParent());
	}

	else if (!(removeNode->getRight()) || !(removeNode->getLeft())) {
		bool rOl = false;
		if(!(removeNode->getRight()))
			rOl = true;
		if(!(removeNode->getLeft()))
			rOl = false;
		if (removeNode->getParent()) {
			if (removeNode->getParent()->getRight() == removeNode){
				if(rOl)
					removeNode->getParent()->setRight(removeNode->getLeft());
				else
					removeNode->getParent()->setRight(removeNode->getRight());
			}
			else {
				if(rOl)
					removeNode->getParent()->setLeft(removeNode->getLeft());
				else
					removeNode->getParent()->setLeft(removeNode->getRight());
			}
		} 
		else {
			if(rOl)
				mRoot = removeNode->getLeft();
			else
				mRoot = removeNode->getRight();
		}
		if(rOl)
	    	removeNode->getLeft()->setParent(removeNode->getParent());
	    else
	    	removeNode->getRight()->setParent(removeNode->getParent());
	    if (removeNode->getParent()) {
	      height_help(removeNode->getParent());
	    }
	}

	else {
		Node<Key, Value> *pred = removeNode->getLeft();
		Node<Key, Value> *right = removeNode->getRight();
		while (pred->getRight()) pred = pred->getRight();
		Node<Key, Value> *removeNodeParent = removeNode->getParent();
		Node<Key, Value> *predParent = pred->getParent();

		if (removeNode == predParent) {
		  pred->setParent(removeNodeParent);

			if (!removeNodeParent) mRoot = pred; 
			else {
				if (removeNodeParent->getRight() == removeNode) removeNodeParent->setRight(pred); 
				else removeNodeParent->setLeft(pred);
			}

			pred->setRight(removeNode->getRight());
			right->setParent(removeNode);
			height_help(pred);
			delete removeNode;
    		return;
		}

		Node<Key, Value> *newRoot = new Node<Key, Value>(pred->getKey(), pred->getValue(), removeNodeParent);
		predParent->setRight(NULL);
		newRoot->setRight(removeNode->getRight());
		newRoot->setLeft(removeNode->getLeft());
		Node<Key, Value> *left = removeNode->getLeft();

		if (removeNodeParent) {
			if(removeNodeParent->getRight() == removeNode) removeNodeParent->setRight(newRoot);
			else removeNodeParent->setLeft(newRoot);
		}
		else mRoot = newRoot;

		if (left) left->setParent(newRoot);
		if (right) right->setParent(newRoot);

		newRoot->setParent(removeNodeParent);

		if (predParent->getRight() == pred) predParent->setRight(pred->getLeft()); 
		else predParent->setLeft(pred->getLeft());
		if (newRoot == mRoot) height_help(newRoot);
		height_help(predParent);

		delete pred;
	}
    delete removeNode;
    return;
}

template<typename Key, typename Value>				//DONE
void BinarySearchTree<Key, Value>::clear_help(Node<Key, Value>* node) {
	if(node == NULL) return;
	clear_help(node->getLeft());
	clear_help(node->getRight());
	delete node;
	return;
}

/**
* A method to remove all contents of the tree and reset the values in the tree 
* for use again.
*/
template<typename Key, typename Value>				//DONE
void BinarySearchTree<Key, Value>::clear() {
	clear_help(mRoot);
	mRoot = NULL;
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>				//DONE
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const {
	Node<Key, Value>* temp = mRoot;
	while(temp) temp = temp->getLeft();
	return temp;
}

/**
* Helper function to find a node with given key, k and 
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>				//DONE
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const 
{
	if((!mRoot) || ((mRoot)->getKey() == key)) return mRoot;
	
	Node<Key, Value> *temp = mRoot;
	while(temp) {
		if(temp->getKey() > key) temp = temp->getLeft();
		else if(temp->getKey() == key) return temp;
		else temp = temp->getRight();
	}
	return NULL;
}

template<typename Key, typename Value>				//DONE
void BinarySearchTree<Key, Value>::printRoot (Node<Key, Value>* root) const
{
	if (root)
	{
		std::cout << "[";
		printRoot (root->getLeft());
		std::cout << " (" << root->getKey() << ", " << root->getValue() << ") ";
		printRoot (root->getRight());
		std::cout << "]";
	}
}

#endif
