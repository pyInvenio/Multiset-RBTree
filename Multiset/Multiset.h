#ifndef RedBlackTree
#define RedBlackTree
#include "Node.h"
#include <iostream>

#define BLACK 0
#define RED 1

using namespace std;
#include "RB_Iterator.h"

template<class T> class Multiset {
private:
	NodePtr<T> root; //root of tree
	NodePtr<T> TNULL; //filler null node

	void initNullNode(NodePtr<T> node, NodePtr<T> parent);

	//traverse orders
	void preOrderHelper(NodePtr<T> node);

	void inOrderHelper(NodePtr<T> node);

	void postOrderHelper(NodePtr<T> node);

	//copy/move helper methods
	NodePtr<T> copyHelper( NodePtr<T> copy_from);
	NodePtr<T> moveHelper( NodePtr<T> move_from);

	//search helper
	NodePtr<T> searchTreeHelper(NodePtr<T> node, T key);
	void rbTransplant(NodePtr<T> u, NodePtr<T> v);

	//successor and predecessor for iteration
	NodePtr<T> successor(NodePtr<T> x);
	NodePtr<T> predecessor(NodePtr<T> x);

	//for printing a tree
	void printHelper(NodePtr<T> root, string indent, bool last);

	//rotation methods
	void leftRotate(NodePtr<T> x);
	void rightRotate(NodePtr<T> x);

	//delete methods
	bool deleteNodeHelper(NodePtr<T> node, T key);
	void fixDelete(NodePtr<T> x);
	void fixInsert(NodePtr<T> k);

public:
	int sizeMultiset = 0;
	//constructors
	Multiset();
	virtual ~Multiset();
	Multiset(const Multiset<T> &other);
	Multiset( Multiset<T> &&other);
	Multiset<T>& operator= (Multiset<T>&& other);
	Multiset<T> operator= (Multiset<T>& other);

	//returns root
	NodePtr<T> getRoot();

	virtual void add(T key); //adds a node with a key

	virtual bool remove(T data); //deletes all nodes with a key

	virtual void prettyPrint(); //prints in tree format

	NodePtr<T> searchTree(T k); //searches tree for node with key
	
	//begin and end iterators
	rbiterator<T> begin();
	rbiterator<T> end();
	//different order helpers
	void preOrder();
	void inOrder();
	void postOrder();

	//finds iterator with a key
	rbiterator<T> findIter(T key);
	NodePtr<T> minimum(NodePtr<T> node);
	NodePtr<T> maximum(NodePtr<T> node);

	//count and size
	int count(T key);
	int size() {
		return sizeMultiset;
	};

	//erases range
	void erase(rbiterator<T> first, rbiterator<T> last);

	//prints in a line
	void print();
};

#include "Multiset_implement.h"

#endif