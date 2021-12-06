#ifndef NODE
#define NODE

#include<iostream>


template<class T> struct Node { //node constructor
	typedef typename T	value_type;
	T data; //holds key for the multiset
	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr; //defines parents and children
	int color = 0; //holds the color value of the node
	bool tn = true;
public:
	virtual ~Node() {
	}
};


template<class T>
using NodePtr = Node<T>*;

template<class T>
NodePtr<T> predecessor(NodePtr<T> x)
{
	// if the left subtree is not null,
	// the predecessor is the rightmost node in the left subtree
	if (x->left != nullptr && !x->left->tn)
	{
		return maximum(x->left);
	}

	// Else it is the lowest ancestor of x whose
	// right child is also an ancestor of x.
	auto y = x->parent;
	while (y != nullptr && x == y->left && !x->tn)
	{
		x = y;
		y = y->parent;
	}

	return y;
}
template<class T>
NodePtr<T> successor(NodePtr<T> x)
{
	// If the right subtree is not null,
	// the successor is the leftmost node in the right subtree
	if (x->right != nullptr && !x->right->tn)
	{
		return minimum(x->right);
	}

	// Else it is the lowest ancestor of x whose
	// left child is also an ancestor of x.
	auto y = x->parent;
	while (y != nullptr && x == y->right && !y->tn)
	{
		x = y;
		y = y->parent;
	}
	return y;
}

template<class T>
NodePtr<T> minimum(NodePtr<T> node)//finds minimum node connected
{
	while (node->left != nullptr && !node->left->tn)
	{
		node = node->left;
	}
	return node;
}

// find the node with the maximum key
template<class T>
NodePtr<T> maximum(NodePtr<T> node)
{
	while (node->right != nullptr && !node->right->tn)
	{
		node = node->right;
	}
	return node;
}

#endif // !NODE