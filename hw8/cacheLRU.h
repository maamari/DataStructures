#include "splayTree.h"
#include <stdexcept>

template <typename Key, typename Value>
class cacheLRU : public SplayTree<Key, Value>{
public:
	//CONSTRUCTOR CONTAINING INITIAL CAP AND SIZE
	cacheLRU(int capacity){
		this->capacity = capacity;
		this->size = 0;
	}

	~cacheLRU(){}

	void put(const std::pair<const Key, Value>& keyValuePair);
	std::pair<const Key, Value> get(const Key& key);

private:
	int capacity, size;
};


//This function will insert the key/value into the cache
template <typename Key, typename Value>
void cacheLRU<Key, Value>::put(const std::pair<const Key, Value>& keyValuePair){
	Node<Key, Value> * pos = BinarySearchTree<Key, Value>::internalFind(keyValuePair.first);
	if(pos == nullptr){
		SplayTree<Key, Value>::insert(keyValuePair);
		if (size == capacity) SplayTree<Key, Value>::deleteMinLeaf();
		else if(size < capacity) size++;
	}
	else SplayTree<Key, Value>::splay(pos->getParent());	
}

//finds a node with specific key in tree and returns the key/value
template <typename Key, typename Value>
std::pair<const Key, Value> cacheLRU<Key, Value>::get(const Key& key){
	typename cacheLRU<Key, Value>::iterator i = SplayTree<Key, Value>::find(key);
	if(i == this->end()) throw std::logic_error("ERROR");
	return *i;
}