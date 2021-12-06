#ifndef RBIterator
#define RBIterator
#include <iostream>
#include <iterator>
#include "Multiset.h"
//#include "RBTree_implement.h"
#include "Node.h"
using namespace std;

template<class T>
class rbiterator  {

protected:
	NodePtr<T> iter;
private:

	//rbiterator(NodePtr<T> ptr):iter(ptr){}
public:
	
	rbiterator() : iter{ nullptr }{}
	rbiterator(NodePtr<T> ptr) :iter{ ptr } {};

	T& value() {
		return iter->data;
	}
	inline NodePtr<T> getIter() { return iter; };
	bool operator== (const rbiterator& source) const { return (iter == source.iter); };
	bool operator!= (const rbiterator& source) const { return (iter != source.iter); };
	bool operator<= (const rbiterator& source) const { return (iter!=nullptr && iter->data <= source.iter->data); };
	bool operator>= (const rbiterator& source) const { return (iter != nullptr && iter->data >= source.iter->data); };
	bool operator< (const rbiterator& source) const { return (iter != nullptr && iter->data < source.iter->data); };
	bool operator> (const rbiterator& source) const { return (iter!=nullptr && iter->data > source.iter->data); };
	rbiterator operator++ ();
	const rbiterator operator++ (int);
	rbiterator       operator--                                         ();
	const rbiterator operator--                                         (int);
	explicit operator bool() const { return (iter != nullptr); };
	T& operator* () const { return (iter->data); };
	NodePtr<T>* operator->(void) { return iter }

};

#include "RBIterator_impl.h"
#endif // !RBIterator
