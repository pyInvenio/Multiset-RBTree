#include <iostream>
#include <vector>
#include "Multiset.h"
#include "Node.h"
using namespace std;
#include "RB_Iterator.h"

template<class T>
Multiset<T>::Multiset() { //default constructor
	TNULL = new Node<T>;
	TNULL->color = BLACK;
	TNULL->left = nullptr;
	TNULL->right = nullptr;
	TNULL->tn = true;
	root = TNULL;
}

//copy constructor
template<class T>
Multiset<T>::Multiset(const Multiset<T> &other) {
	TNULL = new Node<T>;
	TNULL->color = BLACK;
	TNULL->left = nullptr;
	TNULL->right = nullptr;
	TNULL->tn = true;
	root = copyHelper(other.root);
}
//copy operator
template<class T>
Multiset<T> Multiset<T>::operator=(Multiset& other) {
	TNULL = new Node<T>;
	TNULL->color = BLACK;
	TNULL->left = nullptr;
	TNULL->right = nullptr;
	TNULL->tn = true;
	root = copyHelper(other.root);
}
//move constructor
template<class T>
Multiset<T>::Multiset(Multiset<T>&& other) {
	TNULL = new Node<T>;
	TNULL->color = BLACK;
	TNULL->left = nullptr;
	TNULL->right = nullptr;
	TNULL->tn = true;
	root = copyHelper(other.root);
	other.root = nullptr;
}

//move operator
template<class T>
Multiset<T>& Multiset<T>::operator=(Multiset&& other) {
	TNULL = new Node<T>;
	TNULL->color = BLACK;
	TNULL->left = nullptr;
	TNULL->right = nullptr;
	TNULL->tn = true;
	root = copyHelper(other.root);
	other.root = nullptr;
}

//helper method for copy constructor
template<class T>
NodePtr<T> Multiset<T>::copyHelper( NodePtr<T> other) {
	if (other == TNULL)
		return TNULL;
	if (other->tn) 
		return TNULL;
	if (other==nullptr) 
		return nullptr;	
	//reassigns values
	NodePtr<T> newnode = new Node<T>;
	newnode->color = other->color;
	newnode->data = other->data;
	newnode->tn = other->tn;

	//recursion
	newnode->left = copyHelper(other->left);
	if (newnode->left != TNULL && newnode->left != nullptr && !newnode->left->tn)//resassigns parent
		newnode->left->parent = newnode;
	newnode->right = copyHelper(other->right);
	if (newnode->right != TNULL && newnode->right != nullptr && !newnode->right->tn)
		newnode->right->parent = newnode;
	
	return newnode;
	
}

template<class T>
Multiset<T>::~Multiset() {//destructor
	if (root) {
		if (root->left)
			delete root->left;
		if (root->right)
			delete root->right;
		delete root;
	}
}

template<class T>
void Multiset<T>::initNullNode(NodePtr<T> node, NodePtr<T> parent) {//null node creator
	node->data = T();
	node->parent = parent;
	node->left = nullptr;
	node->right = nullptr;
	node->color = 0;
	node->tn = true;
}

template<class T>
void Multiset<T>::preOrderHelper(NodePtr<T> node) {//preorder traverse
	if (node != TNULL) {
		cout << node->data << " ";
		preOrderHelper(node->left);
		preOrderHelper(node->right);
	}
}

template<class T>
void Multiset<T>::inOrderHelper(NodePtr<T> node) {//inordertraverse
	if ( node != nullptr && !node->tn  && node != TNULL) {
		inOrderHelper(node->left);
		cout << node->data << " ";
		inOrderHelper(node->right);
	}
}

template<class T>
NodePtr<T> Multiset<T>::searchTreeHelper(NodePtr<T> node, T key) {//postorder traverse
	if (node == TNULL || key == node->data) return node;
	if (key < node->data) {
		return searchTreeHelper(node->left, key);
	}
	return searchTreeHelper(node->right, key);
}

//fixes tree after deletion
template<class T>
void Multiset<T>::fixDelete(NodePtr<T> x) {
	NodePtr<T> s;

	while (x != root && x->color == BLACK) {
		if (x == x->parent->left) {
			s = x->parent->right;
			if(s->color == RED){
				s->color = BLACK;
				x->parent->color = RED;
				leftRotate(x->parent);
				s = x->parent->right;
			}
			if (s->left->color == BLACK && s->right->color == BLACK)
			{
				// x’s sibling S is black, and both of S’s children are black
				s->color = RED;
				x = x->parent;
			}
			else {
				if (s->right->color == BLACK) {
					s->left->color = BLACK;
					s->color = RED;
					rightRotate(s);
					s = x->parent->right;
				}

				s->color = x->parent->color;
				x->parent->color = BLACK;
				s->right->color = BLACK;
				leftRotate(x->parent);
				x = root;
			}
		}
		else {
			s = x->parent->left;
			if (s->color == RED) {
				s->color = BLACK;
				x->parent->color = RED;
				rightRotate(x->parent);
				s = x->parent->left;
			}

			if (s->right->color == BLACK && s->left->color == BLACK) {
				s->color = RED;
				x = x->parent;
			}
			else {
				if (s->left->color == BLACK) {
					s->right->color = BLACK;
					s->color = RED;
					leftRotate(s);
					s = x->parent->left;
				}

				s->color = x->parent->color;
				x->parent->color = BLACK;
				s->left->color = BLACK;
				rightRotate(x->parent);
				x = root;
			}
		}
	}
	x->color = BLACK;
}

//transplants rb nodes
template<class T>
void Multiset<T>::rbTransplant(NodePtr<T> u, NodePtr<T> v) {
	if (u->parent == nullptr) {
		root = v;
	}
	else if (u == u->parent->left) {
		u->parent->left = v;
	}
	else {
		u->parent->right = v;
	}
	v->parent = u->parent;
}

//helps with deletion method
template<class T>
bool Multiset<T>::deleteNodeHelper(NodePtr<T> node, T key) {
	sizeMultiset--;
	NodePtr<T> z = TNULL;
	NodePtr<T> x, y;
	while ( node !=nullptr && node->tn == false && node != TNULL) //iterate and find the node with the key
	{
		if (node->data == key)
		{
			z = node;

		}

		if (node->data <= key)
		{
			node = node->right;
		}
		else
		{
			node = node->left;
		}
	}

	if (z == TNULL) //can't find node
	{
		sizeMultiset++;
		return false;
	}

	y = z;
	int y_original_color = y->color;
	if (z->left == nullptr || z->left == TNULL)
	{
		x = z->right;
		rbTransplant(z, z->right);
	}
	else if (z->left == nullptr|| z->right == TNULL)
	{
		x = z->left;
		rbTransplant(z, z->left);
	}
	else
	{
		y = minimum(z->right);
		y_original_color = y->color;
		x = y->right;
		if (y->parent == z)
		{
			x->parent = y;
		}
		else
		{
			rbTransplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}

		rbTransplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}

	delete z;

	if (y_original_color == BLACK)
	{
		fixDelete(x);
	}

	return true;
}

//fixes tree after insertion
template<class T>
void Multiset<T>::fixInsert(NodePtr<T> k) {
	NodePtr<T> u; // Uncle Node
	while (k->parent->color == RED)
	{
		if (k->parent == k->parent->parent->right)
		{
			u = k->parent->parent->left;
			if (u->color == RED)
			{
				// parent and uncle are red
				u->color = BLACK;
				k->parent->color = BLACK;
				k->parent->parent->color = RED;
				k = k->parent->parent;
			}
			else
			{
				if (k == k->parent->left)
				{
					// parent is red, uncle is black
					k = k->parent;
					rightRotate(k);
				}
				// K is right child of parent
				k->parent->color = BLACK;
				k->parent->parent->color = RED;
				leftRotate(k->parent->parent);
			}
		}
		else
		{
			u = k->parent->parent->right; // uncle

			if (u->color == RED)
			{
				// mirror case of parent and uncle are red
				u->color = BLACK;
				k->parent->color = BLACK;
				k->parent->parent->color = RED;
				k = k->parent->parent;
			}
			else
			{
				if (k == k->parent->right)
				{
					// mirror case of k is left child of parent
					k = k->parent;
					leftRotate(k);
				}
				// mirror case of k is right child of parent
				k->parent->color = BLACK;
				k->parent->parent->color = RED;
				rightRotate(k->parent->parent);
			}
		}
		if (k == root)
		{
			break;
		}
	}
	root->color = BLACK;
}

//print helper for prettyprint
template<class T>
void Multiset<T>::printHelper(NodePtr<T> root, string indent, bool last) {
	if (root != TNULL&&!root->tn)
	{
		std::cout << indent;
		if (last)
		{
			std::cout << "R----";
			indent += "     ";
		}
		else
		{
			std::cout << "L----";
			indent += "|    ";
		}

		string sColor = (root->color == RED) ? "RED" : "BLACK";
		cout << root->data << "(" << sColor << ")" << std::endl;
		printHelper(root->left, indent, false);
		printHelper(root->right, indent, true);
	}
}

//the different types of traversal
template<class T>
void Multiset<T>::preOrder() {
	preOrderHelper(this->root);
}

template<class T>
void Multiset<T>::inOrder() {
	inOrderHelper(this->root);
}
template<class T>
void Multiset<T>::postOrder() {
	postOrderHelper(this->root);
}

//adds a node with a key
template<class T>
void Multiset<T>::add(T key) {
	sizeMultiset++;
	// Ordinary Binary Search Insertion
	NodePtr<T> node = new Node<T>;
	node->parent = nullptr;
	node->data = key;
	node->left = TNULL;
	node->right = TNULL;
	node->color = RED; // new node must be red
	node->tn = false;
	NodePtr<T> y = nullptr;
	auto x = this->root;

	while (x != TNULL)
	{
		y = x;
		if (node->data < x->data)
		{
			x = x->left;
		}
		else
		{
			x = x->right;
		}
	}

	// y is parent of x
	node->parent = y;
	if (y == nullptr)
	{
		root = node;
	}
	else if (node->data < y->data)
	{
		y->left = node;
	}
	else
	{
		y->right = node;
	}

	// if new node is a root node, simply return
	if (node->parent == nullptr)
	{
		node->color = BLACK;
		return;
	}

	// if the grandparent is null, simply return
	if (node->parent->parent == nullptr)
	{
		return;
	}

	// Fix the tree
	fixInsert(node);
}


//returns root
template<class T>
NodePtr<T> Multiset<T>::getRoot() {
	return this->root;
}

//prints tree shape
template<class T>
void Multiset<T>::prettyPrint()
{
	if (root)
	{
		printHelper(this->root, "", true);
	}
}

//removes all nodes with key
template<class T>
bool Multiset<T>::remove(T data)
{
	bool found = false;
	while (deleteNodeHelper(this->root, data)) {
		found = false;
	}
	return found;
}


//rotation methods for reorganization of RBTree
template<class T>
void Multiset<T>::rightRotate(NodePtr<T> x)
{
	auto y = x->left;
	x->left = y->right;
	if (y->right != TNULL&& !y->right->tn)
	{
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr)
	{
		this->root = y;
	}
	else if (x == x->parent->right)
	{
		x->parent->right = y;
	}
	else
	{
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
}


template<class T>
void Multiset<T>::leftRotate(NodePtr<T> x)
{
	
	auto y = x->right;
	x->right = y->left;
	if (y->left != TNULL&&!y->left->tn)
	{
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr)
	{
		this->root = y;
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}


//finds prev node
template<class T>
NodePtr<T> Multiset<T>::predecessor(NodePtr<T> x)
{
	// if the left subtree is not null,
	// the predecessor is the rightmost node in the left subtree
	if (x->left != TNULL)
	{
		return maximum(x->left);
	}

	// Else it is the lowest ancestor of x whose
	// right child is also an ancestor of x.
	auto y = x->parent;
	while (y != TNULL && x == y->left)
	{
		x = y;
		y = y->parent;
	}

	return y;
}

//finds next node
template<class T>
NodePtr<T> Multiset<T>::successor(NodePtr<T> x)
{
	// If the right subtree is not null,
	// the successor is the leftmost node in the right subtree
	if (x->right != TNULL)
	{
		return minimum(x->right);
	}

	// Else it is the lowest ancestor of x whose
	// left child is also an ancestor of x.
	auto y = x->parent;
	while (y != TNULL && x == y->right)
	{
		x = y;
		y = y->parent;
	}
	return y;
}


// search the tree for the key k and return the corresponding node
template<class T>
NodePtr<T> Multiset<T>::searchTree(T k)
{
	return searchTreeHelper(this->root, k);
}

// find the node with the minimum key
template<class T>
NodePtr<T> Multiset<T>::minimum(NodePtr<T> node)
{
	while (node->left != nullptr  &&node->left != TNULL)
	{
		node = node->left;
	}
	return node;
}

// find the node with the maximum key
template<class T>
NodePtr<T> Multiset<T>::maximum(NodePtr<T> node)
{
	while (node->right != nullptr  && node->right != TNULL)
	{
		node = node->right;
	}
	return node;
}


//returns begin iterator
template<class T>
rbiterator<T> Multiset<T>::begin(){
	rbiterator<T> i = minimum(this->root);
	return i;
}

//returns end iterator
template<class T>
rbiterator<T> Multiset<T>::end() {
	rbiterator<T> i = maximum(this->root);
	return i;
}

//finds iterator with a key
template <typename T>
rbiterator<T> Multiset<T>::findIter(T key) {
	rbiterator<T> b = this->begin();
	rbiterator<T> e = this->end();
	while (b.value()!=key) {
		if (b == e)
			return NULL;
		b++;
	}
	return b;
}


//counts nodes with a key
template<typename T>
int Multiset<T>::count(T key) {
	rbiterator<T> b = this->begin();
	rbiterator<T> e = this->end();
	int count = 0;
	while (b<=e) {
		if (b.value() == key)
			count++;
		b++;
	}
	return count;
}

//erases a range
template<typename T>
void Multiset<T>::erase(rbiterator<T> first, rbiterator<T> last) {
	vector<T> removeList;
	for (rbiterator<T> i = first; i <= last; i++) {
		removeList.push_back(*i);
	}
	for (auto& e : removeList) {
		remove(e);
	}
	return;
}

//prints in order
template<class T>
void Multiset<T>::print() {
	inOrder();
	cout << endl;
}